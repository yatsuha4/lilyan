LILYANDIR	:= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

OBJDIR		:= obj
BINDIR		:= bin

MKDIR		:= mkdir -p
RUBY		:= ruby

CXX		:= clang++
CXXFLAGS	:= \
		-std=c++17 \
		-stdlib=libc++ \
		-I$(LILYANDIR) \
		-MMD \
		-c \
		-o

LD		:= clang++

#
SRCS = \
	main.cpp

OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

$(BINDIR)/sample: $(OBJS)
	$(MKDIR) $(dir $@)
	$(LD) -o $@ $(OBJS)

Parser.hpp: Parser.ll $(LILYANDIR)/lilyan.rb
	$(RUBY) $(LILYANDIR)/lilyan.rb -o $@ Parser.ll

$(OBJDIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) $@ $<

#
-include $(patsubst %.o, %.d, $(OBJS))
