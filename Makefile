# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gricquie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/21 20:51:53 by gricquie          #+#    #+#              #
#    Updated: 2018/11/14 16:28:02 by gricquie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
L_NAME = libft_malloc.so

TEST_NAME = test
TEST_SRC = main.c
TEST_OBJ = $(TEST_SRC:.c=.o)

SRCS =	malloc.c \
		free.c \
		realloc.c \
		get_page_size_for_size.c \
		get_type_for_size.c \
		search_blk.c \
		search_blk_in_page.c \
		get_prev_free_blk.c \
		get_next_free_blk.c \
		create_page_for_size.c \
		init_page.c \
		get_page_for_blk.c \
		show_alloc_mem.c \
		print_blk.c \
		show_all_mem.c \

OBJS = $(SRCS:.c=.o)

HEADER = malloc.h

SDIR = srcs/
ODIR = objs/
HEADERDIR = includes/

OBJFULL = $(addprefix $(ODIR), $(OBJS))
HEADERFULL = $(addprefix $(HEADERDIR), $(HEADER))

FLAGS = -Wall \
 		-Wextra \
 		-Werror \
		

all: $(NAME)

$(NAME): $(OBJFULL) $(HEADERFULL) 
	gcc $(FLAGS) -shared -o $(NAME) $(OBJFULL) -I $(HEADERDIR) \
		-D_REENTRANT -lpthread
	ln -fs $(NAME) $(L_NAME)

$(L_NAME): $(NAME)

test: $(TEST_OBJ) $(OBJFULL) $(HEADERFULL)
	gcc $(FLAGS) -o $(TEST_NAME) $(OBJFULL) $(TEST_OBJ) -I $(HEADERDIR)

inject: $(L_NAME)
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES="$(L_NAME)"
	export DYLD_FORCE_FLAT_NAMESPACE=1

$(ODIR)%.o : $(SDIR)%.c $(HEADERFULL)
	@mkdir $(ODIR) 2> /dev/null || true
	gcc -o $@ -c $< $(FLAGS) -I $(HEADERDIR)

$(TEST_OBJ) : $(TEST_SRC)
	gcc -o $@ -c $< $(FLAGS) -I $(HEADERDIR)

clean :
	rm -f $(OBJFULL)
	rmdir $(ODIR) 2> /dev/null || true
	rm -f $(TEST_OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f $(L_NAME)
	rm -f $(TEST_NAME)

re : fclean all

.PHONY : all clean fclean re
