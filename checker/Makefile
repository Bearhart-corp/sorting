# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/27 14:48:13 by etaboure          #+#    #+#              #
#    Updated: 2025/12/27 17:51:17 by etaboure         ###   ########.fr        #
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

#list of obj files
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re