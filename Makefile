CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -O2
LDLIBS  = -lm

SRC_DIR = src
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/artemis.c $(SRC_DIR)/validaciones.c
OBJS    = $(SRCS:.c=.o)
TARGET  = artemis

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe reporte_mision.txt

.PHONY: all run clean
