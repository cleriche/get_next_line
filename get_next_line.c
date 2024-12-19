/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleriche <cleriche@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:48:53 by cleriche          #+#    #+#             */
/*   Updated: 2024/12/19 13:52:41 by cleriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find_newline(char *stash)
{
	char	*pos;

	if (!stash)
		return (NULL);
	pos = ft_strchr(stash, '\n');
	return (pos);
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
		return ;
	if (newline_pos)
	{
		remaining = ft_strdup(newline_pos + 1);
		if (!remaining)
			return ;
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
	if (!line)
		return (NULL);
	ft_update_stash(stash, newline_pos);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	ssize_t		bytes_read;

	line = NULL;
	bytes_read = 1;
	printf("start get_next_line\n");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	printf("start while\n");
	buffer = malloc(BUFFER_SIZE + 1);
                if (!buffer)
                        return(NULL);
	while (!line && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		printf("bytes_read = %zd\n", bytes_read);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_strjoin(stash, buffer);
			line = extract_line_from_stash(&stash);
		}
	}
	free(buffer);
	if (!line && stash)
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
	}
	return (line);
}
