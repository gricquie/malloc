/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_free_blk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:54:30 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/07 16:57:19 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_blk	*get_next_free_blk(t_blk *blk)
{
	t_page	*page;

	if (!(page = get_page_for_blk(blk)))
		return (NULL);
	blk = (void *)blk + BLK_SIZE(blk);
	while ((void *)blk < (void *)page + page->size && !BLK_FREE(blk))
		blk = (void *)blk + BLK_SIZE(blk);
	if ((void *)blk >= (void *)page + page->size)
		return (NULL);
	return (blk);
}
