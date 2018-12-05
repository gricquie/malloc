#include "includes/malloc.h"
#include <stdio.h>

int main()
{
	size_t	i;
	size_t	n = 64000;
	size_t	s1 = 128;
	char	*ptr[n * 2];

	i = 0;
	while (i < n)
	{
		write(1, BIN_STR("calloc s1 n"));
		print_dec(i);
		write(1, BIN_STR("\n"));	
		ptr[i] = calloc(s1, 1);
		ptr[i][0] = 46;
		ptr[i][s1 - 1] = 46;
		i++;
	}

	i = 0;
	while (i < n)
	{
		free(ptr[i]);
		write(1, BIN_STR("free n"));
		print_dec(i);
		write(1, BIN_STR("\n"));	
		i++;
	}
	return (0);
}
