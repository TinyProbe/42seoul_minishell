/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:34:07 by tkong             #+#    #+#             */
/*   Updated: 2023/01/22 22:18:29 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	repl_wild(t_db *db)
{
	DIR	*dir;

	recwd(db);
	dir = opendir(db->cwd);

	closedir(dir);
}
