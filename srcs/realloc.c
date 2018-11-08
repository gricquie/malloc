/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:27:42 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:09:59 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	reduce_blk_size2(t_blk *blk, t_blk *next_blk,
		size_t size, size_t diff)
{
	t_blk	*new_blk;

	new_blk = (void *)next_blk - diff;
	if (next_blk->prev_free_blk)
		next_blk->prev_free_blk = new_blk;
	if (next_blk->next_free_blk)
		next_blk->next_free_blk = new_blk;
	new_blk->prev_blk_size = size + BLK_MIN_SIZE;
	new_blk->blk_size = next_blk->blk_size + diff;
	new_blk->prev_free_blk = next_blk->prev_free_blk;
	new_blk->next_free_blk = next_blk->next_free_blk;
	blk->blk_size -= diff;
}

static void	*reduce_blk_size(t_blk *blk, size_t size, t_page *page)
{
	t_blk	*next_blk;
	t_blk	*new_blk;
	size_t	diff;

	next_blk = (void *)blk + BLK_SIZE(blk);
	if ((void *)next_blk >= (void *)page + page->size)
		next_blk = NULL;
	diff = BLK_SIZE(blk) - size - BLK_MIN_SIZE;
	if (next_blk && BLK_FREE(next_blk))
	{
		reduce_blk_size2(blk, next_blk, size, diff);
		pthread_mutex_unlock(&g_malloc_mutex);
		return (BLK_TO_MEM(blk));
	}
	if (diff >= sizeof(t_blk))
	{
		new_blk = (void *)blk + size + BLK_MIN_SIZE;
		new_blk->blk_size = diff | 1;
		blk->blk_size -= diff;
		new_blk->prev_blk_size = blk->blk_size;
		new_blk->prev_free_blk = get_prev_free_blk(new_blk);
		new_blk->next_free_blk = get_next_free_blk(new_blk);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	return (BLK_TO_MEM(blk));
}

static void	*augment_blk_size(t_blk *blk, size_t size, t_page *page)
{
	t_blk	*next_blk;
	t_blk	*new_blk;
	size_t	diff;

	next_blk = (void *)blk + BLK_SIZE(blk);
	diff = size - BLK_SIZE(blk) + BLK_MIN_SIZE;
	next_blk = ((void *)next_blk > (void *)page + page->size ? NULL : next_blk);
	if (next_blk && BLK_FREE(next_blk))
	{
		new_blk = (void *)next_blk + diff;
		if (next_blk->prev_free_blk)
			next_blk->prev_free_blk = new_blk;
		if (next_blk->next_free_blk)
			next_blk->next_free_blk = new_blk;
		new_blk->prev_free_blk = next_blk->prev_free_blk;
		new_blk->next_free_blk = next_blk->next_free_blk;
		new_blk->blk_size = next_blk->blk_size - diff;
		blk->blk_size += diff;
		new_blk->prev_blk_size = blk->blk_size;
		pthread_mutex_unlock(&g_malloc_mutex);
		return (BLK_TO_MEM(blk));
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	free(BLK_TO_MEM(blk));
	return (malloc(size));
}

void		*realloc(void *ptr, size_t size)
{
	t_blk	*blk;
	t_page	*page;
	int		type;

	if (!ptr)
		return (malloc(size));
	size = PAD_SIZE(size);
	blk = MEM_TO_BLK(ptr);
	pthread_mutex_lock(&g_malloc_mutex);
	if (!(page = get_page_for_blk(blk)))
		return (NULL);
	if (BLK_FREE(blk))
		return (NULL);
	type = get_type_for_size(size);
	if (type != page->type)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		free(ptr);
		return (malloc(size));
	}
	if (size < BLK_SIZE(blk) - BLK_MIN_SIZE)
		return (reduce_blk_size(blk, size, page));
	else if (size > BLK_SIZE(blk) - BLK_MIN_SIZE)
		return (augment_blk_size(blk, size, page));
	return (BLK_TO_MEM(blk));
}
