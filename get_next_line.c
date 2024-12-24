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

/*static char	*ft_read_and_stash(int fd, char **stash)
{
    char	*buffer;
    char	*temp;
    ssize_t	bytes_read;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        if (!*stash)
            *stash = ft_strdup(buffer);
        else
        {
            temp = ft_strjoin(*stash, buffer);
            free(*stash);
            *stash = temp;
        }
        if (ft_strchr(*stash, '\n'))
            break ;
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    free(buffer);
    return (*stash);
}*/

static char	*ft_read_and_stash(int fd, char **stash)
{
    char	*buffer;
    char	*temp;
    ssize_t	bytes_read;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        if (!*stash)
        {
            *stash = malloc(sizeof(char) * (bytes_read + 1));
            if (!*stash)
                break;
            (*stash)[0] = '\0';
        }
        temp = ft_strjoin(*stash, buffer);
        free(*stash);
        *stash = temp;

        if (ft_strchr(buffer, '\n'))
            break;
    }
    free(buffer);
    return (*stash);
}


static char	*get_line(char **stash)
{
    size_t	len = 0;
    char	*line;

    while ((*stash)[len] && (*stash)[len] != '\n')
        len++;
    if ((*stash)[len] == '\n')
        len++;
    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);
    ft_memcpy(line, *stash, len);
    line[len] = '\0';
    return (line);
}

static void	clean_stash(char **stash)
{
    char	*temp;
    char	*new_start;

    new_start = ft_strchr(*stash, '\n');
    if (!new_start)
    {
        free(*stash);
        *stash = NULL;
        return ;
    }
    new_start++;
    temp = ft_strdup(new_start);
    free(*stash);
    *stash = temp;
}


char	*get_next_line(int fd)
{
    static char	*stash = NULL;
    char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
      if (!stash || !ft_strchr(stash, '\n'))
        stash = ft_read_and_stash(fd, &stash);
    
    if (!stash)
        return (NULL);
    
    
    line = get_line(&stash);
    
    
    clean_stash(&stash);
    
    
    if (stash && !*stash)
    {
        free(stash);
        stash = NULL;
    }
    
    return (line);
}
