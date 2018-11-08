/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:36:18 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:12:14 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	print_one_blk(const t_blk *blk)
{
	printf("blk		: %p\n", blk);
	printf("prev_size	: %zx\n", blk->prev_blk_size);
	printf("size		: %zx\n", BLK_SIZE(blk));
	if (BLK_FREE(blk))
		printf("blk free\n");
	else
		printf("blk allocated\n");
	if (BLK_FREE(blk))
		printf("prev_blk	: %p\n", blk->prev_free_blk);
	if (BLK_FREE(blk))
		printf("next_blk	: %p\n", blk->next_free_blk);
	printf("\n");
}
