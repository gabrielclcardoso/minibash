/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:24:05 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/05 11:20:41 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_linelen(char const *str);
char		*find_line_in(int fd, char **buffer);
char		*get_last_line_from(char **buffer);
char		*get_line_from(char **buffer);

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	if (!ft_linelen(buffer[fd]))
		line = find_line_in(fd, &(buffer[fd]));
	else
		line = get_line_from(&(buffer[fd]));
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}

static int	ft_linelen(char const *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*find_line_in(int fd, char **buffer)
{
	char	tempread[BUFFER_SIZE + 1];
	char	*tempcontent;
	int		returnvalue;

	returnvalue = 1;
	while (!ft_linelen(*buffer) && returnvalue)
	{
		returnvalue = read(fd, tempread, BUFFER_SIZE);
		if (returnvalue >= 0)
		{
			tempread[returnvalue] = '\0';
			tempcontent = ft_strjoin(*buffer, tempread, 0);
			free(*buffer);
			*buffer = tempcontent;
		}
		else
			return (NULL);
	}
	if (!returnvalue)
		return (get_last_line_from(buffer));
	else
		return (get_line_from(buffer));
}

char	*get_last_line_from(char **buffer)
{
	char	*line;
	int		linelen;

	linelen = ft_strlen(*buffer);
	if (!linelen)
		return (NULL);
	line = malloc(linelen + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer, linelen + 1);
	*buffer[0] = '\0';
	return (line);
}

char	*get_line_from(char **buffer)
{
	char	*line;
	int		linelen;

	linelen = ft_linelen(*buffer);
	line = malloc(linelen + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer, linelen + 1);
	ft_strlcpy(*buffer, *buffer + linelen, ft_strlen(*buffer));
	free(*buffer);
	return (line);
}
