CXX = icc

INCLUDES =
LDFLAGS =
LIBS =

target = main

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = 
CXXFLAGS = -O3 -xHost

$(target): draw_grid.o jacobi_avx.o jacobi_avx_blocked.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
main.o: main.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^ 
jacobi_avx.o: jacobi_avx.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^ 
draw_grid.o: draw_grid.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^
jacobi_avx_blocked.o: jacobi_avx_blocked.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) $(target)
