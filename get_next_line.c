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
	if (*data == NULL)
	{
		*data = (char *) malloc(sizeof(char));
		if (*data)
			**data = '\0';
		else
			return (1);
	}
	return (0);
}

char	*ft_update_value(char *old)  // func2
{
	size_t	len;
	char	*new_line_pos;
	char	*new;

	if (old == NULL)
		return (ft_strdup(""));
	new_line_pos = ft_strchr(old, '\n');
	if (new_line_pos == NULL)
	{
		free(old);
		return (ft_strdup(""));
	}
	new_line_pos++;
	len = ft_strlen(old) - (new_line_pos - old);
	new = ft_substr(new_line_pos, 0, len);
	free(old);
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_get_the_line(char *old, char *src) // func3
{
	char	*new;
	char	*new_src;
	char	*new_line_pos;

	new_line_pos = ft_strchr(src, '\n');
	if (new_line_pos)
		new_src = ft_substr(src, 0, new_line_pos - src + 1);
	else
		new_src = ft_substr(src, 0, ft_strlen(src));
	if (!new_src)
		return (NULL);
	new = ft_strjoin(old, new_src);
	free(new_src);
	if (!new)
		return (NULL);
	free(old);
	return (new);
}

char	*get_next_line(int fd) // func4
{
	char		buffer[BUFFER_SIZE + 1];
	char		*total_line;
	static char *remains = NULL;
	int			bytes_read;

	total_line = NULL;
	bytes_read = 1;
	if (fd < 0 || ft_set_data(&total_line) || ft_set_data(&remains))
		return (NULL);
	if (remains[0] != '\0' && remains)
	{
		total_line = ft_get_the_line(total_line, remains);
		remains = ft_update_value(remains);
	}
	while (!ft_strchr(total_line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		total_line = ft_get_the_line(total_line, buffer);
	}
	if (remains[0] == '\0')
		remains = ft_update_value(&buffer);
	return (total_line);
}

/*deleted part*/


int main()
{
	int fd = open("deneme.txt", O_RDWR, 0666);

	char *line = ft_strdup("umut");
	char *line2;
	char buf[] = "enes";

	ft_set_data(&line2);

	printf("%d", line2[0]);
 
	close(fd);
}
