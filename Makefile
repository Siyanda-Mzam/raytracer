# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simzam <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/10 09:17:10 by simzam            #+#    #+#              #
#    Updated: 2016/07/05 11:25:12 by simzam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = rt

FLAG = -Wall -Wextra -Werror -g

SRC =	matrix/matrix1.c matrix/matrix2.c matrix/matrix3.c matrix/matrix4.c \
		utility/utility.c vector/vector1.c \
		vector/vector2.c vector/vector3.c visibility/intersections.c

RM = rm -f

MACMLX = -lm -lmlx -framework OpenGL -framework AppKit
LIXMLX = -lm -lmlx -lXext -lX11

INC = -I /usr/include/X11 -I includes/

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re


all: $(NAME)

%.o: %.c
	@echo "Linking\t\033[33m$@\033[0m"
	@$(CC) $(FLAG) -c -o $@ $^ $(INC)

$(NAME): $(OBJ)
		@echo "Compiled the pieces together..."
ifeq ($(shell uname), Linux)
		@$(CC) $(FLAG) $(OBJ) -o $@ $(INC) $(LIXMLX)
else
		@$(CC) $(FLAG) $(OBJ) -o $@ $(INC) $(MACMLX)
endif
		@echo "\033[32mDone!\033[0m\nManufactured\t\033[31m$@\033[0m..."

clean:
		@echo "Cleaning\t\033[34m$(NAME)\033[m"
		@$(RM) $(OBJ)
		@cd utility/ && $(RM) $(OBJ)
		@cd matrix/ && $(RM) $(OBJ)
		@cd vector/ && $(RM) $(OBJ)
		@cd visibility/ && $(RM) $(OBJ)
		@echo "**********Done!********"

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re