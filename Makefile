CC = g++
CFLAGS = -std=c++11 -Wall -c -g
OBJS = obj/deck.o obj/game.o obj/gamestate.o obj/main.o obj/pb.o
EXECUTABLE = pb

all: $(EXECUTABLE)
	@echo ===== pb has been successfully compiled =====

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $(OBJS)

obj/deck.o: src/deck.cpp src/deck.hpp
	$(CC) $(CFLAGS) $< -o $@

obj/game.o: src/game.cpp src/game.hpp
	$(CC) $(CFLAGS) $< -o $@

obj/gamestate.o: src/gamestate.cpp src/gamestate.hpp
	$(CC) $(CFLAGS) $< -o $@

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) $< -o $@

obj/pb.o: src/pb.cpp src/pb.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(EXECUTABLE)
	@echo ===== build has been successfully cleaned =====
