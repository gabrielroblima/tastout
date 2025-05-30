BIN = tastout
FLAGS = -std=c++17 -lX11 -lpthread
all: bin run

bin:
	$(CXX) main.cpp -o $(BIN) $(FLAGS)

run: 
	./$(BIN) -s false
clean:
	rm $(BIN) tastout.output
