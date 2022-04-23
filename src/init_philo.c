#include "../include/philosophers.h"



int	malloc_philo(t_info *info)
{
	info->philos = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
}

int	init_philo(t_info *info)
{
	if (malloc_philo(&info))
		return (FAILURE);
	return (SUCCESS);
}