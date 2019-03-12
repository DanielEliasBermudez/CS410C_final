
all:
	g++ -std=c++1z cgrep.cpp SearchManager.cpp SearchThread.cpp -lstdc++fs -pthread -o cg

clean:
	rm cg
