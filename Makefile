NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = pipex_main.c ft_split.c ft_strjoin.c ft_strncmp.c \
	child_proses.c ft_calloc.c ft_bzero.c  ft_substr.c \
	ft_strlen.c \

OBJ = $(SRC:.c=.o)

all:$(NAME)


$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
%.o:%.c pipex.h
	$(CC) $(FLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all 
