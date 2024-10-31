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

int	ft_refill_buffer(char *buffer, char *remains)
{
	size_t	i;

	i = 0;
	while (remains[i] != '\0')
	{
		buffer[i] = remains[i];
		remains[i] = 0;
		i++;
	}
	buffer[i] = '\0';
	return (1);
}

char	*ft_rearrange_remains(char *remains, char *pos)
{

}

char	*ft_get_line(char *old, char *buf) // func2
{
	char	*new;
	char	*new_buf;
	char	*new_line_pos;
	size_t	buffer_len;

	new_line_pos = ft_strchr(buf, '\n');
	if (new_line_pos)
		buffer_len = new_line_pos - buf + 1;
	else
		buffer_len = ft_strlen(buf);
	new_buf = ft_substr(buf, 0, buffer_len);
	if (!new_buf)
		return (NULL);
	new = ft_strjoin(old, new_buf);
	free(new_buf);
	return (new);
}

char	*get_next_line(int fd) // func3
{
	char		buffer[BUFFER_SIZE + 1];
	char		*total_line;
	static char *remains = NULL;
	int			bytes_read;

	if (fd < 0 || ft_set_data(&total_line) || ft_set_data(&remains))
		return (NULL);
	if (remains[0] != '\0')
	{
		ft_refill_buffer(buffer, remains);
		total_line = ft_get_line(total_line, buffer);
	}
	

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

	char *line;

	
	

	close(fd);
}
