/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:20:42 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/10 21:16:23 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*rep;

	rep = b;
	i = 0;
	while (i < len)
	{
		rep[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

static int	docp(char **tab, char const *s, int *ct)
{
	int i;

	if (!(tab[ct[2]] = malloc(sizeof(char) * (ct[1] - ct[0]))))
		return (0);
	i = 0;
	while (ct[0] + 1 + i < ct[1])
	{
		tab[ct[2]][i] = s[ct[0] + 1 + i];
		i++;
	}
	tab[ct[2]][i] = '\0';
	ct[2]++;
	return (1);
}

static int	sizet(char const *s, char c)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

char		**ft_split(char const *s, char c)
{
	char		**tab;
	int			count[3];

	ft_memset(count, 0, sizeof(count));
	if (s == NULL || !(tab = malloc(sizeof(char *) * (sizet(s, c) + 2))))
		return (NULL);
	count[0] = -1;
	while (s[count[1]])
	{
		if (s[count[1]] == c || s[count[1] + 1] == '\0')
		{
			if (s[count[1] + 1] == '\0' && s[count[1]] != c)
				count[1]++;
			if (count[1] - count[0] != 1)
			{
				if (!(docp(tab, s, count)))
					return (NULL);
			}
			count[0] = count[1];
		}
		if (s[count[1]])
			count[1]++;
	}
	tab[count[2]] = NULL;
	return (tab);
}
