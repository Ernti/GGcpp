CC=g++
CFLAGS=-c -Wall -std=c++0x `sdl2-config --cflags` -I./include
LDFLAGS=`sdl2-config --libs` -lSDL2_net -lGL -lGLU -lGLEW
OBJDIR=obj
BINDIR=bin

CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

$(BINDIR)/projectseven: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp
	    $(CC) $(CFLAGS) -o $@ $<
