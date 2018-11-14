/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_blk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:37:51 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:44:32 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_blk	*search_blk(size_t size)
{
	t_page	*cur;
	t_blk	*blk;
	int		type;

	type = get_type_for_size(size);
	cur = g_pages;
	while (cur)
	{
		if (cur->type == type)
		{
			blk = search_blk_in_page(cur, size);
			if (blk)
			{
				return (blk);
			}
		}
		cur = cur->next_page;
	}
	cur = create_page_for_size(size);
	if (!cur)
		return (NULL);
	blk = search_blk_in_page(cur, size);
	return (blk);
}
