# -*- coding: utf-8 -*-

require 'optparse'

#
class Input
  def initialize(src)
    @buff = File.read(src)
  end

  def token(pattern)
    skip
    @buff = @buff.gsub(/\A#{pattern}/, '')
    return $~
  end

  def skip
    @buff = @buff.gsub(/\A\s+/, '')
  end

  def end?
    skip
    return @buff.empty?
  end

  def to_s
    return @buff[0, 40]
  end
end

#
class Output
  INDENT = 2

  def initialize(output)
    @output = output
    @indent = 0
  end

  def puts(line, offset = 0, &proc)
    @output.print(' ' * (INDENT * @indent + offset))
    @output.puts(line)
    if proc
      @indent += 1
      proc.call
      @indent -= 1
    end
  end

  def debug(line)
    puts(line)
  end
end

#
class Rule
  @@rules = Hash.new

  def initialize(name, prefix)
    @name = name
    @prefix = prefix
    @list = Array.new
    @recursion = Array.new
    @@rules[name] = self
  end
  attr_reader :name

  def self.[](name)
    return @@rules[name]
  end

  def append(list)
    if list.recursion?(@name)
      @recursion.push(list)
    else
      @list.push(list)
    end
  end

  def recursion?
    return !@recursion.empty?
  end

  def write(output)
    output.puts("std::any #{self}() {") {
      @list.each { |list|
        list.write(output, self)
      }
      puts_return(output, 'std::any()')
    }
    output.puts("}")

    unless @recursion.empty?
      output.puts("std::any #{self}(const std::any& value) {") {
        @recursion.each { |list|
          list.write(output, self)
        }
        output.puts("return value;")
      }
      output.puts("}")
    end
  end

  def puts_return(output, value)
    if recursion?
      output.puts("return #{self}(#{value});")
    else
      output.puts("return #{value};")
    end
  end

  def to_s
    return "#{@prefix}#{@name.to_s}"
  end
end

#
class List
  def initialize
    @terms = Array.new
    @action = nil
  end
  attr_reader :terms
  attr_accessor :action

  def recursion?(rule)
    return @terms.include?(rule)
  end

  def write(output, rule)
    output.puts("{") {
      output.puts("lilyan::Input _input(getInput());")
      @action.prematch(output)
      text = ''
      @terms.each_with_index { |item, i|
        if text.empty?
          text << 'if('
        else
          text << ' &&'
          output.puts(text)
          text = '   '
        end
        cond = case item
               when Symbol
                 if item == rule.name
                   'value'
                 else
                   (Rule[item] || raise('no such rule')).to_s + "()"
                 end
               when String
                 "getToken(std::string(\"#{item}\"))"
               when Regexp
                 "getToken(std::regex(R\"(#{item.source})\"))"
               end
        text << @action.match(i, cond) << ".has_value()";
      }
      output.puts(text + ') {') {
        @action.postmatch(output)
        rule.puts_return(output, "result")
      }
      output.puts('}')
      output.puts('else {') {
        output.puts("getInput() = _input;")
      }
      output.puts('}')
    }
    output.puts("}")
  end
end

#
class Action
  def initialize(name, args)
    @name = name
    @args = args
  end
  attr_reader :name
  attr_reader :args

  def prematch(output)
    if @name
      output.puts("auto result = std::make_shared<List>(#{@args.size + 1});")
    else
      output.puts("std::any result;")
    end
  end

  def match(index, cond)
    if i = @args.find_index(index + 1)
      if @name
        cond = "(result->at(#{i + 1}) = #{cond})"
      else
        cond = "(result = #{cond})"
      end
    end
    return cond
  end

  def postmatch(output)
    if @name
      output.puts("result->at(0) = Action(\"#{@name}\", static_cast<action_t>(&Parser::#{@name}));")
    end
  end

  def to_s
    return "std::any #{@name}(const List& args)"
  end
end

#
class Parser
  INDENT = '  '

  def initialize
    @name = 'Parser'
    @rule_prefix = ''
    @output = Output.new(STDOUT)
    @rules = Hash.new
    @actions = Hash.new
  end
  attr_accessor :name
  attr_accessor :output

  def parse(src)
    input = Input.new(src)
    while(!input.end?)
      begin
        if match = input.token('(\w+)\s*:')
          rule = Rule.new(match[1].to_sym, @rule_prefix)
          while(!input.token(';'))
            list = List.new
            while(!input.token('->'))
              if match = input.token('(\w+)')
                list.terms.push(match[1].to_sym)
              elsif match = input.token('\'(.+?)\'')
                list.terms.push(match[1])
              elsif match = input.token('\"(.+?)\"')
                list.terms.push(match[1])
              elsif match = input.token('\/(.+?)\/')
                list.terms.push(Regexp.new(match[1]))
              else
                raise "syntax error"
              end
            end
            if match = input.token('(\w+)\(\$(\d+)(?:\s*,\s*\$(\d+))*\)')
              action = Action.new(match[1], 
                              match[2...match.length].compact.collect { |n|
                                Integer(n)
                              })
              list.action = action
              @actions[action.name] = action
            elsif match = input.token('\$(\d+)')
              list.action = Action.new(nil, [ Integer(match[1]) ])
            else
              raise "syntax error"
            end
            rule.append(list)
          end
          @rules[rule.name] = rule
        else
          raise "syntax error"
        end
      rescue => e
        puts(input.to_s)
        raise(e)
      end
    end
  end

  def write
    @output.puts('#include "lilyan/lilyan.hpp"')
    @output.puts("class #{@name} : public lilyan::Parser {") {
      @output.puts("public:", -1)
      @rules.each_value { |rule|
        rule.write(@output)
      }
      @output.puts("protected:", -1);
      @output.puts("Parser() = default;")
      @output.puts("virtual ~Parser() = default;")
      @actions.each_value { |action|
        @output.puts("virtual #{action.to_s} = 0;")
      }
    }
    @output.puts("};")
  end
end

#
parser = Parser.new

option = OptionParser.new
option.on('-c', '--class=NAME') { |v| parser.name = v }
option.on('-o', '--output=FILE') { |v| parser.output = Output.new(File.open(v, 'w')) }
option.parse!(ARGV)

ARGV.each { |src|
  parser.parse(src)
}
parser.write
