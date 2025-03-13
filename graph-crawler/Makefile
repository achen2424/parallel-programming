CXX = g++
CXXFLAGS = -std=c++11 -I ~/rapidjson/include
LDFLAGS = -lcurl

all: gc

gc: graph_crawler.o
	$(CXX) graph_crawler.o -o gc $(LDFLAGS)

graph_crawler.o: graph_crawler.cpp
	$(CXX) $(CXXFLAGS) -c graph_crawler.cpp

clean:
	rm -f *.o gc