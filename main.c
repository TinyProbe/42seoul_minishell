/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/11 18:41:00 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);
static void	release(t_db *db);

int	main(void)
{
	t_db	db;

	init(&db);
	minish(&db);
	release(&db);
	exit(0);
}

static void	init(t_db *db)
{
	db->proc_len = ft_strcpy(db->proc, "minish");
	db->cmd = NULL;
	db->cmd_len = 0;
	getcwd(db->cwd, CWD_MAX);
	db->cwd_len = ft_strlen(db->cwd);
	db->sigstat = PROCCMD;
	sigtoggle(db);
}

static void	release(t_db *db)
{
	if (db->cmd)
		free(db->cmd);
	rl_clear_history();
}
