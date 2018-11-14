/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:07:41 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/14 15:42:55 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_page			*g_pages = NULL;
pthread_mutex_t	g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	t_blk	*blk;

	size = PAD_SIZE(size);
	if (size == 0)
		size = 8;
	pthread_mutex_lock(&g_malloc_mutex);
	blk = search_blk(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (blk ? BLK_TO_MEM(blk) : NULL);
}
