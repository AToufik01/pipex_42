NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = pipex_main.c
OBJ = $(SRC:.c=.o)

all:$(NAME)


$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
%.o:%.c 
	$(CC) $(FLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all 
