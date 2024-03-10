NAME = pipex
NAMEB = pipex_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = Mandatory/pipex_main.c Mandatory/child_proses.c Mandatory/free_error.c ./utils/ft_split.c \
	./utils/ft_strjoin.c ./utils/ft_strncmp.c ./utils/ft_calloc.c ./utils/ft_bzero.c \
	./utils/ft_substr.c ./utils/ft_strlen.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c \
	./utils/ft_split_s_tab.c \

SRCB = bonus/pipex_main_bonus.c bonus/free_error_bonus.c ./utils/ft_split.c ./utils/ft_strjoin.c \
	./utils/ft_strncmp.c bonus/child_proses_bonus.c ./utils/ft_calloc.c ./utils/ft_bzero.c \
	./utils/ft_substr.c ./utils/ft_strlen.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c \
	./utils/ft_putstr_fd.c ./gnl_bonus/get_next_line_utils.c ./gnl_bonus/get_next_line.c \
	./utils/ft_split_s_tab.c \

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