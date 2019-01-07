# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/11 17:02:10 by tblaudez          #+#    #+#              #
#    Updated: 2018/08/20 20:07:09 by tblaudez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
SRC := src/minishell.c src/env_list.c src/built_in.c src/input.c src/utils.c
OBJ := $(SRC:.c=.o)
LIB := libft/libft.a
INCLUDES := includes/
FLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@printf "\n\e[1;31mCréation du binaire \e[0m- %s\n" $(NAME)
	@gcc $(FLAGS) -I $(INCLUDES) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c
	@printf "\e[1;32mCréation des .o \e[0m- %-50s\r" $@
	@gcc $(FLAGS) -I $(INCLUDES) -o $@ -c $<

$(LIB):
	@make -C libft/

clean:
	@rm -f $(OBJ) && \
	make -C libft/ clean

fclean: clean
	@rm -f $(NAME)  && \
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
