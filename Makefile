CXX = g++
CXXFLAGS = -g

BIN_DIR = ./bin
SRC_DIR = ./src

# Directories
MAKE_DIRS = $(BIN_DIR) ./output ./doc/figs
MKDIR_P = mkdir -p

.PHONY: directories $(MAKE_DIRS)

directories: $(MAKE_DIRS)

$(MAKE_DIRS):
	$(MKDIR_P) $@

# Target 1
NAME = Hydro1D
TARGET = $(BIN_DIR)/$(NAME)
_SRC1 = $(NAME)
_SRC2 = Hydro initialize physics io
SRC = $(_SRC1) $(_SRC2)

_OBJ_LIST = $(addsuffix .o, $(SRC))
OBJ_LIST = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET): $(OBJ_LIST)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Object recipes
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

all: directories $(TARGET)

TESTS = $(TARGET)

test: directories $(TESTS)

clean:
	$(RM) -r $(BIN_DIR)