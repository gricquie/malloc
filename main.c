#include "includes/malloc.h"
#include <stdio.h>

int main()
{
	size_t	i;
	void	*ptr[4096];

	i = 0;
	while (i < 4096)
		ptr[i++] = calloc(1024, 1);

	i = 0;
	while (i < 4096)
	{
		ptr[i] = realloc(ptr[i], 2048);
		i++;
	}

	i = 0;
	while (i < 4096)
		free(ptr[i++]);

	return (0);
}
