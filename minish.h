/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:03:29 by tkong             #+#    #+#             */
/*   Updated: 2023/01/11 17:49:05 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# define PROC_MAX		1024
# define CWD_MAX		4096
# define MINISH_PROMPT	"minish> "
# define WAITCMD		0
# define PROCCMD		1

# include "ft/ft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_db
{
	char	proc[PROC_MAX];
	int		proc_len;
	char	*cmd;
	int		cmd_len;
	char	cwd[CWD_MAX];
	int		cwd_len;
	int		sigstat;
	errno_t	errno;
}	t_db;

void	sigtoggle(t_db *db);
void	sigint(int signo);

void	init(t_db *db);
void	release(t_db *db);
void	minish(t_db *db);
void	subsh(t_db *db);

int		parse(t_db *db);
int		check(t_db *db);

void	exec(t_db *db);

void	error(t_db *db);

#endif
