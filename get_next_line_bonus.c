/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleriche <cleriche@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:39:18 by cleriche          #+#    #+#             */
/*   Updated: 2025/01/13 09:14:28 by cleriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
/*#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>*/

char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, i + 1);
	return (line);
}

char	*update_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = malloc(ft_strlen(&stash[i]) + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	j = -1;
	while (stash[i])
		new_stash[++j] = stash[i++];
	new_stash[++j] = '\0';
	free(stash);
	return (new_stash);
}

char	*init_and_check(char *stash)
{
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	return (stash);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	stash = init_and_check(stash);
	if (!stash)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	stash[fd] = read_file(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = update_stash(stash[fd]);
	return (line);
}

/*int process_file(const char *filename)
{
    int fd;
    char *line;
    int line_number = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    printf("Reading file: %s\n", filename);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_number, line);
        if (line[0] != '\0' && line[ft_strlen(line) - 1] != '\n')
            printf("\n");
        free(line);
    }
    printf("\n");

    close(fd);
    return (0);
}

int main(int argc, char **argv)
{
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1> [file2] [file3] ...\n", argv[0]);
        return (1);
    }

    for (i = 1; i < argc; i++)
    {
        if (process_file(argv[i]) != 0)
        {
            fprintf(stderr, "Error processing file: %s\n", argv[i]);
        }
    }

    return (0);
}*/
