# 1. Ustawienia kompilatora
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# 2. Nazwa pliku wynikowego (Twojego programu)
TARGET = student_app

# 3. Lista plików źródłowych
SRCS = main.c student_utilits.c
OBJS = $(SRCS:.c=.o)

# 4. Domyślna reguła (odpala się po wpisaniu samego 'make')
all: $(TARGET)

# 5. Łączenie (linkowanie) plików .o w gotowy program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 6. Kompilacja pojedynczych plików .c do plików obiektowych .o
# Dodajemy student.h, żeby make wiedział, że jak zmienisz nagłówek, musi przebudować kod
%.o: %.c student.h
	$(CC) $(CFLAGS) -c $< -o $@

# 7. Reguła do sprzątania śmieci (plików .o i programu)
clean:
	rm -f $(OBJS) $(TARGET)