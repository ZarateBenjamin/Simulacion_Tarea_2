CXX = g++
CXXFLAGS = -Wall -Wextra -g3 -Iinclude
SRC = FilaGG1.cc main.cc Simulator.cc Random.cc include/checkArgs.cc
OBJ = $(SRC:.cc=.o)
EXEC = main.exe
ARGS = --espaciosDisponibles 4 --trabajosAProcesar 20 --slogs --elogs

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXEC)
	@echo "Si se ejecuta $(EXEC):"
	@echo "  faltan argumentos para comenzar,"
	@echo "  --espaciosDisponibles = -e (n)"
	@echo "  --trabajosAProcesar  = -t (n)"
	@echo "  --slogs = -sl"
	@echo "  --elogs = -el"
	@echo " Ejemplo de comando:"
	@echo " "./main.exe --espaciosDisponibles 4 --trabajosAProcesar 20 --slogs --elogs"

	./$(EXEC) $(ARGS)

clean:
	rm -f $(OBJ) $(EXEC)

