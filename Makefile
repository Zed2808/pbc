CC = g++
CFLAGS = -std=c++11 -Wall -c
OBJS = obj/deck.o
EXECUTABLE = pb

all: $(EXECUTABLE)
	@echo ===== pb has been successfully compiled =====

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $(OBJS)

obj/deck.o: src/deck.cpp src/deck.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(EXECUTABLE)
	@echo ===== build has been successfully cleaned =====
