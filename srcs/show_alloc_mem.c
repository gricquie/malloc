/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:38 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 17:11:49 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void		print_hexa(size_t x)
{
	const char	hexa[16] = "0123456789ABCDEF";

	if (x >= 16)
		print_hexa(x / 16);
	write(1, hexa + x % 16, 1);
}

static void		print_dec(size_t x)
{
	const char	dec[10] = "0123456789";

	if (x >= 10)
		print_dec(x / 10);
	write(1, dec + x % 10, 1);
}

static size_t	print_blk(const t_blk *blk)
{
	if (BLK_FREE(blk))
		return (0);
	write(1, BIN_STR("0x"));
	print_hexa((size_t)BLK_TO_MEM(blk));
	write(1, BIN_STR(" - 0x"));
	print_hexa((size_t)blk + BLK_SIZE(blk));
	write(1, BIN_STR(" : "));
	print_dec(BLK_SIZE(blk) - BLK_MIN_SIZE);
	write(1, BIN_STR("\n"));
	return (BLK_SIZE(blk) - BLK_MIN_SIZE);
}

static size_t	print_page(const t_page *page)
{
	const t_blk	*blk;
	size_t		total;

	if (page->type == tiny)
		write(1, BIN_STR("TINY : 0x"));
	else if (page->type == small)
		write(1, BIN_STR("SMALL : 0x"));
	else
		write(1, BIN_STR("LARGE : 0x"));
	print_hexa((size_t)page);
	write(1, BIN_STR("\n"));
	blk = page->blks;
	total = 0;
	while ((void *)blk < (void *)page + page->size)
	{
		total += print_blk(blk);
		blk = (void *)blk + BLK_SIZE(blk);
	}
	return (total);
}

void			show_alloc_mem(void)
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
	write(1, BIN_STR("Total : "));
	print_dec(total);
	write(1, BIN_STR(" octets\n"));
	pthread_mutex_unlock(&g_malloc_mutex);
}
