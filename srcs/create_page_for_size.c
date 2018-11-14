/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_page_for_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:17:54 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/08 18:40:11 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_page	*create_page_for_size(size_t size)
{
	t_page	*page;
	t_page	*cur;
	int		type;
	size_t	page_size;

	type = get_type_for_size(size);
	page_size = get_page_size_for_size(size);
	page = mmap(NULL, page_size, PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_ANON | MAP_SHARED, -1, 0);
	if (page == (void *)-1)
		return (NULL);
	init_page(page, page_size, type);
	if (!g_pages)
	{
		g_pages = page;
		return (page);
	}
	cur = g_pages;
	while (cur->next_page && cur->next_page < page)
		cur = cur->next_page;
	page->next_page = cur->next_page;
	page->prev_page = cur;
	cur->next_page = page;
	return (page);
}
