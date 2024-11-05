/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:54:19 by tle-dref          #+#    #+#             */
/*   Updated: 2024/11/05 09:29:31 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
void				*ft_memset(void *pointer, int value, size_t size);
void				ft_bzero(void *pointer, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t size);
void				*ft_memmove(void *dst, const void *src, size_t size);
void				*ft_memchr(const void *ptr, int search, size_t size);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *str, const char *search,
						size_t len);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *src, unsigned int start, size_t len);
char				*ft_strjoin(char const *str1, char const *str2);
char				*ft_strtrim(char const *str, char const *set);
char				**ft_split(char const *str, char c);
char				*ft_itoa(int nb);
char				*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void				ft_striteri(char *str, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char ch, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*get_next_line(int fd);
int					ft_printf(const char *format, ...);
char				*clean_join(char *s1, char *s2);
int					isfullspace(char *str);
int					is_dot_or_slash(char s);
