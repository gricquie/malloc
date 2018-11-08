/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prev_free_blk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:57:31 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/07 16:49:10 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_blk	*get_prev_free_blk(t_blk *blk)
{
	t_page	*page;

	if (!(page = get_page_for_blk(blk)))
		return (NULL);
	while ((void *)blk > (void *)page && !BLK_FREE(blk))
	{
		if (!PREV_BLK_SIZE(blk))
			return (NULL);
		blk = (void *)blk - PREV_BLK_SIZE(blk);
	}
	if ((void *)blk <= (void *)page + sizeof(t_page))
		return (NULL);
	return (blk);
}
