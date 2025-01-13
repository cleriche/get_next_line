/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleriche <cleriche@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:39:51 by cleriche          #+#    #+#             */
/*   Updated: 2025/01/13 08:48:55 by cleriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	if (!dest || size == 0)
		return (src_len);
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*array;
	size_t	s1_len;
	size_t	s2_len;

	if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	array = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, s1_len + 1);
	ft_strlcpy(array + s1_len, s2, s2_len + 1);
	free(s1);
	return (array);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
