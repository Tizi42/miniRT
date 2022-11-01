/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:54:29 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/05 11:06:55 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;
	size_t	i;

	if (!(a = malloc(count * size)))
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		*(char *)(a + i) = 0;
		i++;
	}
	return (a);
}
