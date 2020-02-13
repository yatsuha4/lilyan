TOPDIR	:= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

SRCDIR	:= src
OBJDIR	:= obj
BINDIR	:= bin

MKDIR	:= mkdir -p
RUBY	:= ruby

CXX	:= clang++
CXXFLAGS	:= \
	-std=c++17 \
	-I$(TOPDIR) \
	-MMD \
	-c

LD	:= clang++

#
SRCS	:= $(wildcard $(SRCDIR)/*.cpp)
OBJS	:= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

$(BINDIR)/lilyan: $(OBJS)
	@$(MKDIR) $(dir $@)
	$(LD) -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(SRCDIR)/Grammer.hpp: $(SRCDIR)/Grammer.ll $(TOPDIR)/lilyan.rb
	$(RUBY) $(TOPDIR)/lilyan.rb -o $@ $<

#
-include $(patsubst %.o, %.d, $(OBJS))
