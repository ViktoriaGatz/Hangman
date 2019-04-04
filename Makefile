FLAGS := -std=c99
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./obj

all: $(BIN_DIR)/hangman


$(BIN_DIR)/hangman:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/hangman.o  $(OBJ_DIR)/function.o
	gcc -Wall -Wextra  $(OBJ_DIR)/main.o  $(OBJ_DIR)/hangman.o  $(OBJ_DIR)/function.o -o $(BIN_DIR)/hangman -lm $(FLAGS)


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o $(FLAGS)


$(OBJ_DIR)/hangman.o: $(SRC_DIR)/hangman.c
		gcc -Wall -Wextra -c  $(SRC_DIR)/hangman.c -o  $(OBJ_DIR)/hangman.o -lm $(FLAGS)


$(OBJ_DIR)/function.o: $(SRC_DIR)/function.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/function.c -o  $(OBJ_DIR)/function.o $(FLAGS)

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/hangman

install:
	sudo cp ./bin/hangman /usr/bin/hangman

uninstall:
	sudo rm -f /usr/bin/hangman
