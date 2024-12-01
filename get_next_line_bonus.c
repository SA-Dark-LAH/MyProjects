/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharraz <saharraz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:13:14 by saharraz          #+#    #+#             */
/*   Updated: 2024/11/30 10:22:24 by saharraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
			return (free(line), NULL);
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

static char	*get_line_b(char *remain)
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
	i = 0 ;
	while (remain[i] && remain[i] != '\n')
		holder[s++] = remain[i++];
	if (remain[i] == '\n')
		holder[i++] = '\n';
	holder[i] = '\0';
	return (holder);
}

static char	*rest_fornext_b(char *current_line, char *remain)
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
	static char	*remain_data[1024];
	char		*current_line;
	char		*tmp_buffer;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < 1024)
		{
			free(remain_data[fd]);
			remain_data[fd] = NULL;
		}
		return (NULL);
	}
	tmp_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (NULL);
	remain_data[fd] = line_finder(fd, remain_data[fd], tmp_buffer);
	free(tmp_buffer);
	if (!remain_data[fd])
		return (NULL);
	current_line = get_line_b(remain_data[fd]);
	remain_data[fd] = rest_fornext_b(current_line, remain_data[fd]);
	return (current_line);
}
/*int main ()
{
    int fd = open("tst.txt", O_RDONLY);
    int fd2= open("tst2.txt", O_RDONLY);
    int fd3 = open("tst3.txt", O_RDONLY);
    
    int arr[] = {fd,fd2,fd3,fd,fd2,fd3,fd,fd2,fd3,fd3};
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
