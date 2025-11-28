# ===========================
# Project Configuration
# ===========================
PROJECT_NAME = test_game

SRC_DIR      = src
INCLUDE_DIR  = include
BUILD_DIR    = build
BIN_DIR      = $(BUILD_DIR)/bin
OBJ_DIR      = $(BUILD_DIR)/obj


# ===========================
# Compiler Configuration
# ===========================
CC       = gcc
CFLAGS   = -Wall -Wextra -std=c23 -O2 -g
INCLUDES = -I$(INCLUDE_DIR) -I$(SRC_DIR) -Iexternal/raylib/src

LDFLAGS  = -Lexternal/raylib/src -lraylib -lm -lpthread -ldl -lGL -lrt -lX11


# ===========================
# Source and Object Discovery
# ===========================
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
TARGET = $(BIN_DIR)/$(PROJECT_NAME)


# ===========================
# Build Rules
# ===========================
.PHONY: all run clean rebuild print-sources core

all: $(TARGET)


$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@echo "🔗 Linking $(PROJECT_NAME)..."
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	@echo "✅ Build complete: $@"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# ===========================
# Run normally
# ===========================
run: all
	@echo "🚀 Running $(PROJECT_NAME)..."
	./$(TARGET)


# ===========================
# Run with core dump support
# ===========================
core: all
	@mkdir -p $(BIN_DIR)/cores
	@echo "💥 Enabling core dumps..."

	@bash -c '\
		ulimit -c unlimited; \
		echo "$(BIN_DIR)/cores/core.%e.%p" | sudo tee /proc/sys/kernel/core_pattern >/dev/null; \
		echo "🚀 Running $(PROJECT_NAME)..."; \
		./$(TARGET); \
	'

	@echo "📦 If a crash occurred, core dump is in: $(BIN_DIR)/cores/"


# ===========================
# Cleanup
# ===========================
clean:
	@rm -rf $(BUILD_DIR)
	@echo "🧹 Cleaned build files."


rebuild: clean all


print-sources:
	@echo "SRC:"
	@echo "$(SRC)"
	@echo "OBJ:"
	@echo "$(OBJ)"

