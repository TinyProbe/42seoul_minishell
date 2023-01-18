/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:22:02 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 03:54:00 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	rein(t_db *db);
static void	heredoc(t_db *db);
static void	reout(t_db *db);

void	redirect(t_db *db)
{
	rein(db);
	reout(db);
}

static void	rein(t_db *db)
{
	t_i32	i;

	i = 0;
	while (i < db->rein_len)
	{
		if (db->fd[STDIN__] > STDERR__)
			close(db->fd[STDIN__]);
		if (ft_strlen(db->rein[i]) == 1)
			db->fd[STDIN__] = open(db->rein[i + 1], O_RDONLY);
		else
			heredoc(db);
		if (db->fd[STDIN__] == -1)
		{
			db->errno = ERRNO_FILEPATH;
			error(db);
		}
		i += 2;
	}
}

static void	heredoc(t_db *db)
{
	(void) db;
}

static void	reout(t_db *db)
{
	t_i32	i;

	i = 0;
	while (i < db->reout_len)
	{
		if (db->fd[STDOUT__] > STDERR__)
			close(db->fd[STDOUT__]);
		if (ft_strlen(db->reout[i]) == 1)
			db->fd[STDOUT__] = open(
					db->rein[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			db->fd[STDOUT__] = open(
					db->rein[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (db->fd[STDIN__] == -1)
		{
			db->errno = ERRNO_FILEFAIL;
			error(db);
		}
		i += 2;
	}
}
