# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 06:26:52 by tkong             #+#    #+#              #
#    Updated: 2023/01/30 12:17:36 by tkong            ###   ########.fr        #
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
	  redirect.c\
	  minish.c\
	  check.c\
	  token.c\
	  valid.c\
	  error.c\
	  execute.c\
	  subst.c\
	  repl_cmd.c\
	  repl_env.c\
	  repl_wild.c\
	  join.c\
	  apply.c\
	  process.c\
	  parent.c\
	  child.c\
	  program.c\
	  subsh.c\
	  echo.c\
	  cd.c\
	  pwd.c\
	  export.c\
	  unset.c\
	  env.c\
	  exit.c\
	  file_exe.c\
	  util.c\
	  util2.c\
	  util3.c\
	  util4.c\
	  handler.c

ifdef B
	INC = $(patsubst %.h, bonus/%_bonus.h, $(INC))
	SRC = $(patsubst %.c, bonus/%_bonus.c, $(SRC))
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
