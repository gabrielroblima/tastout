BIN = tastout

all: bin run

bin:
	$(CXX) main.cpp -o $(BIN)

run: 
	./$(BIN) > tastout.output
	
clean:
	rm $(BIN) tastout.output
