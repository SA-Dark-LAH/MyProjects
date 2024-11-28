/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharraz <saharraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:13:14 by saharraz          #+#    #+#             */
/*   Updated: 2024/11/28 12:00:00 by saharraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_finder(int fd, char *remain, char *buff)
{
	int		b_read;
	char	*line;
	char	*temp;

	line = remain;
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read < 0)
			return (free(remain), NULL);
		buff[b_read] = '\0';
		temp = line;
		line = ft_strjoin(line, buff);
		free(temp);
		if (!line)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

static char	*get_line_b(char *remain)
{
	char	*line;
	int		i;

	if (!remain || *remain == '\0')
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	line = malloc(i + (remain[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*rest_fornext_b(char *remain, char *line)
{
	char	*rest;
	int		offset;
	int		i;

	offset = ft_strlen(line);
	if (!remain[offset])
		return (free(remain), NULL);
	rest = malloc(ft_strlen(remain) - offset + 1);
	if (!rest)
		return (free(remain), NULL);
	i = 0;
	while (remain[offset])
		rest[i++] = remain[offset++];
	rest[i] = '\0';
	free(remain);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*remain_data[1024];
	char		*current_line;
	char		*tmp_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	tmp_buffer = malloc(BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (NULL);
	remain_data[fd] = line_finder(fd, remain_data[fd], tmp_buffer);
	free(tmp_buffer);
	if (!remain_data[fd])
		return (NULL);
	current_line = get_line_b(remain_data[fd]);
	remain_data[fd] = rest_fornext_b(remain_data[fd], current_line);
	return (current_line);
}
/*int main ()
{
    int fd = open("tst.txt", O_RDONLY);
    int fd2= open("tst2.txt", O_RDONLY);
    int fd3 = open("tst3.txt", O_RDONLY);
    
    int arr[] = {fd,fd3,fd,fd2,fd};
    char *ptr ;
    int i = 0 ;
    while((ptr = get_next_line(arr[i])) != NULL)
    {
        printf("%s",ptr);
        i++;
        free(ptr);
    }
    close(fd);
}*/