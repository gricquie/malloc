/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:36:18 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/14 20:08:59 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	print_one_blk(const t_blk *blk)
{
	write(1, BIN_STR("blk	: 0x"));
	print_hexa((size_t)blk);
	write(1, BIN_STR("\nprev_size	: "));
	print_dec(PREV_BLK_SIZE(blk));
	write(1, BIN_STR("\nsize		: "));
	print_dec(BLK_SIZE(blk));
	if (BLK_FREE(blk))
	{
		write(1, BIN_STR("\nblk free\nprev_blk	: 0x"));
		print_hexa((size_t)blk->prev_free_blk);
		write(1, BIN_STR("\nnext_blk	: 0x"));
		print_hexa((size_t)blk->next_free_blk);
		write(1, BIN_STR("\n"));
	}
	else
		write(1, BIN_STR("\nblk allocated\n"));
}
