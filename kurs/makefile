# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Каталоги и файлы
SRCDIR = .
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Файлы и библиотеки
MAIN_OBJ = FileManager.o Error.o Network.o ArgsDecoder.o CryptoManager.o main.o
UNIT_OBJ = FileManager.o Error.o Network.o ArgsDecoder.o CryptoManager.o unit.o

TARGET_MAIN = client
TARGET_UNIT = unit

# Правила
all: $(TARGET_MAIN) $(TARGET_UNIT) clean

$(TARGET_MAIN): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcryptopp

$(TARGET_UNIT): $(UNIT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcryptopp -lUnitTest++

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean
