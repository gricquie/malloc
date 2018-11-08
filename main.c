#include <malloc.h>
#include <stdio.h>

void	*thread_malloc(void *p_data)
{
	int		i;

	(void)p_data;
	i = 0;
	while (i++ < 10)
		malloc(128);
	return (NULL);
}

int main()
{
	void	*p1;

	p1 = malloc(5000);
	show_all_mem();
	p1 = realloc(p1, 2222);
	p1 = realloc(p1, 3000);
	show_all_mem();
}
