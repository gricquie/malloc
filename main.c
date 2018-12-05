#include "includes/malloc.h"
#include <stdio.h>

int		malloc_debug = 0;
int main()
{
	size_t	i;
	char	*ptr[4096];

	i = 0;
	while (i < 4096)
	{
		write(1, BIN_STR("calloc n"));
		print_dec(i);
		write(1, BIN_STR("\n"));	
		ptr[i] = calloc(1024, 1);
		ptr[i][1023] = 46;
		i++;
	}

	i = 0;
	while (i < 4096)
	{
		write(1, BIN_STR("realloc n"));
		print_dec(i);
		write(1, BIN_STR("\n"));	
		if (i == 1999)
			malloc_debug = 1;
		else
			malloc_debug = 0;
		ptr[i] = realloc(ptr[i], 2048);
		ptr[i][2047] = 46;
		i++;
	}

	i = 0;
	while (i < 4096)
	{
		free(ptr[i]);
		write(1, BIN_STR("free n"));
		print_dec(i);
		write(1, BIN_STR("\n"));	
		i++;
	}
	return (0);
}
