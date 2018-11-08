/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_page_for_blk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:35:15 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/07 15:36:39 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_page	*get_page_for_blk(t_blk *blk)
{
	t_page	*page;

	page = g_pages;
	while (page && (void *)page + page->size < (void *)blk)
		page = page->next_page;
	return (page);
}
