BIN = tastout
FLAGS =

all: bin run

bin:
	$(CXX) main.cpp -o $(BIN) $(FLAGS)
	
run:
	./$(BIN)

clean:
	rm $(BIN)
