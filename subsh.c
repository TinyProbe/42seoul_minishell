/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:15:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/11 18:54:58 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	parse(t_db *db);
static void	error(t_db *db);
static void	exec(t_db *db);

void	subsh(t_db *db)
{
	if (parse(db))
		error(db);
	else
		exec(db);
}

static int	parse(t_db *db)
{
	if (check(db))
		return (-1);
	return (0);
}

static int	check(t_db *db)
{
	(void) db;
	return (0);
}

static void	error(t_db *db)
{
	(void) db;
}

static void	exec(t_db *db)
{
	write(1, db->cmd, db->cmd_len);
	write(1, "\n", ft_min(db->cmd_len, 1));
}
