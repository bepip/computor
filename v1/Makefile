NAME = computor

CPP = c++

INC = -I./includes/


FLAGS = -Werror -Wextra -Wall -g
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
SRC_FILES = main.cpp Parser.cpp computor.cpp Complex.cpp display.cpp

SRC = $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
	 

ifdef TEST
	FLAGS += -DTEST=1
endif

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CPP) $(FLAGS) $(INC) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CPP) $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

test:
	make all TEST=1

re: fclean all
