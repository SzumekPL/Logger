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
SRC = tests/test_logger.cpp Logger.cpp
TARGET = tests/test_logger.exe

test: 
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(GTEST_LIBS)

run: 
	./tests/test_logger.exe

clean:
	rm -f ./tests/test_logger.exe

