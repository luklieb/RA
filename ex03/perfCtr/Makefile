CXX = icc
CXXFLAGS = -Wall -Wextra -Wshadow -O3

INCLUDES =
LDFLAGS =
LIBS =


# likwid
CXXFLAGS += -pthread -DLIKWID_PERFMON
INCLUDES += -I/apps/likwid/system/include/
LDFLAGS += -L/apps/likwid/system/lib/
LIBS += -llikwid

TARGET = perfCtr
OBJS = $(TARGET).o

all: $(TARGET)

$(TARGET): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

$(TARGET).o: $(TARGET).c  Makefile
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $(TARGET).c

clean:
	@$(RM) -rf *.o $(TARGET)
