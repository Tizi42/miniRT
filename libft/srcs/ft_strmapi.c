/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:04:56 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/10 17:18:07 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	len = 0;
	while (s[len])
	{
		res[len] = (*f)(len, s[len]);
		len++;
	}
	res[len] = '\0';
	return (res);
}
