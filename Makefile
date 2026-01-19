NAME=computor
CPP=c++
FLAGS= -Werror -Wextra -Wall -g
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(FLAGS) -o $(NAME) $(OBJ)

%.o:%.cpp
	$(CPP) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
