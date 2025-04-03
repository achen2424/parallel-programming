CXXFLAGS=-std=c++11 -I ~/rapidjson/include
LDFLAGS=-lcurl -lpthread
LD=g++
CC=g++

all: level_client

level_client: level_client.o
	$(LD) $< -o $@ $(LDFLAGS)

clean:
	-rm level_client level_client.o *.out
