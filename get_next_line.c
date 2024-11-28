/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharraz <saharraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:20:06 by saharraz          #+#    #+#             */
/*   Updated: 2024/11/28 16:22:54 by saharraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_finder(int fd, char *remain, char *buff)
{
	int		b_read;
	char	*line;
	char	*memo_holder;

	line = remain;
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read < 0)
			return (NULL);
		buff[b_read] = '\0';
		memo_holder = line;
		if (!line)
			line = ft_strjoin("", buff);
		else
			line = ft_strjoin(line, buff);
		free(memo_holder);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (b_read == 0 && (!line || *line == '\0'))
		return (free(line), NULL);
	return (line);
}

static char	*get_line_m(char *remain)
{
	char	*holder;
	int		i;
	int		s;

	i = 0 ;
	s = 0 ;
	if (!remain)
		return (NULL);
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[1])
		holder = malloc(2);
	else if (!remain[i])
		holder = malloc(i + 1);
	else
		holder = malloc(i + 2);
	if (!holder)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		holder[s++] = remain[i++];
	if (remain[i] == '\n')
		holder[i++] = '\n';
	holder[i] = '\0';
	return (holder);
}

static char	*rest_for_next(char *current_line, char *remain)
{
	int		index ;
	char	*rest;
	int		i;

	index = ft_strlen(current_line);
	i = 0 ;
	if (!remain || !remain[index])
	{
		free(remain);
		return (NULL);
	}
	rest = malloc(ft_strlen(remain) - index + 1);
	if (!rest)
	{
		free(remain);
		return (NULL);
	}
	while (remain[index])
		rest[i++] = remain[index++];
	rest[i] = '\0';
	free(remain);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*remain_data;
	char		*current_line;
	char		*tmp_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remain_data);
		remain_data = NULL;
		return (NULL);
	}
	tmp_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (NULL);
	remain_data = line_finder(fd, remain_data, tmp_buffer);
	free(tmp_buffer);
	if (!remain_data)
		return (NULL);
	current_line = get_line_m(remain_data);
	remain_data = rest_for_next(current_line, remain_data);
	return (current_line);
}
/*int main()
{
    int fd = open("tst.txt", O_RDWR); // Open a test file for reading.
    char *ptr;

    // Read and print lines until no more lines are returned.
    while ((ptr = get_next_line(fd)) != NULL)
    {
        printf("%s", ptr);
		if(ptr[1] == '\0')
		printf("/0");// Print the current line.
        free(ptr);         // Free the line after use.
    }
    //printf("%s",ptr);
    close(fd);             // Close the file descriptor.
    return 0;
}*/
