#include "../include/philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, FORK_MSG);
	print_msg(philo, FORK_MSG);
}

void	eat(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	print_msg(philo, EAT_MSG);
	philo->last_eat_time = get_time();
	custom_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	print_msg(philo, SLEEP_MSG);
	custom_sleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	print_msg(philo, THINK_MSG);
}

void *routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo*) param;

	philo->last_eat_time = get_time();

	if (philo->id % 2 == 0)
		custom_sleep(philo->info->time_to_eat);
	while (!philo->info->is_death)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	printf("end\n");
	return (NULL);
}