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
      output.puts("return #{@name.to_s}(input, checkValue(#{value}));")
    else
      output.puts("return checkValue(#{value});")
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
      output.puts("lilyan::Semantic semantic;")
      text = ''
      @terms.each { |item|
        if text.empty?
          text << 'if('
        else
          text << ' &&'
          output.puts(text)
          text = '   '
        end
        text << 'append(semantic, _input, '
        case item
        when Symbol
          if item == rule.name
            text << 'value'
          else
            text << "#{item.to_s}(_input)"
          end
        when String
          text << "_input.match(std::string(\"#{item}\"))"
        when Regexp
          text << "_input.matchRegex(std::string(R\"(#{item.source})\"))"
        end
        text << ')'
      }
      output.puts(text + ') {') {
        @func.write(output, rule)
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

  def write(output, rule)
    args = @args.collect { |n| "semantic[#{n}]"}.join(", ")
    output.debug("std::cerr << \"#{@name}\" << std::endl;")
    output.puts("input = _input;")
    rule.puts_return(output, "#{@name}(#{args})")
  end

  def to_s
    args = @args.collect { "const std::any&" }.join(", ")
    return "std::any #{@name}(#{args})"
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
