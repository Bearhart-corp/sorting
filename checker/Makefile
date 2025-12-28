# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/27 14:48:13 by etaboure          #+#    #+#              #
#    Updated: 2025/12/28 15:48:11 by etaboure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# variable decalaration
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
NAME = checker

#lst of src files
SRC =	checker.c \
		checker_utils.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \
		../push_swap/push_swap_helper.c \
		../push_swap/push_swap_stk.c \
		../push_swap/cocktail.c \
		../push_swap/helper.c

#list of obj files
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c 
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re