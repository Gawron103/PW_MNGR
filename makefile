CC = gcc

SRC_DIR = ./src
INC_DIR = ./inc
BIN_DIR = ./bin
OUTPUT = $(BIN_DIR)/pw_mngr

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC: $(SRC_DIR)/%.c = $(BIN_DIR)/%.o)

C_FLAGS = -Wall -I$(INC_DIR)
LIBS = -lsqlite3

.PHONY: all clean


all: $(OUTPUT)


$(OUTPUT): $(OBJ) | $(BIN_DIR)
	$(CC) $(LIBS) $^ $(C_FLAGS) -o $@


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@


$(BIN_DIR):
	mkdir -p $@


clean:
	$(RM) -rv $(BIN_DIR)