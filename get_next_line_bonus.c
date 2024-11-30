/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2024/11/26 13:15:50 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

int	ft_set_d(char **data)
{
	if (!data)
		return (1);
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

char	*ft_free_and_update_repo(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (new);
}

char	*ft_free_and_clean(char **data)
{
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}

char	*ft_get_the_line(char *data)
{
	size_t	len;

	if (!data)
		return (NULL);
	len = 0;
	while (data[len] != '\0')
	{
		if (data[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	return (ft_substr(data, 0, len));
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*repo[1024] = {NULL};
	char		*total_line;
	int			bytes_read;

	if (fd < 0 || ft_set_d(&repo[fd]) || BUFFER_SIZE <= 0)
		return (NULL);
	while (repo[fd] && !ft_strchr(repo[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_free_and_update_repo(&repo[fd], ft_strjoin(repo[fd], buffer));
	}
	if (bytes_read == -1 || !repo[fd] || repo[fd][0] == '\0')
		return (ft_free_and_clean(&repo[fd]));
	total_line = ft_get_the_line(repo[fd]);
	if (!total_line)
		return (ft_free_and_clean(&repo[fd]));
	ft_free_and_update_repo(&repo[fd], ft_update_repo(total_line, repo[fd]));
	return (total_line);
}
