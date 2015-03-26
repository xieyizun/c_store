CC = g++
OBJ = main.o
EXE = db
SRC_PATH = src

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ)

main.o: $(SRC_PATH)/main.cpp
	$(CC) -c $(SRC_PATH)/main.cpp

clean:
	rm $(OBJ) $(EXE)
