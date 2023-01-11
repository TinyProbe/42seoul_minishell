/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:59:09 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:37:10 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../ft.h"
# include <stdarg.h>

# define MAX_SIZE		1000000000

# define FLAG_MINUS		1
# define FLAG_PLUS		2
# define FLAG_SPACE		4
# define FLAG_SHARP		8
# define FLAG_ZERO		16

# define WID_NUM		1
# define WID_STAR		2

# define PREC_DOT		1
# define PREC_NUM		2
# define PREC_STAR		4

# define LEN_H			1
# define LEN_HH			2
# define LEN_L			4
# define LEN_LL			8
# define LEN_J			16
# define LEN_Z			32
# define LEN_T			64
# define LEN_L_UP		128

# define SPEC_D_OR_I	1
# define SPEC_U			2
# define SPEC_O			4
# define SPEC_X			8
# define SPEC_X_UP		16
# define SPEC_F			32
# define SPEC_F_UP		64
# define SPEC_E			128
# define SPEC_E_UP		256
# define SPEC_G			512
# define SPEC_G_UP		1024
# define SPEC_A			2048
# define SPEC_A_UP		4096
# define SPEC_C			8192
# define SPEC_S			16384
# define SPEC_P			32768
# define SPEC_N			65536
# define SPEC_PERCENT	131072

typedef struct s_elem
{
	t_u32	flag;
	t_u32	wid;
	t_u32	prec;
	t_u32	len;
	t_u32	spec;
	t_i32	width;
	t_i32	precis;
	t_i8	res[MAX_SIZE];
	t_i32	begin;
	t_i32	end;
	t_i32	neg;
}	t_elem;

t_i32	ft_vfprintf(const t_i8 *format, va_list ap);
void	set_arg_value(va_list ap, t_elem *info);
t_i32	scan_flag(const t_i8 *form, t_i32 idx, t_elem *info);
t_i32	scan_wid(const t_i8 *form, t_i32 idx, t_elem *info);
t_i32	scan_prec(const t_i8 *form, t_i32 idx, t_elem *info);
t_i32	scan_len(const t_i8 *form, t_i32 idx, t_elem *info);
t_i32	scan_spec(const t_i8 *form, t_i32 idx, t_elem *info);
t_i32	is_flag(t_i32 c);
t_i32	is_wid(t_i32 c);
t_i32	is_prec(t_i32 c);
t_i32	is_len(t_i32 c);
t_i32	is_spec(t_i32 c);
t_i32	is_spec_part1(t_i32 c);
t_i32	is_spec_part2(t_i32 c);
t_i32	check_flag(t_elem *info);
t_i32	check_wid(t_elem *info);
t_i32	check_prec(t_elem *info);
t_i32	check_len(t_elem *info);
t_i32	check_spec(t_elem *info);
t_i32	check_mix_minus(t_elem *info);
t_i32	check_mix_plus(t_elem *info);
t_i32	check_mix_space(t_elem *info);
t_i32	check_mix_sharp(t_elem *info);
t_i32	check_mix_zero(t_elem *info);
void	itodec(t_elem *info, t_i32 i);
void	utodec(t_elem *info, t_u32 u);
void	ulltohex(t_elem *info, t_u64 ull, t_i32 up);
void	ptohex(t_elem *info, void *p);
void	apply_prec(t_elem *info);
void	apply_base(t_elem *info);
void	apply_wid(t_elem *info);
void	apply_sign(t_elem *info);

#endif
