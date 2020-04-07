SRC_DIR = ./src
INCLUDE_DIR = ./incl
BIN_DIR = ./bin
DOC_DIR = ./doc
CFLAGS =

BIN_OUT = Carrito.out

CC = gcc

build:
	mkdir --parents $(BIN_DIR)
	$(CC) -I $(INCLUDE_DIR) $(SRC_DIR)/comunicación_interfaz.c main.c  -o $(BIN_DIR)/$(BIN_OUT) `pkg-config --cflags --libs gtk+-2.0` -lm

run:
	./$(BIN_DIR)/$(BIN_OUT)

clean:
	rm -rf $(BIN_DIR)/$(BIN)
	rm -rf doc

doc:
	doxygen ./Doxyfile
	cd doc/latex && make
