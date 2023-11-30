BIN := tvg-test

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Werror
LDFLAGS := -lthorvg -lSDL2_image -lSDL2

ALL: $(BIN)
.PHONY: clean

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ) $(BIN)
