TARGET = imageBMP

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra 

INCLUDES = bmp.h gaussfilter.h image.h
SOURCES = bmp.cpp gaussfilter.cpp image.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f $(TARGET) $(OBJECTS)