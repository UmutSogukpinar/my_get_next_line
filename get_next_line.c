/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2024/11/02 16:27:02 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_set_data(char **data)
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

char	*ft_update_repo(char *old)
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

char	*ft_update_wbuf(char *old)
{
	size_t	len;
	char	*new_line_pos;
	char	*new;

	if (old == NULL)
		return (ft_strdup(""));
	new_line_pos = ft_strchr(old, '\n');
	if (new_line_pos == NULL)
		return (ft_strdup(""));
	new_line_pos++;
	len = ft_strlen(old) - (new_line_pos - old);
	new = ft_substr(new_line_pos, 0, len);
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_get_the_line(char *old, char *src)
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
	{
		free(old);
		return (NULL);
	}
	new = ft_strjoin(old, new_src);
	free(new_src);
	free(old);
	if (!new)
		return (NULL);
	if (new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*total_line;
	static char	*repo = NULL;
	int			bytes_read;

	total_line = NULL;
	bytes_read = 1;
	if (fd < 0 || ft_set_data(&total_line) || ft_set_data(&repo))
		return (NULL);
	if (repo[0] != '\0' && repo)
	{
		total_line = ft_get_the_line(total_line, repo);
		repo = ft_update_repo(repo);
	}
	while (!ft_strchr(total_line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		total_line = ft_get_the_line(total_line, buffer);
	}
	if (repo[0] == '\0')
		repo = ft_update_wbuf(buffer);
	return (total_line);
}

int main()
{
	int fd = open("deneme.txt", O_RDWR, 0666);

	char *line1 = get_next_line(fd); 
	char *line2 = get_next_line(fd); 
	char *line3 = get_next_line(fd);
	char *line4 = get_next_line(fd);

	printf("%s", line1);
	printf("%s", line2);
	printf("%s", line3);
	printf("%s", line4);

	close(fd);
}