#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
SUBDIRS := $(wildcard */.)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS))) $(wildcard $(SRC)/engine/*.cpp) $(wildcard $(SRC)/engine/ECS/*.cpp) $(wildcard $(SRC)/tmxlite/*.cpp) $(wildcard $(SRC)/tmxlite/detail/*.cpp)

# define the C object files 
OBJECTS		:= $(SOURCES:.cpp=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo $(CXX) $(INCLUDES) $(LIBS) -o $(OUTPUTMAIN) $(OBJECTS) $(CXXFLAGS) $(LFLAGS) 
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)
$(MAIN): $(OBJECTS) 
	$(CXX) $(INCLUDES) $(LIBS) -o $(OUTPUTMAIN) $(OBJECTS) $(CXXFLAGS) $(LFLAGS) 

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	@echo $(CXX) $(INCLUDES) $(LIBS) -c $<  -o $@ $(CXXFLAGS)
	$(CXX) $(INCLUDES) $(LIBS) -c $<  -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!

.PHONY: rebuild
rebuild:
	@echo $(SOURCES)
	$(MAKE) clean
	$(MAKE) all

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!