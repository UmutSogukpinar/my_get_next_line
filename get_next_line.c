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

int	ft_set_initial_data(char *data)
{
	int	i;

	i = 0;
	data = malloc(BUFFER_SIZE * sizeof(char));
	while (data[i] != '\0')
	{
		data[i] = 0;
		i++;
	}
	return (1);
}

char	*ft_create_and_free_arr(char *old, char *buffer)
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
	if (!new || !ft_set_initial_data(new))
		return (NULL);
	if (buffer[BUFFER_SIZE] == '\n')
		new_buffer = ft_substr(buffer, 0, buffer_len + 1);
	else
		new_buffer = ft_substr(buffer, 0, buffer_len);
	new = ft_strjoin(old, new_buffer);
	free(old);
	free(new_buffer);
	return (new);
}

// char	*get_next_line(int fd)
// {
// 	char		buffer[BUFFER_SIZE + 1];
// 	char		*total_line;
// 	static char *remaining_data = 0;

// 	if (fd < 0 || ft_set_initial_data(remaining_data))
// 		return (NULL);
	
// }
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
	char *s = ft_strdup("ahmet ");
	char *buffer = ft_strdup("buffer\n 1 4234");

	char *new = ft_create_and_free_arr(s, buffer);
	// printf("new: %s", new);
	printf("buf: %s", buffer);
}