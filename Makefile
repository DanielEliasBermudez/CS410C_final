
all:
	g++ -std=c++1z cgrep.cpp SearchManager.cpp -o cg

clean:
	rm cg
