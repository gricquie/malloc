/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:33:30 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/16 20:10:51 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	tot;

DEBUG_STRING("calloc called\n");
	tot = count * size;
	ptr = malloc(tot);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < tot)
	{
		*((size_t *)(ptr + i)) = 0;
		i += sizeof(size_t);
	}
DEBUG_STRING("calloc end\n");
	return (ptr);
}
