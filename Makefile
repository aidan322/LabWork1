CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -Wpedantic
OBJS = main.o bmp.o
TARGET = lab1

all: labwork1

labwork1: main.o bmp.o
	$(CXX) $(CXXFLAGS) main.o bmp.o -o labwork1

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
