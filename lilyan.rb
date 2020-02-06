# -*- coding: utf-8 -*-

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
class Parser
  INDENT = '  '

  def initialize(output = STDOUT)
    @output = output
  end

  def parse(src)
    input = Input.new(src)
    print("class Parser : public lilyan::Parser {\n")
    print(" public:\n")
    funcs = Hash.new
    while(!input.end?)
      if match = input.token('(\w+)\s*:')
        print("std::any #{match[1]}(Input& input) {\n", 1)
        rule = match[1]
        while(!input.token(';'))
          print("{\n", 2)
          print("Input _input(input);\n", 3)
          print("Semantic semantic;\n", 3)
          first = true
          while(!input.token('->'))
            if first
              print("if(", 3)
              first = false
            else
              print(" &&\n")
              print("   ", 3)
            end
            print("append(semantic, _input, ")
            if match = input.token('(\w+)')
              print("#{match[1]}(_input)")
            elsif match = input.token('\'(.+)\'')
              print("_input.match(std::string(\"#{match[1]}\"))")
            elsif match = input.token('\"(.+)\"')
              print("_input.match(std::regex(R\"\\A#{match[1]}\"))")
            elsif match = input.token('\/(.+)\/')
              print("_input.match(std::regex(R\"\\A#{match[1]}\"))")
            else
              raise "syntax error"
            end
            print(")")
          end
          print(") {\n")
          if match = input.token('(\w+)\(\$(\d+)(?:\s*,\s*\$(\d+))*\)')
            args = match[2...match.length].compact.collect { |n|
              Integer(n)
            }
            funcs[match[1]] = args
            args = args.collect { |n| "semantic[#{n}]"}.join(", ")
            print("return #{match[1]}(#{args})\n", 4)
          else
            raise "syntax error"
          end
          print("}\n", 3)
          print("}\n", 2)
        end
        print("return std::any();\n", 2)
        print("}\n", 1)
      else
        raise "syntax error"
      end
    end
    print(" protected:\n");
    print("Parser() = default;\n", 1)
    print("virtual ~Parser() = default;\n", 1)
    funcs.each { |func, args|
      args = args.collect { "const std::any&" }.join(", ")
      print("virtual std::any #{func}(#{args}) = 0;\n", 1)
    }
    print("};\n")
  end

  def print(text, indent = 0)
    @output.print(INDENT * indent)
    @output.print(text)
  end
end

ARGV.each { |src|
  Parser.new.parse(src)
}
