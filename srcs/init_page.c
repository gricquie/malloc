/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:06:37 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:38:21 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	init_page(t_page *page, size_t page_size, int type)
{
	t_blk	*first_blk;

	page->next_page = NULL;
	page->prev_page = NULL;
	page->size = page_size;
	page->type = type;
	first_blk = page->blks;
	first_blk->prev_blk_size = 0;
	first_blk->blk_size = page_size - sizeof(t_page);
	SET_FREE(first_blk, 1);
	SET_TYPE(first_blk, type);
	first_blk->prev_free_blk = NULL;
	first_blk->next_free_blk = NULL;
}
