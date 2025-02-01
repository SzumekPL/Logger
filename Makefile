all:
	g++ -std=c++17 -pthread Logger.cpp main.cpp -o logger

run:
	./logger

clean:
	rm -f logger