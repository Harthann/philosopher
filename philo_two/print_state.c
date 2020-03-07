#include "philo_two.h"

void	print_state(long timestamp, int number, char *str)
{
	int i;
	char *to_print;
	char *to_free;
	char *to_add;

	i = 0;
	to_print = ft_ultoa(timestamp);
	to_free = to_print;
	to_print = ft_strjoin(to_print, " ");
	free(to_free);
	to_add = ft_ultoa(number);
	to_free = to_print;
	to_print = ft_strjoin(to_print, to_add);
	free(to_free);
	to_free = to_print;
	to_print = ft_strjoin(to_print, str);
	free(to_free);
	write(1, to_print, ft_strlen(to_print));
}