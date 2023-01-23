/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:51:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 05:22:06 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	subsh2(t_db *db);

void	program(t_db *db)
{
	if (db->len)
		subsh(db);
	else if (db->ac && !ft_strcmp(db->av[0], "echo"))
		echo(db);
	else if (db->ac && !ft_strcmp(db->av[0], "cd"))
		cd(db);
	else if (db->ac && !ft_strcmp(db->av[0], "pwd"))
		pwd(db);
	else if (db->ac && !ft_strcmp(db->av[0], "export"))
		export__(db);
	else if (db->ac && !ft_strcmp(db->av[0], "unset"))
		unset(db);
	else if (db->ac && !ft_strcmp(db->av[0], "env"))
		env(db);
	else if (db->ac && !ft_strcmp(db->av[0], "exit"))
		exit__(db);
	else if (db->ac && db->av[0][0] == '(')
		subsh2(db);
	else if (db->ac && db->av[0][0] == '.')
		exec_file(db);
}

static void	subsh2(t_db *db)
{
	db->len = ft_strlen(db->av[0]) - 2;
	ft_memcpy(db->cmd, db->av[0] + 1, db->len);
	subsh(db);
}
