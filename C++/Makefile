CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinc -g -O0

SRC = src/main.cpp src/data.cpp src/hora.cpp src/compromisso.cpp src/aula.cpp \
      src/orientacao.cpp src/reuniao.cpp src/evento.cpp src/pessoal.cpp
OBJ = $(SRC:.cpp=.o)

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: main
	./main

# Novo target para valgrind
valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main

# Valgrind com output em arquivo
valgrind-log: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_output.txt ./main

# Valgrind simplificado (apenas leaks)
valgrind-quick: main
	valgrind --leak-check=full ./main

clean:
	rm -f src/*.o main valgrind_output.txt

# Limpa e recompila com valgrind
fresh-valgrind: clean valgrind

.PHONY: all run clean valgrind valgrind-log valgrind-quick fresh-valgrind