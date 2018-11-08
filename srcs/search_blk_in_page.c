/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_blk_in_page.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:25:56 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:11:53 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	cut_blk(t_blk *blk, size_t size)
{
	t_blk	*tmp;

	tmp = (void *)blk + BLK_MIN_SIZE + size;
	tmp->blk_size = blk->blk_size - BLK_MIN_SIZE - size;
	blk->blk_size -= BLK_SIZE(tmp);
	tmp->prev_blk_size = blk->blk_size;
	tmp->next_free_blk = blk->next_free_blk;
	tmp->prev_free_blk = blk->prev_free_blk;
}

t_blk		*search_blk_in_page(t_page *page, size_t size)
{
	t_blk	*cur;

	cur = page->blks;
	while (cur && (void *)cur < (void *)page + page->size - BLK_MIN_SIZE)
	{
		if (!BLK_FREE(cur))
		{
			cur = (void *)cur + cur->blk_size;
			continue;
		}
		if (BLK_SIZE(cur) >= BLK_MIN_SIZE + size)
		{
			if (BLK_SIZE(cur) > BLK_MIN_SIZE + size + sizeof(t_blk))
				cut_blk(cur, size);
			SET_FREE(cur, 0);
			return (cur);
		}
		cur = cur->next_free_blk;
	}
	return (NULL);
}
