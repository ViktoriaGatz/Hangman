CC := gcc -Wall -Wextra
C := gcc
FLAGS := -std=c99
FLAG := -std=c11
LIBS := -lm
SDL2 := `sdl2-config --libs --cflags` -lSDL2_image
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./obj
TEST_OBJ := ./obj/test
TEST_DIR := ./test

.PHONY: all clean install uninstall rebuild test_run

#	gcc main.c `sdl2-config --libs --cflags` --std=c99 -Wall -lSDL2_image -lm -o main
# gcc -I thirdparty src -c test/board_test.c -o build/test/board_test.o
# gcc ./test/*.c ./src/geometry.c -lm -std=c11

all: $(BIN_DIR)/hangman $(BIN_DIR)/test

$(BIN_DIR)/hangman: $(OBJ_DIR)/main.o $(OBJ_DIR)/names.o $(OBJ_DIR)/play.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/names.o $(OBJ_DIR)/play.o $(FLAGS) $(LIBS) -o $(BIN_DIR)/hangman $(SDL2)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(FLAGS)

$(OBJ_DIR)/play.o: $(SRC_DIR)/play.c
	$(CC) -c $(SRC_DIR)/play.c -o $(OBJ_DIR)/play.o $(FLAGS)

$(OBJ_DIR)/names.o: $(SRC_DIR)/names.c
	$(CC) -c $(SRC_DIR)/names.c -o $(OBJ_DIR)/names.o $(FLAGS)


$(BIN_DIR)/test: $(TEST_OBJ)/main.o $(TEST_OBJ)/play.o $(OBJ_DIR)/play.o
	$(C) $(TEST_OBJ)/main.o $(TEST_OBJ)/play.o $(OBJ_DIR)/play.o $(FLAG) $(LIBS) -o $(BIN_DIR)/test $(SDL2)

$(TEST_OBJ)/main.o: $(TEST_DIR)/main.c
	$(C) -c $(TEST_DIR)/main.c -o $(TEST_OBJ)/main.o $(FLAG)

$(TEST_OBJ)/play.o: $(TEST_DIR)/play.c
	$(C) -c $(TEST_DIR)/play.c -o $(TEST_OBJ)/play.o $(FLAG)

test_run:
	./bin/test

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/hangman
	rm -rf ./bin/test

install:
	sudo cp ./bin/hangman /usr/bin/hangman

uninstall:
	sudo rm -f /usr/bin/hangman

rebuild: clean all
