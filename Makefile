# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 16:32:50 by aneumann          #+#    #+#              #
#    Updated: 2024/07/25 13:12:13 by aneumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

NAME_BONUS	=	pipex

SRC		=	pipex.c path.c 

SRC_BONUS	=		here_doc_bonus.c pipex_bonus.c path_bonus.c

LIBFT		=	libft/libft.a

OBJ		=	$(SRC:.c=.o)

OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

CC		=	cc

RM		=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -g3

$(NAME):	$(OBJ)
			make -C ./libft
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

all:		$(NAME)

$(NAME_BONUS):	$(OBJ_BONUS)
			make -C ./libft
			$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT)

bonus:		$(NAME_BONUS)

clean:		
			make clean -C libft
			${RM} $(OBJ) $(OBJ_BONUS)

fclean:		clean
			make fclean -C libft
			${RM} $(NAME) $(NAME_BONUS) $(OBJ) $(OBJ_BONUS)

re:		fclean all bonus

PHONY:		all bonus clean fclean re
