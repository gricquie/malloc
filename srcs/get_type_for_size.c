/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_for_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:44:41 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/05 18:47:00 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int	get_type_for_size(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		return (tiny);
	if (size <= SMALL_MAX_SIZE)
		return (small);
	return (large);
}
