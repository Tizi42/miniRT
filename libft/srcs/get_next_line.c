/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:51:50 by tyuan             #+#    #+#             */
/*   Updated: 2020/06/04 13:59:45 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checknewl(char *buf, int ret, char **line, t_fdnl *istruct)
{
	int i;

	i = -1;
	while (++i < ret)
	{
		if (buf[i] == '\n')
		{
			if (istruct->iline)
				free(istruct->iline);
			istruct->iline = f_strdup("");
			append(&istruct->iline, buf, i + 1, ret);
			return (append(line, buf, 0, i));
		}
	}
	i = append(line, buf, 0, ret);
	if (i < 0)
		return (-1);
	else
		return (42);
}

int	f_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	append(char **line, char *buf, int start, int end)
{
	char	*tmp;
	int		i;

	if (!(tmp = malloc(sizeof(char) * (f_strlen(*line) + (end - start) + 1))))
		return (-1);
	i = 0;
	if (*line && **line)
	{
		while (line[0][i])
		{
			tmp[i] = line[0][i];
			i++;
		}
	}
	while ((start < end))
		tmp[i++] = buf[start++];
	tmp[i] = '\0';
	if (*line)
		free(*line);
	*line = tmp;
	return (1);
}

int	ft_return(int ret, t_fdnl **istruct, t_fdnl **begin)
{
	if (ret > 0)
		return (1);
	else
	{
		free((*istruct)->iline);
		del_istruct(begin, istruct);
		if (ret == 0)
			return (0);
		else
			return (-1);
	}
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static t_fdnl	*begin;
	t_fdnl			*istruct;
	char			*tmp;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = f_strdup("");
	if ((istruct = checkfd(begin, fd)))
	{
		tmp = f_strdup(istruct->iline);
		ret = checknewl(tmp, f_strlen(istruct->iline), line, istruct);
		free(tmp);
		if (ret <= 1)
			return (ret);
	}
	else
		f_lstadd_back(&begin, istruct = f_lstnew(fd));
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if ((ret = checknewl(buf, ret, line, istruct)) <= 1)
			return (ret);
	}
	return (ft_return(ret, &istruct, &begin));
}
