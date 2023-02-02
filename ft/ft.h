/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:39:05 by tkong             #+#    #+#             */
/*   Updated: 2023/02/02 15:44:18 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stdlib.h>
# include <unistd.h>

typedef float				t_f32;
typedef double				t_f64;
typedef char				t_i8;
typedef short				t_i16;
typedef int					t_i32;
typedef long long			t_i64;
typedef long int			t_isize;
typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;
typedef unsigned long long	t_u64;
typedef unsigned long int	t_usize;
typedef char				t_bool;

# define TRUE		1
# define FALSE		0
# define STDIN__	0
# define STDOUT__	1
# define STDERR__	2

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define MAX_FILE 10000
# define MAX_LEN 1000000

# define CODE_SIZE	256

typedef struct s_buf
{
	t_i8	buf[BUFFER_SIZE];
	t_i32	idx;
	t_i32	len;
	t_i32	fd;
}	t_buf;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
typedef struct s_node
{
	struct s_node	*l;
	struct s_node	*r;
	void			*e;
}	t_node;
typedef struct s_bdll
{
	t_node	*hd;
	t_i32	len;
}	t_bdll;

void	ft_putchar_fd(t_i8 c, t_i32 fd);
void	ft_putendl_fd(const t_i8 *s, t_i32 fd);
void	ft_putstr_fd(const t_i8 *s, t_i32 fd);
void	ft_putnbr_fd(t_i32 n, t_i32 fd);
t_bool	ft_isalnum(t_i32 c);
t_bool	ft_isalpha(t_i32 c);
t_bool	ft_isascii(t_i32 c);
t_bool	ft_isdigit(t_i32 c);
t_bool	ft_isprint(t_i32 c);
t_bool	ft_isspace(t_i32 c);
t_bool	ft_islower(t_i32 c);
t_bool	ft_isupper(t_i32 c);
void	ft_lstadd_back(t_list **lst, t_list *new_);
void	ft_lstadd_front(t_list **lst, t_list *new_);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
t_i32	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	*ft_memchr(const void *s, t_i32 c, size_t n);
void	*ft_memset(void *s, t_i32 c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
t_i32	ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const t_i8 *s);
t_i8	*ft_strchr(const t_i8 *s, t_i32 c);
t_i8	*ft_strrchr(const t_i8 *s, t_i32 c);
t_i8	*ft_strnstr(const t_i8 *big, const t_i8 *little, size_t len);
t_i32	ft_strcmp(const t_i8 *s1, const t_i8 *s2);
t_i32	ft_strncmp(const t_i8 *s1, const t_i8 *s2, size_t n);
size_t	ft_strcpy(t_i8 *dst, const t_i8 *src);
size_t	ft_strlcpy(t_i8 *dst, const t_i8 *src, size_t size);
size_t	ft_strlcat(t_i8 *dst, const t_i8 *src, size_t size);
void	ft_striteri(t_i8 *s, void (*f)(t_u32, t_i8 *));
t_i8	*ft_strmapi(t_i8 const *s, t_i8 (*f)(t_u32, t_i8));
t_i8	*ft_strdup(const t_i8 *s1);
t_i8	*ft_strndup(const t_i8 *s1, size_t n);
t_i8	*ft_strjoin(t_i8 const *s1, t_i8 const *s2);
t_i8	*ft_strtrim(t_i8 const *s1, t_i8 const *set);
t_i32	ft_strdel(t_i8 *dst, const t_i8 *set);
t_i8	*ft_substr(t_i8 const *s, t_u32 start, size_t len);
t_i8	**ft_split(t_i8 const *s, t_i8 c);
void	ft_sort_i8(t_i8 *arr, t_i32 begin, t_i32 end);
void	ft_sort_i16(t_i16 *arr, t_i32 begin, t_i32 end);
void	ft_sort_i32(t_i32 *arr, t_i32 begin, t_i32 end);
void	ft_sort_i64(t_i64 *arr, t_i32 begin, t_i32 end);
void	ft_sort_u8(t_u8 *arr, t_i32 begin, t_i32 end);
void	ft_sort_u16(t_u16 *arr, t_i32 begin, t_i32 end);
void	ft_sort_u32(t_u32 *arr, t_i32 begin, t_i32 end);
void	ft_sort_u64(t_u64 *arr, t_i32 begin, t_i32 end);
void	ft_sort_f32(t_f32 *arr, t_i32 begin, t_i32 end);
void	ft_sort_f64(t_f64 *arr, t_i32 begin, t_i32 end);
void	ft_swap(void *a, void *b, size_t siz);
void	ft_reverse(void *arr, t_i32 begin, t_i32 end, size_t siz);
t_i32	ft_tolower(t_i32 c);
t_i32	ft_toupper(t_i32 c);
t_i32	ft_stoi(const t_i8 *str);
t_i32	ft_atoi(const t_i8 *str);
t_i8	*ft_itoa(t_i32 n);
t_f64	ft_abs(t_f64 n);
t_f64	ft_max(t_f64 a, t_f64 b);
t_f64	ft_min(t_f64 a, t_f64 b);
t_u64	ft_gcd(t_u64 a, t_u64 b);
t_u64	ft_lcm(t_u64 a, t_u64 b);
t_u64	ft_fact(t_u64 n);
t_f64	ft_pow(t_f64 n, t_u64 indices);
t_u64	ft_fibo(t_u64 idx);
t_f64	ft_sqrt(t_f64 n);
t_i32	ft_isprime(t_u64 n);
t_i32	ft_printf(const t_i8 *format, ...);
t_i8	*ft_gnl(t_i32 fd);
void	ft_pushf(t_bdll *bdll, void *e);
void	ft_pushb(t_bdll *bdll, void *e);
void	*ft_popf(t_bdll *bdll);
void	*ft_popb(t_bdll *bdll);
void	*ft_popat(t_bdll *bdll, t_i32 idx);
void	*ft_front(t_bdll *bdll);
void	*ft_back(t_bdll *bdll);
t_node	*ft_search(t_bdll *bdll, t_i32 idx);
void	*ft_at(t_bdll *bdll, t_i32 idx);
void	*ft_setat(t_bdll *bdll, t_i32 idx, void *e);

#endif
