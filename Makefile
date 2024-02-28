NAME = pipex
CC = cc -g
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = pipex_main.c ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/ft_strncmp.c \
	child_proses.c ./utils/ft_calloc.c ./utils/ft_bzero.c  ./utils/ft_substr.c \
	./utils/ft_strlen.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c \

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
