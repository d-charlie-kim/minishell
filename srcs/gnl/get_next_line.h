/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:19:37 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 14:32:52 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define BUFFER_SIZE 5

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

int		get_next_line(int fd, char **line);
int		newline_check(char *s);
int		put_save_in_temp(char **temp, char **save);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
int		zero_or_error(char **line, char *temp, int ret);
int		error_free(char *first, char *second);

#endif
