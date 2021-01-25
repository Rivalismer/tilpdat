.DEFAULT_GOAL := taco

SOURCES := protein.c taco_krydder.c taco_lefse.c taco_saus.c\
grønnsaker.c main.c drikke.c

BUILD_DIR := build
SOURCE_DIR := source

SRC := $(SOURCES:%.c=source/%.c)
CC = gcc
CFLAGS = -O0 -g3
INGR = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/taco

taco : $(INGR)
	echo ingr: $(INGR)
	echo build: $(SRC)
	$(CC) -o $(BUILD_DIR)/taco $(INGR) $(CFLAGS)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)
