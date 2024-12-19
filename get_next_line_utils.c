/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleriche <cleriche@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:49:23 by cleriche          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:54 by cleriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	size_t	src_len;
	size_t	i;

	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*array;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	array = malloc(s_len + 1);
	if (!array)
		return (NULL);
	ft_strlcpy(array, s, s_len + 1);
	return (array);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*array;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	s1_len = ft_strlen(s1);
	array = malloc(s1_len + s2_len + 1);
	if (!array)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_strlcpy(array, s1, s1_len + 1);
	if (s2)
		ft_strlcpy(array + s1_len, s2, s2_len + 1);
	free((char *)s1);
	return (array);
}
/*char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*array;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	array = malloc(s1_len + s2_len + 1);
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, s1_len + 1);
	ft_strlcpy(array + s1_len, s2, s2_len + 1);
	return (array);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (ft_strdup(s2));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}*/

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == 0)
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
