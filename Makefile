BIN = tastout

all: bin run

bin:
	$(CXX) -std=c++17 main.cpp -o $(BIN)

run: 
	./$(BIN) > tastout.output
	
clean:
	rm $(BIN) tastout.output
