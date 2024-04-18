CXX = g++
CXXFLAGS = -Wall -Wextra -g3 -Iinclude
SRC = FilaGG1.cc main.cc Simulator.cc Random.cc
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cc=.o))
EXEC = main.exe
ARGS = --espaciosDisponibles 4 --trabajosAProcesar 20 --slogs --elogs

$(EXEC): $(OBJ) checkArgs.o
	$(CXX) $(CXXFLAGS) $(OBJ) checkArgs.o -o $(EXEC)

$(OBJ_DIR)/%.o: %.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

checkArgs.o: include/checkArgs.cc
	$(CXX) $(CXXFLAGS) -c $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

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
	rm -rf $(OBJ_DIR) $(EXEC) checkArgs.o
