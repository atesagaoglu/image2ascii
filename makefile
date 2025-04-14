SRC = main.c

OBJ = $(SRC:.c=.o)

TARGET = image2ascii

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $(TARGET) -lm $(OBJ)

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
