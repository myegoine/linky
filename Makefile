# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable name
TARGET = Linky

# Source files
SRCS = Linky.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
    $(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
    $(RM) $(OBJS) $(TARGET)
