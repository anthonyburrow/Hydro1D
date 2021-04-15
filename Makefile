CXX = g++
CXXFLAGS =

BIN_DIR = ./bin
SRC_DIR = ./src

NAME = Hydro1D
TARGET = $(BIN_DIR)/$(NAME)

SRC = $(NAME) Hydro initialize physics io
SRC_LIST = $(addprefix $(SRC_DIR)/, $(SRC))

_OBJ_LIST = $(addsuffix .o, $(SRC))
OBJ_LIST = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

# Create executable from objects
$(TARGET): $(OBJ_LIST)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Because "main" cpp does not have a header file
$(TARGET).o: $(SRC_DIR)/$(NAME).cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile all other objects objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

clean:
	$(RM) $(BIN_DIR)/*.o $(TARGET)
