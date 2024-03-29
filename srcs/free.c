/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:47:34 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/16 20:11:40 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	attach_blk(t_blk *blk)
{
	t_blk	*prev_free_blk;
	t_blk	*next_free_blk;

	prev_free_blk = get_prev_free_blk(blk);
	next_free_blk = get_next_free_blk(blk);
	blk->prev_free_blk = prev_free_blk;
	if (prev_free_blk)
		prev_free_blk->next_free_blk = blk;
	blk->next_free_blk = next_free_blk;
	if (next_free_blk)
		next_free_blk->prev_free_blk = blk;
}

static void	unfragment_mem(t_blk *blk)
{
	t_blk	*next_blk;
	t_page	*page;

	if (!(page = get_page_for_blk(blk)))
		return ;
	next_blk = (void *)blk + BLK_SIZE(blk);
	if ((void *)page + page->size >= (void *)blk && BLK_FREE(next_blk))
	{
		blk->blk_size += BLK_SIZE(next_blk);
		if (next_blk->prev_free_blk)
			next_blk->prev_free_blk->next_free_blk = blk;
		blk->next_free_blk = next_blk->next_free_blk;
		blk->prev_free_blk = next_blk->prev_free_blk;
		if (blk->next_free_blk)
		{
			blk->next_free_blk->prev_free_blk = blk;
			next_blk = (void *)blk + BLK_SIZE(blk);
			if ((void *)page + page->size > (void *)next_blk)
				next_blk->prev_blk_size = blk->blk_size;
		}
	}
	next_blk = blk;
	blk = (void *)blk - PREV_BLK_SIZE(blk);
	if ((void *)page + sizeof(t_page) > (void *)blk && BLK_FREE(next_blk))
	{
		blk->blk_size += BLK_SIZE(next_blk);
		if (next_blk->prev_free_blk)
			next_blk->prev_free_blk->next_free_blk = blk;
		blk->next_free_blk = next_blk->next_free_blk;
		blk->prev_free_blk = next_blk->prev_free_blk;
		if (blk->next_free_blk)
		{
			blk->next_free_blk->prev_free_blk = blk;
			next_blk = (void *)blk + BLK_SIZE(blk);
			if ((void *)page + page->size > (void *)next_blk)
				next_blk->prev_blk_size = blk->blk_size;
		}
	}
}

static void	delete_page(t_page *page)
{
	if (page->prev_page)
		page->prev_page->next_page = page->next_page;
	if (page->next_page)
		page->next_page->prev_page = page->prev_page;
	if (page == g_pages)
		g_pages = page->next_page;
	munmap(page, page->size);
}

void		free(void *ptr)
{
	t_page	*page;
	t_blk	*blk;

DEBUG_STRING("free called\n");
	if (!ptr)
	{
DEBUG_STRING("free called on NULL, end\n");
		return ;
	}
	blk = MEM_TO_BLK(ptr);
	pthread_mutex_lock(&g_malloc_mutex);
	if (!(page = get_page_for_blk(blk)))
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return ;
	}
	SET_FREE(blk, 1);
	if (page->type == large)
	{
		delete_page(page);
	}
	else
	{
		attach_blk(blk);
		unfragment_mem(blk);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
DEBUG_STRING("free end\n");
}
