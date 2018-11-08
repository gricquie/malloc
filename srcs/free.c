/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:47:34 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 17:10:38 by gricquie         ###   ########.fr       */
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
	if (blk->next_free_blk == (void *)blk + BLK_SIZE(blk))
	{
		blk->blk_size += BLK_SIZE(blk->next_free_blk);
		blk->next_free_blk = blk->next_free_blk->next_free_blk;
		if (blk->next_free_blk)
		{
			blk->next_free_blk->prev_free_blk = blk;
			((t_blk *)((void *)blk->next_free_blk
				+ BLK_SIZE(blk)))->prev_blk_size = blk->blk_size;
		}
	}
	if (blk->prev_free_blk == (void *)blk - PREV_BLK_SIZE(blk))
	{
		blk = blk->prev_free_blk;
		blk->blk_size += BLK_SIZE(blk->next_free_blk);
		blk->next_free_blk = blk->next_free_blk->next_free_blk;
		if (blk->next_free_blk)
		{
			blk->next_free_blk->prev_free_blk = blk;
			((t_blk *)((void *)blk->next_free_blk
				+ BLK_SIZE(blk)))->prev_blk_size = blk->blk_size;
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

	if (!ptr)
		return ;
	blk = MEM_TO_BLK(ptr);
	pthread_mutex_lock(&g_malloc_mutex);
	if (!(page = get_page_for_blk(blk)))
		return ;
	SET_FREE(blk, 1);
	if (page->type == large)
		delete_page(page);
	else
	{
		attach_blk(blk);
		unfragment_mem(blk);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}
