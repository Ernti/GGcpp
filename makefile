CC=g++
CFLAGS=-c -Wall -std=c++11 `sdl2-config --cflags` -I./include
LDFLAGS=`sdl2-config --libs` -lSDL2_net -lSDL2_image -lGL -lGLU -lGLEW
OBJDIR=obj
BINDIR=bin

CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

$(BINDIR)/gg: $(OBJ_FILES) obj/main.o
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<
