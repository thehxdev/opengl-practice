include ../../config.mk

SRC_FILES = main.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
BIN = a.out

$(BIN): $(OBJ_FILES) $(LIBCOMMON)
	$(CXX) $(LDFLAGS) -o $(BIN) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o $(BIN)
