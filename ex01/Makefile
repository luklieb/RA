CXX = gcc

INCLUDES =
LDFLAGS =
LIBS =

target = main

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = 
CXXFLAGS = -O3

$(target): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

.PHONY: clean
clean:
	rm -f $(obj) $(target)
