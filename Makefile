# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 06:26:52 by tkong             #+#    #+#              #
#    Updated: 2023/01/19 03:53:33 by tkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OPT = -Wall -Wextra -Werror -o $(NAME) -lreadline
L_RL = -L/opt/homebrew/Cellar/readline/8.2.1/lib/
I_RL = -I/opt/homebrew/Cellar/readline/8.2.1/include/
# L_RL = -L
# I_RL = -I
LIB = ft/libft.a
INC = minish.h
SRC = main.c\
	  process.c\
	  parent.c\
	  child.c\
	  redirect.c\
	  minish.c\
	  subsh.c\
	  check.c\
	  token.c\
	  execute.c\
	  error.c\
	  util.c\
	  handler.c

ifdef B
	INC = $(patsubst %.h, %_bonus.h, $(INC))
	SRC = $(patsubst %.c, %_bonus.c, $(SRC))
endif

$(NAME): $(LIB) $(INC) $(SRC) Makefile
	cc $(OPT) $(L_RL) $(I_RL) $(SRC) $(LIB)

$(LIB):
	make -sC ft/ all

all: $(NAME)

re: fclean all

clean:
	make -sC ft/ clean

fclean: clean
	rm -rf $(NAME) $(LIB)

bonus:
	make B=1 all

.PHONY: all re clean fclean bonus
