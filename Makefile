BIN = tastout

all: bin run

bin:
	$(CXX) main.cpp -o $(BIN)

run: 
	./$(BIN)
	
clean:
	rm $(BIN)
