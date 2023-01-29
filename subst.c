/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:29:50 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 17:44:23 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	variable(t_z *z);
static void	check_stack(t_z *z);
static void	setrange(t_z *z);
static void	wildcard(t_z *z);

void	subst(t_z *z)
{
	z->repl[z->repl_len].l = -1;
	z->repl[z->repl_len].r = -1;
	z->repl[z->repl_len].last = -1;
	z->repl[z->repl_len].type = TYPE_NONE;
	z->repl[z->repl_len]._ = NULL;
	z->repl[z->repl_len].len = 0;
	variable(z);
	wildcard(z);
}

static void	variable(t_z *z)
{
	while (++(z->repl[z->repl_len].r) < z->len)
	{
		if (z->tkn[z->ab]._[z->repl[z->repl_len].r] == '('
				|| z->tkn[z->ab]._[z->repl[z->repl_len].r] == ')')
			bracket(z, z->tkn[z->ab]._, z->repl[z->repl_len].r);
		else if (z->tkn[z->ab]._[z->repl[z->repl_len].r] == '\'')
			quote(z);
		else if (z->tkn[z->ab]._[z->repl[z->repl_len].r] == '"')
			claw(z);
		check_stack(z);
	}
	apply_repl(z);
}

static void	check_stack(t_z *z)
{
	if (z->stk_len > 1 || (z->stk_len && z->stk[z->stk_len - 1] != '"'))
		return ;
	if (z->repl[z->repl_len].r < z->tkn[z->ab].len - 1
			&& z->tkn[z->ab]._[z->repl[z->repl_len].r] == '$')
	{
		if (z->tkn[z->ab]._[z->repl[z->repl_len].r + 1] == '(')
		{
			z->repl[z->repl_len].l = z->repl[z->repl_len].r;
			z->repl[z->repl_len].last = z->stk_len;
		}
		else
		{
			setrange(z);
			repl_env(z);
		}
	}
	else if (z->stk_len == z->repl[z->repl_len].last
			&& z->tkn[z->ab]._[z->repl[z->repl_len].r] == ')')
	{
		z->repl[z->repl_len].r++;
		repl_cmd(z);
	}
}

static void	setrange(t_z *z)
{
	z->repl[z->repl_len].l = z->repl[z->repl_len].r;
	if (ft_isdigit(z->tkn[z->ab]._[z->repl[z->repl_len].r + 1])
			|| z->tkn[z->ab]._[z->repl[z->repl_len].r + 1] == '?')
	{
		z->repl[z->repl_len].r += 2;
		return ;
	}
	while (++(z->repl[z->repl_len].r) < z->tkn[z->ab].len)
		if (z->tkn[z->ab]._[z->repl[z->repl_len].r] != '_'
				&& !ft_isalnum(z->tkn[z->ab]._[z->repl[z->repl_len].r]))
			break ;
}

static void	wildcard(t_z *z)
{
	t_i32	i;
	t_i32	amt;

	i = -1;
	amt = 0;
	// if (z->buf[0] == '(')
	// 	return ;
	while (++i < z->tkn[z->ab].len)
	{
		if (z->tkn[z->ab]._[i] == '(' || z->tkn[z->ab]._[i] == ')')
			bracket(z, z->tkn[z->ab]._, i);
		else if (z->tkn[z->ab]._[i] == '\'')
			quote(z);
		else if (z->tkn[z->ab]._[i] == '"')
			claw(z);
		if (z->tkn[z->ab]._[i] == '*' && ++amt && z->stk_len)
			break ;
	}
	z->tkn[z->ab].len = ft_strdel(z->tkn[z->ab]._, "'\"");
	if (i == z->tkn[z->ab].len && amt)
		repl_wild(z);
}
