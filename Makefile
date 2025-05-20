BIN_SEND = send
BIN_RECV = recv
FLAGS = -std=c++17 -lX11 -lzmq
all: bin run

bin:
	$(CXX) send.cpp -o $(BIN_SEND) $(FLAGS)
	$(CXX) recv.cpp -o $(BIN_RECV) $(FLAGS)

run: 
	./$(BIN_SEND) -s false
clean:
	rm $(BIN_SEND) $(BIN_RECV) tastout.output
