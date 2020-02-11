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
  def initialize(name)
    @name = name
    @list = Array.new
    @recursion = Array.new
  end
  attr_reader :name

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
    output.puts("std::any #{@name.to_s}(lilyan::Input& input) {") {
      @list.each { |list|
        list.write(output, self)
      }
      puts_return(output, 'std::any()')
    }
    output.puts("}")

    unless @recursion.empty?
      output.puts("std::any #{@name.to_s}(lilyan::Input& input, const std::any& value) {") {
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
      output.puts("return #{@name.to_s}(input, #{value});")
    else
      output.puts("return #{value};")
    end
  end
end

#
class List
  def initialize
    @terms = Array.new
    @func = nil
  end
  attr_reader :terms
  attr_accessor :func

  def recursion?(rule)
    return @terms.include?(rule)
  end

  def write(output, rule)
    output.puts("{") {
      output.puts("lilyan::Input _input(input);")
      @func.prematch(output)
      text = ''
      @terms.each_with_index { |item, i|
        if text.empty?
          text << 'if('
        else
          text << ' &&'
          output.puts(text)
          text = '   '
        end
        text << 'skip(_input) && '
        cond = case item
               when Symbol
                 if item == rule.name
                   'value'
                 else
                   "#{item.to_s}(_input)"
                 end
               when String
                 "_input.match(std::string(\"#{item}\"))"
               when Regexp
                 "_input.match(std::regex(R\"(#{item.source})\"))"
               end
        text << @func.match(i, cond) << ".has_value()";
      }
      output.puts(text + ') {') {
        @func.postmatch(output)
        output.puts("input = _input;")
        rule.puts_return(output, "result")
      }
      output.puts('}')
    }
    output.puts("}")
  end
end

#
class Func
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
      output.puts("result->at(0) = Func(\"#{@name}\", static_cast<func_t>(&Parser::#{@name}));")
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
    @output = Output.new(STDOUT)
    @rules = Hash.new
    @funcs = Hash.new
  end
  attr_accessor :name
  attr_accessor :output

  def parse(src)
    input = Input.new(src)
    while(!input.end?)
      if match = input.token('(\w+)\s*:')
        rule = Rule.new(match[1].to_sym)
        while(!input.token(';'))
          list = List.new
          while(!input.token('->'))
            if match = input.token('(\w+)')
              list.terms.push(match[1].to_sym)
            elsif match = input.token('\'(.+?)\'')
              list.terms.push(match[1])
            elsif match = input.token('\"(.+?)\"')
              list.terms.push(Regexp.new(match[1]))
            elsif match = input.token('\/(.+?)\/')
              list.terms.push(Regexp.new(match[1]))
            else
              raise "syntax error"
            end
          end
          if match = input.token('(\w+)\(\$(\d+)(?:\s*,\s*\$(\d+))*\)')
            func = Func.new(match[1], 
                            match[2...match.length].compact.collect { |n|
                              Integer(n)
                            })
            list.func = func
            @funcs[func.name] = func
          elsif match = input.token('\$(\d+)')
            list.func = Func.new(nil, [ Integer(match[1]) ])
          else
            raise "syntax error"
          end
          rule.append(list)
        end
        @rules[rule.name] = rule
      else
        raise "syntax error"
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
      @funcs.each_value { |func|
        @output.puts("virtual #{func.to_s} = 0;")
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
