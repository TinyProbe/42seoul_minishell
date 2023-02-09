/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:22:02 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 01:10:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	rein(t_a *a);
static void	heredoc(t_a *a, t_i32 i);
static void	reout(t_a *a);

void	redirect(t_a *a)
{
	rein(a);
	reout(a);
}

static void	rein(t_a *a)
{
	t_i32	i;

	i = 0;
	while (i < a->ri_l)
	{
		if (a->fd[STDIN__] > STDERR__)
			close(a->fd[STDIN__]);
		if (ft_strlen(a->ri[i]) == 1)
			a->fd[STDIN__] = open(a->ri[i + 1], O_RDONLY);
		else
			heredoc(a, i);
		if (a->fd[STDIN__] == -1)
		{
			a->errn = ERR_FILEPATH;
			a->erra = a->ri[i + 1];
			error(a);
		}
		i += 2;
	}
}

static void	heredoc(t_a *a, t_i32 i)
{
	t_i8	*s;
	t_i32	fd[2];

	pipe(fd);
	while (TRUE)
	{
		s = readline("> ");
		if (!ft_strcmp(s, a->ri[i + 1]))
			break ;
		write(fd[1], s, ft_strlen(s));
		write(fd[1], "\n", 1);
		free(s);
	}
	free(s);
	close(fd[1]);
	a->fd[STDIN__] = fd[0];
}

static void	reout(t_a *a)
{
	t_i32	i;

	i = 0;
	while (i < a->ro_l)
	{
		if (a->fd[STDOUT__] > STDERR__)
			close(a->fd[STDOUT__]);
		if (ft_strlen(a->ro[i]) == 1)
			a->fd[STDOUT__] = open(
					a->ro[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			a->fd[STDOUT__] = open(
					a->ro[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (a->fd[STDIN__] == -1)
		{
			a->errn = ERR_FILEFAIL;
			a->erra = a->ro[i + 1];
			error(a);
		}
		i += 2;
	}
}
