BUILD_DIR = build
SRC_DIR = src/F15
INC_DIR = src/include
CC = gcc
CFLAGS = -O3 -Wall -Wextra
RM = rm -f
STRIP = strip

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
EXEC = $(BUILD_DIR)/f15

.PHONY: all clean install release

all: $(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

release: CFLAGS += -s
release: all
	$(STRIP) $(EXEC)
	@echo Release build complete: $(EXEC)

clean:
	$(RM) $(BUILD_DIR)/*.o $(EXEC)

install: all
	@echo "Running $(EXEC) with hello.f15..."
	./$(EXEC) hello.f15