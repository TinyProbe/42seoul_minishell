/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:29:50 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 18:35:22 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void		variable(t_a *a);
static void		check_stack(t_a *a);
static t_i32	setrange(t_a *a);
static t_i32	wildcard(t_a *a);

t_i32	subst(t_a *a)
{
	a->rp[a->rp_l].l = -1;
	a->rp[a->rp_l].r = -1;
	a->rp[a->rp_l].last = -1;
	a->rp[a->rp_l].type = TYPE_NONE;
	a->rp[a->rp_l]._ = NULL;
	a->rp[a->rp_l].len = 0;
	variable(a);
	return (wildcard(a));
}

static void	variable(t_a *a)
{
	while (++(a->rp[a->rp_l].r) < a->tkn[a->ab].len)
	{
		if (a->tkn[a->ab]._[a->rp[a->rp_l].r] == '('
			|| a->tkn[a->ab]._[a->rp[a->rp_l].r] == ')')
			bracket(a, a->tkn[a->ab]._, a->rp[a->rp_l].r);
		else if (a->tkn[a->ab]._[a->rp[a->rp_l].r] == '\'')
			quote(a);
		else if (a->tkn[a->ab]._[a->rp[a->rp_l].r] == '"')
			claw(a);
		check_stack(a);
	}
	apply_rp(a);
}

static void	check_stack(t_a *a)
{
	if (a->stk_l > 1 || (a->stk_l && a->stk[a->stk_l - 1] != '"'))
		return ;
	if (a->rp[a->rp_l].r < a->tkn[a->ab].len - 1
		&& a->tkn[a->ab]._[a->rp[a->rp_l].r] == '$')
	{
		if (a->tkn[a->ab]._[a->rp[a->rp_l].r + 1] == '(')
		{
			a->rp[a->rp_l].l = a->rp[a->rp_l].r;
			a->rp[a->rp_l].last = a->stk_l;
		}
		else
		{
			if (setrange(a))
				return ;
			rp_env(a);
		}
	}
	else if (a->stk_l == a->rp[a->rp_l].last
		&& a->tkn[a->ab]._[a->rp[a->rp_l].r] == ')')
	{
		a->rp[a->rp_l].r++;
		rp_cmd(a);
	}
}

static t_i32	setrange(t_a *a)
{
	if (!ft_isalnum(a->tkn[a->ab]._[a->rp[a->rp_l].r + 1])
		&& a->tkn[a->ab]._[a->rp[a->rp_l].r + 1] != '_'
		&& a->tkn[a->ab]._[a->rp[a->rp_l].r + 1] != '-'
		&& a->tkn[a->ab]._[a->rp[a->rp_l].r + 1] != '?')
		return (-1);
	a->rp[a->rp_l].l = a->rp[a->rp_l].r;
	if (ft_isdigit(a->tkn[a->ab]._[a->rp[a->rp_l].r + 1])
		|| a->tkn[a->ab]._[a->rp[a->rp_l].r + 1] == '?')
	{
		a->rp[a->rp_l].r += 2;
		return (0);
	}
	while (++(a->rp[a->rp_l].r) < a->tkn[a->ab].len)
		if (a->tkn[a->ab]._[a->rp[a->rp_l].r] != '_'
			&& !ft_isalnum(a->tkn[a->ab]._[a->rp[a->rp_l].r]))
			break ;
	return (0);
}

static t_i32	wildcard(t_a *a)
{
	t_i32	i;
	t_i32	amt;

	i = -1;
	amt = 0;
	while (++i < a->tkn[a->ab].len)
	{
		if (a->tkn[a->ab]._[i] == '(' || a->tkn[a->ab]._[i] == ')')
			bracket(a, a->tkn[a->ab]._, i);
		else if (a->tkn[a->ab]._[i] == '\'')
			quote(a);
		else if (a->tkn[a->ab]._[i] == '"')
			claw(a);
		if (a->tkn[a->ab]._[i] == '*' && ++amt && a->stk_l)
			break ;
	}
	a->tkn[a->ab].len = ft_strdel(a->tkn[a->ab]._, "'\"");
	if (i == a->tkn[a->ab].len && amt)
		return (rp_wild(a));
	return (a->errn);
}
