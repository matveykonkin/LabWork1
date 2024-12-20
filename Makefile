PROJECT=image

IDIR=.
CXX=g++
CXXFLAGS=-I$(IDIR) -std=c++17

ODIR=obj
LDIR=../lib

LIBS=-lm

DEPS = image.h turnimage.h kernel.h

OBJ = main.o image.o rightturnimage.o leftturnimage.o kernel.o

.PHONY: default

default: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

main.o: main.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

Image.o: image.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

RightTurnImage.o: rightturnimage.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

LeftTurnImage.o: leftturnimage.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

Kernel.o: kernel.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(PROJECT)