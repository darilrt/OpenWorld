CC       := g++
C        := gcc
CCFLAGS  := -Wall -pedantic -std=c++17 -D _DEBUG
CFLAGS   := $(CCFLAGS)

APP      := openworld
SOURCES  := $(wildcard src/*.cpp)
INCLUDES := -I./amuse/include -I./amuse -I/usr/include/SDL2
LIBS     := ./amuse/libamuse.a -lGL -lGLEW -lSDL2

./PHONY: all

all: $(APP)

$(APP): $(SOURCES)
	$(CC) $(CCFLAGS) -o $@ $(SOURCES) $(LIBS) $(INCLUDES)

amuse: info
	$(MAKE) -C amuse all

amuse-clean:
	$(MAKE) -C amuse clean

amuse-cleanall:
	$(MAKE) -C amuse cleanall

info: 
 	$(info $(SOURCES))

clean: 
	rm $(APP)
