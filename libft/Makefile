NAME		=	libft.a

SRC			= ft_error.c ft_split.c ft_strjoin.c ft_strchr.c ft_strlen.c ft_strnstr.c\
				ft_strncmp.c ft_strdup.c get_next_line.c get_next_line_utils.c

CFLAGS		= -Wall -Wextra -Werror -g3

INCLUDE = libft.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re	
