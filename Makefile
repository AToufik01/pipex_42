NAME = pipex
NAMEB = pipex_bonus
CC = cc -g
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = Mandatory/pipex_main.c ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/ft_strncmp.c \
	Mandatory/child_proses.c ./utils/ft_calloc.c ./utils/ft_bzero.c  ./utils/ft_substr.c \
	./utils/ft_strlen.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c \

SRCB = bonus/pipex_main_bonus.c ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/ft_strncmp.c \
	bonus/child_proses_bonus.c ./utils/ft_calloc.c ./utils/ft_bzero.c  ./utils/ft_substr.c \
	./utils/ft_strlen.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c \

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

all:$(NAME)


$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJB)
	$(CC) $(FLAGS) $(OBJB) -o $(NAMEB)

%.o:%.c pipex.h pipex_bonus.h
	$(CC) $(FLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)
	$(RM) $(OBJB)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMEB)

re : fclean all 
