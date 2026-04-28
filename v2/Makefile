NAME = computor-v2

CPP = c++

INC = -Iinclude

FLAGS = -Werror -Wextra -Wall -Wpedantic -Wconversion -g -O3 -std=c++17

SRC_DIR = ./src/
CLI_DIR = cli/
INTERPRETER_DIR = interpreter/
MATHLIB_DIR = mathlib/
COMMON_DIR = common/


OBJ_DIR = obj/

CLI = repl.cpp
INTERPRETER = 
MATHLIB = 
COMMON = utils.cpp
MAIN = main.cpp

CLI_SRC = $(addprefix ${CLI_DIR}, ${CLI})
INTERPRETER_SRC = $(addprefix ${INTERPRETER_DIR}, ${INTERPRETER})
MATHLIB_SRC = $(addprefix ${MATHLIB_DIR}, ${MATHLIB})
COMMON_SRC = $(addprefix ${COMMON_DIR}, ${COMMON})

SRC_FILES = ${MAIN} ${CLI_SRC} ${INTERPRETER_SRC} ${MATHLIB_SRC} ${COMMON_SRC}
SRC = $(addprefix ${SRC_DIR}, ${SRC_FILES})

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
	 
all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(FLAGS) $(INC) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
