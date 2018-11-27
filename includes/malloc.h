/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:07:39 by gricquie          #+#    #+#             */
/*   Updated: 2018/11/16 20:11:16 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define DEBUG 0
# define DEBUG_STRING(s) (DEBUG ? write(1, BIN_STR(s)): 0)

# include <unistd.h>
# include <stddef.h>
# include <sys/mman.h>
# include <pthread.h>

# define BIN_STR(s) s, sizeof(s) - 1

# define TINY_MAX_SIZE 512
# define SMALL_MAX_SIZE 2048

# define FREE_MASK 0x1
# define TYPE_MASK 0x6
# define SIZE_MASK 0x7
# define BLK_SIZE(b) (b->blk_size & ~SIZE_MASK)
# define BLK_FREE(b) (b->blk_size & FREE_MASK)
# define BLK_TYPE(b) ((b->blk_size & TYPE_MASK) >> 1)
# define PREV_BLK_SIZE(b) (b->prev_blk_size & ~SIZE_MASK)
# define PREV_BLK_FREE(b) (b->prev_blk_size & FREE_MASK)
# define SET_FREE(b, v) (b->blk_size = (b->blk_size & ~FREE_MASK) | (v & FREE_MASK))
# define SET_TYPE(b, t) (b->blk_size = (b->blk_size & ~TYPE_MASK) | ((t << 1) & TYPE_MASK))

# define PAD_SIZE(s) ((s & SIZE_MASK) ? ((s | SIZE_MASK) + 1) : s)

typedef	enum e_type	t_type;
enum	e_type
{
	tiny = 0,
	small = 1,
	large = 2
};

typedef struct	s_blk	t_blk;
struct s_blk
{
	size_t		prev_blk_size;
	size_t		blk_size;
	
	t_blk		*prev_free_blk;
	t_blk		*next_free_blk;
};

# define BLK_MIN_SIZE (offsetof(t_blk, prev_free_blk))
# define BLK_TO_MEM(b) ((void *)b + BLK_MIN_SIZE)
# define MEM_TO_BLK(m) ((t_blk *)(m - BLK_MIN_SIZE))

typedef	struct s_page	t_page;
struct s_page
{
	t_page			*next_page;	
	t_page			*prev_page;
	size_t			size;
	long			type;
	t_blk			blks[];
};

pthread_mutex_t	g_malloc_mutex;
t_page			*g_pages;

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);

size_t	get_page_size_for_size(size_t size);
t_blk	*search_blk(size_t size);
t_blk	*search_blk_in_page(t_page *page, size_t size);
t_blk	*get_prev_free_blk(t_blk *blk);
t_blk	*get_next_free_blk(t_blk *blk);

t_page	*create_page_for_size(size_t size);
void	init_page(t_page *page, size_t page_size, int type);
t_page	*get_page_for_blk(t_blk *blk);

int		get_type_for_size(size_t size);
size_t	get_max_size_for_type(int type);
size_t	get_page_size_for_type(int type);

void	show_alloc_mem(void);

///////////////////////////////////////////////////////////////////////
void	print_one_blk(const t_blk *blk);
void	show_all_mem(void);
void	print_hexa(size_t n);
void	print_dec(size_t n);

#endif
