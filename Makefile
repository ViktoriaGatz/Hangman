CC := gcc -Wall
FLAGS := -std=c99
LIBS := -lm
SDL2 := `sdl2-config --libs --cflags` -lSDL2_image
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./obj

.PHONY: all clean install uninstall rebuild

#	gcc main.c `sdl2-config --libs --cflags` --std=c99 -Wall -lSDL2_image -lm -o
#	main

all: $(BIN_DIR)/hangman

$(BIN_DIR)/hangman: $(OBJ_DIR)/main.o $(OBJ_DIR)/names.o $(OBJ_DIR)/play.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/names.o $(OBJ_DIR)/play.o $(FLAGS) $(LIBS) -o $(BIN_DIR)/hangman $(SDL2)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(FLAGS) $(LIBS)

#$(BIN_DIR)/hangman:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/hangman.o  $(OBJ_DIR)/names.o
#	$(CC) $(OBJ_DIR)/main.o  $(OBJ_DIR)/hangman.o  $(OBJ_DIR)/names.o -o $(BIN_DIR)/hangman $(FLAGS) $(LIBS)

#$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
#	$(CC) -c $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o $(FLAGS) $(LIBS)

$(OBJ_DIR)/play.o: $(SRC_DIR)/play.c
	$(CC) -c $(SRC_DIR)/play.c -o $(OBJ_DIR)/play.o $(FLAGS) $(LIBS)

$(OBJ_DIR)/names.o: $(SRC_DIR)/names.c
	$(CC) -c $(SRC_DIR)/names.c -o $(OBJ_DIR)/names.o $(FLAGS) $(LIBS)

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/hangman

install:
	sudo cp ./bin/hangman /usr/bin/hangman

uninstall:
	sudo rm -f /usr/bin/hangman

rebuild: clean all
