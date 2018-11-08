/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_all_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:44:05 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:08:10 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static size_t	print_blk(const t_blk *blk)
{
	printf("%p - %p : %zu - %s\n", blk,
			(void *)blk + BLK_SIZE(blk), BLK_SIZE(blk) - BLK_MIN_SIZE,
			BLK_FREE(blk) ? "FREE" : "ALLOC");
	return (BLK_FREE(blk) ? 0 : BLK_SIZE(blk) - BLK_MIN_SIZE);
}

static size_t	print_page(const t_page *page)
{
	const t_blk	*blk;
	size_t		total;

	if (page->type == tiny)
		printf("TINY : ");
	else if (page->type == small)
		printf("SMALL : ");
	else
		printf("LARGE : ");
	blk = page->blks;
	total = 0;
	printf("%p - %p\n", page, (void *)page + page->size);
	while ((void *)blk < (void *)page + page->size)
	{
		total += print_blk(blk);
		blk = (void *)blk + BLK_SIZE(blk);
	}
	return (total);
}

void			show_all_mem(void)
{
	t_page	*cur;
	size_t	total;

	pthread_mutex_lock(&g_malloc_mutex);
	cur = g_pages;
	total = 0;
	while (cur)
	{
		total += print_page(cur);
		cur = cur->next_page;
	}
	printf("Total : %zu octets\n", total);
	pthread_mutex_unlock(&g_malloc_mutex);
}
