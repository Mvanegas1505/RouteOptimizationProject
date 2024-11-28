CXX = g++
CXXFLAGS = -Wall -Wextra -O2
LDFLAGS =

# Intenta usar C++17, si no está disponible, usa C++11
ifeq ($(shell $(CXX) -std=c++17 -E -x c++ - < /dev/null > /dev/null 2>&1 && echo yes),yes)
    CXXFLAGS += -std=c++17
else
    CXXFLAGS += -std=c++11
endif

SRCS = Grafo.cpp Parcial.cpp EvaluarParcial.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
TARGET = evaluador

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

-include $(DEPS)

.PHONY: all clean run