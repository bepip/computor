NAME = computor
TEST_NAME = tester

CPP = c++

INC = -I./includes/


FLAGS = -Werror -Wextra -Wall -Wpedantic -Wconversion -g -O3 -std=c++17
TEST_FLAGS = -DTEST=1
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
TEST_OBJ_DIR = ./test_objs/
SRC_FILES = main.cpp Parser.cpp computor.cpp display.cpp Complex.cpp test.cpp

SRC = $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
TEST_OBJS = $(addprefix $(TEST_OBJ_DIR), $(SRC_FILES:.cpp=.o))
	 
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CPP) $(FLAGS) $(INC) $(OBJS) -o $(NAME)

test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJ_DIR) $(TEST_OBJS)
	$(CPP) $(FLAGS) $(INC) $(TEST_OBJS) -o $(TEST_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CPP) $(FLAGS) $(INC) -c $< -o $@

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CPP) $(FLAGS) $(TEST_FLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(TEST_NAME)


re: fclean all
