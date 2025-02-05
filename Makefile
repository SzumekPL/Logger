# Wykrywanie systemu operacyjnego
OS := $(shell uname -s)

# Domyślne ustawienia (dla Linuxa)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I /usr/local/include
GTEST_LIBS = -L /usr/local/lib -lgtest -lgtest_main -pthread
RM = rm -f

# Specjalne ustawienia dla Windowsa
ifeq ($(OS), Windows_NT)
    CXXFLAGS = -std=c++17 -Wall -I C:/googletest/include
    GTEST_LIBS = -LC:/googletest/lib -lgtest -lgtest_main -pthread
    RM = del
endif

#Może warto zrobić flage przy kompilacji zamiast sprawdzać nazwę systemu ?

# Pliki źródłowe i wynikowy program
SRC_TESTS = tests/test_logger.cpp Logger.cpp
TARGET_TESTS = tests/test_logger

SRC = *.cpp
TARGET = logger

all:
	$(CXX) -std=c++17 -Wall -pthread $(SRC) -o $(TARGET)

test: 
	$(CXX) $(CXXFLAGS) $(SRC_TESTS) -o $(TARGET_TESTS) $(GTEST_LIBS)

coverage:
	$(CXX) $(CXXFLAGS) -O0 -fprofile-arcs -ftest-coverage $(SRC_TESTS) -o $(TARGET_TESTS) $(GTEST_LIBS) --coverage
	
run: 
	./logger.exe
	
run_test:
	./tests/test_logger

clean:
	rm -f ./tests/test_logger
	rm -f ./logger
	rm -f ./tests/*.txt
	rm -rf ./tests_dir

