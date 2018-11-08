/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_page_size_for_size.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:04:41 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 17:05:52 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t			get_page_size_for_size(size_t size)
{
	size_t pagesize;

	if (size > SMALL_MAX_SIZE)
		size += BLK_MIN_SIZE + sizeof(t_page);
	else
		size = (size + BLK_MIN_SIZE) * 100 + sizeof(t_page);
	pagesize = getpagesize();
	while (pagesize < size)
	{
		pagesize += getpagesize();
	}
	return (pagesize);
}
