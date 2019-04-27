CC := gcc
FLAGS := -std=c99 -Wall -Wextra -g3 -O0
LIBS := -lm
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./obj

.PHONY: all clean install uninstall rebuild

all: $(BIN_DIR)/hangman

$(BIN_DIR)/hangman:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/hangman.o  $(OBJ_DIR)/function.o
	$(CC) $(OBJ_DIR)/main.o  $(OBJ_DIR)/hangman.o  $(OBJ_DIR)/function.o -o $(BIN_DIR)/hangman $(FLAGS) $(LIBS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o $(FLAGS) $(LIBS)

$(OBJ_DIR)/hangman.o: $(SRC_DIR)/hangman.c
	$(CC) -c $(SRC_DIR)/hangman.c -o $(OBJ_DIR)/hangman.o $(FLAGS) $(LIBS)

$(OBJ_DIR)/function.o: $(SRC_DIR)/function.c
	$(CC) -c $(SRC_DIR)/function.c -o $(OBJ_DIR)/function.o $(FLAGS) $(LIBS)

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/hangman

install:
	sudo cp ./bin/hangman /usr/bin/hangman

uninstall:
	sudo rm -f /usr/bin/hangman

rebuild: clean all
