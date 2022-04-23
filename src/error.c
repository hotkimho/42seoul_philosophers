#include "../include/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	error_msg(char *message)
{
	write(1, message, ft_strlen(message));
	exit(FAILURE);
}