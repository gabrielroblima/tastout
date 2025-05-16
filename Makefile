BIN = tastout
FLAGS = -std=c++17 -lX11
all: bin run

bin:
	$(CXX) main.cpp -o $(BIN) $(FLAGS)

run: 
	./$(BIN) > tastout.output
	cat tastout.output
clean:
	rm $(BIN) tastout.output
