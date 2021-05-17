DEBUG=yes
CC=g++
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -ansi -pedantic -g -std=c++11 `sdl2-config --cflags`
	LDFLAGS=-lm -g -export-dynamic `sdl2-config --libs` -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx

else
	CFLAGS=-W -Wall -ansi -O2 -pedantic -std=c++11 `sdl2-config --cflags` 
	LDFLAGS=-lm -export-dynamic `sdl2-config --libs` -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx
endif
EXEC=cosmic_clock
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.c=.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

cosmic_clock: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
					

