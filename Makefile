T1 = main
CI = city
TSP = tsp

CXX = g++
FLAG = -g -Wall -std=c++11

all: $(T1).o
	$(CXX) $(FLAG) $(T1).o $(CI).o $(TSP).o -o $(T1)
	rm -f $(T1).o
	rm -f $(CI).o
	rm -f $(TSP).o

$(T1).o:
	$(CXX) $(FLAG) -c $(T1).cpp -o $(T1).o

dep:
	$(CXX) $(FLAG) -c $(CI).cpp -o $(CI).o 
	$(CXX) $(FLAG) -c $(TSP).cpp -o $(TSP).o

clean:
	rm -f $(T1)
