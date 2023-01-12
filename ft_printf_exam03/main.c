#include <stdio.h>

int	ft_printf(const char *str, ...);

int	main(void)
{
	int		num = 2147483648;
	char	*str = NULL;
	int		i;
	int		j;

	i = printf(" c_printf: d: %d\tx: %x\ts: %s\n", num, num, str);
	j = ft_printf("ft_printf: d: %d\tx: %x\ts: %s\n", num, num, str);
	printf("\n\n numbers:\n c: %d\nft: %d\n", i, j);
	return (0);
}
