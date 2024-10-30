/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/28 12:51:01 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/28 12:51:01 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_set_data(char **data)  // func1
{
	*data = (char *) malloc(sizeof(char));
	if (*data)
		**data = '\0';
	return (*data == NULL);
}

char	*ft_rearrange_remains(char *remains, char *pos)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (pos[i] != '\0')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	while (j < i)
	{
		new[j] = pos[j];
		j++;
	}
	new[j] = '\0';
	free(remains);
	return (new);
}

char	*ft_create_and_free_arr(char *old, char *buffer)  // func2
{
	char 	*new;
	char	*new_buffer;
	size_t	old_str_len;
	size_t	buffer_len;
	size_t	total_len;

	old_str_len = ft_strlen(old);
	buffer_len = ft_strlen(buffer);
	if (buffer[buffer_len] == '\n')
		total_len = old_str_len + buffer_len + 2;
	else
		total_len = old_str_len + buffer_len + 1;
	new = malloc(sizeof(char) * (total_len));
	if (!new)
		return (NULL);
	if (buffer[buffer_len] == '\n')
		new_buffer = ft_substr(buffer, 0, buffer_len + 1);
	else
		new_buffer = ft_substr(buffer, 0, buffer_len);
	new = ft_strjoin(old, new_buffer);

	free(old);
	free(new_buffer);
	return (new);
}

char	*get_next_line(int fd) // func3
{
	char		buffer[BUFFER_SIZE + 1];
	char		*total_line;
	static char *remains = 0;
	int			bytes_read;

	if ((fd < 0 && remains) || ft_set_data(&remains))
		return (NULL);
	ft_set_data(&total_line);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_read] = '\0';
	total_line = ft_create_and_free_arr(total_line, buffer);
	while (!(ft_strchr(buffer, '\n')) && bytes_read != 0)
	{
		total_line = ft_create_and_free_arr(total_line, buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
	}
	remains = ft_rearrange_remains(remains, ft_strchr(buffer, '\n'));
	return (total_line);
}
/*deleted part*/

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(s1);
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int main()
{
	int fd = open("deneme.txt", O_RDWR, 0666);

	char *result = get_next_line(fd);
	// char *result2 = get_next_line(fd);
	
	printf("result is: %s", result);+

	close(fd);
}