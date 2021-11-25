/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:07:41 by gricquie          #+#    #+#             */
/*   Updated: 2021/11/25 18:00:28 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_page			*g_pages = NULL;
pthread_mutex_t	g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
int				malloc_debug = 0;

void	*malloc(size_t size)
{
	t_blk	*blk;

DEBUG_STRING("malloc called\n");
	size = PAD_SIZE(size);
	if (size <= sizeof(t_blk) - BLK_MIN_SIZE)
		size = sizeof(t_blk) - BLK_MIN_SIZE;
	pthread_mutex_lock(&g_malloc_mutex);
	blk = search_blk(size);
	pthread_mutex_unlock(&g_malloc_mutex);
if (!blk)
DEBUG_STRING("malloc failed\n");
else
DEBUG_STRING("malloc success\n");
	return (blk ? BLK_TO_MEM(blk) : NULL);
}
