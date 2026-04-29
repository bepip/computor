NAME = computor-v2
TEST_NAME = tester

CPP = c++

INC = -Iinclude

FLAGS = -Werror -Wextra -Wall -Wpedantic -Wconversion -g -O3 -std=c++17

SRC_DIR = ./src/
CLI_DIR = cli/
INTERPRETER_DIR = interpreter/
MATHLIB_DIR = mathlib/
COMMON_DIR = common/
TEST_DIR = tests/


OBJ_DIR = obj/

CLI = repl.cpp
INTERPRETER = Lexer.cpp
MATHLIB = 
COMMON = utils.cpp
TEST = lexer_test.cpp main_test.cpp tests_utils.cpp
MAIN = main.cpp

CLI_SRC = $(addprefix ${CLI_DIR}, ${CLI})
INTERPRETER_SRC = $(addprefix ${INTERPRETER_DIR}, ${INTERPRETER})
MATHLIB_SRC = $(addprefix ${MATHLIB_DIR}, ${MATHLIB})
COMMON_SRC = $(addprefix ${COMMON_DIR}, ${COMMON})
TEST_SRC = $(addprefix ${TEST_DIR}, ${TEST})

SRC_FILES = ${MAIN} ${CLI_SRC} ${INTERPRETER_SRC} ${MATHLIB_SRC} ${COMMON_SRC}
TEST_SRC_FILES = ${TEST_SRC} ${CLI_SRC} ${INTERPRETER_SRC} ${MATHLIB_SRC} ${COMMON_SRC}

SRC = $(addprefix ${SRC_DIR}, ${SRC_FILES})
SRC_TEST = $(addprefix ${SRC_DIR}, ${TEST_SRC_FILES})

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
OBJ_TEST = $(addprefix $(OBJ_DIR), $(TEST_SRC_FILES:.cpp=.o))

#================================================================
all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(FLAGS) $(INC) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(FLAGS) $(INC) -c $< -o $@

#================================================================
test: ${TEST_NAME}

${TEST_NAME}: ${OBJ_TEST}
	$(CPP) $(FLAGS) $(INC) $(OBJ_TEST) -o $(TEST_NAME)

$(OBJ_DIR)%.o: $(TEST_SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(FLAGS) $(INC) -c $< -o $@

#================================================================
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -f ${TEST_NAME}

re: fclean all

#================================================================
