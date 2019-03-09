
all:
	g++ -std=c++1z cgrep.cpp SearchManager.cpp -lstdc++fs -o cg

clean:
	rm cg
