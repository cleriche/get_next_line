/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleriche <cleriche@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:48:53 by cleriche          #+#    #+#             */
/*   Updated: 2024/12/18 14:20:37 by cleriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 42

size_t  ft_strlen(const char *str)
{
        printf("ft_strlen start");
	size_t     i;
	
	if (!str)
		return (0);
        i = 0;
        while (str[i])
                i++;
	printf("ft_strlen end");
        return (i);
}

size_t  ft_strlcpy(char *dest, const char *src, size_t size)
{
        printf("ft_strlcpy start");
	size_t  src_len;
        size_t  i;

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
	printf("ft_strlcpy end");
        return (src_len);
}

char    *ft_strdup(const char *s)
{
        printf("ft_strdup start");
	size_t          s_len;
        char      *array;

        if (s == NULL)
                return (NULL);
        s_len = ft_strlen(s);
        array = malloc(s_len + 1);
        if (!array)
                return (NULL);
        ft_strlcpy(array, s, s_len + 1);
	printf("ft_strdup end");
        return (array);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *array;
        size_t  s1_len;
        size_t  s2_len;

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

char    *ft_strchr(const char *s, int c)
{
        size_t     i;

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

char	*ft_find_newline(char* stash)
{
	if (!stash)
		return (NULL);
	return (ft_strchr(stash, '\n'));
}

char	*ft_extract_entire_line(char *stash, char *newline_pos)
{
	size_t	line_len;
	char	*line;
	
	if (!stash)
		return (NULL);
	if (newline_pos)
	{
		line_len = newline_pos - stash + 1;
		line = malloc(line_len + 1);
		if (!line)
			return (NULL);
		ft_strlcpy(line, stash, line_len + 1);
	}
	else
		line = ft_strdup(stash);
	return (line);
}

void	ft_update_stash(char **stash, char *newline_pos)
{
	char	*remaining;

	if (!stash || !(*stash))
		return;
	if(newline_pos)
	{
		remaining = ft_strdup(newline_pos + 1);
		if (!remaining)
			return;
		free(*stash);
		*stash = remaining;
	}
	else
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*extract_line_from_stash(char **stash)
{
	char	*newline_pos;
	char	*line;
	
	if (!stash || !(*stash))
		return (NULL);

	newline_pos = ft_find_newline(*stash);
	line = ft_extract_entire_line(*stash, newline_pos);
	ft_update_stash(stash, newline_pos);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*line;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	stash = NULL;	
	if (fd < 0 || BUFFER_SIZE <= 0)// || read(fd, &line, 0) < 0)
		return (NULL);
	printf("entering get_next_line.\n");
	while (!(line == extract_line_from_stash(&stash)) &&
		(bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		printf("read %ld bytes.\n", bytes_read);
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}	
	return (line);
}

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;
	
	if (argc != 2)
	{
		printf("Usage: %s <file_name>\n", argv[0]);
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	printf("file opened succesfully.\n");
	
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line read: %s\n", line);
		free(line);
	}

	printf("finished reading file>\n");
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}
