CXX = icc

INCLUDES =
LDFLAGS =
LIBS =

target = main

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = 
CXXFLAGS = -O3 -xHost

$(target): VecSum.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
main.o: main.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^ 
VecSum.o: VecSum.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^ 

.PHONY: clean
clean:
	rm -f $(obj) $(target)
