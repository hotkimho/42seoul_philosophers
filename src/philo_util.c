#include "../include/philosophers.h"

void	check_death(t_philo *philo)
{
	long long	time;

	if (philo->info->is_death)
		return;
	pthread_mutex_lock(&philo->info->die_mutex);
	time = get_time() - philo->last_eat_time;
	if (time > (long long) philo->info->time_to_die)
		philo->info->is_death = 1;
	if (philo->info->is_death)
		print_die(philo, DIE_MSG);
	pthread_mutex_unlock(&philo->info->die_mutex);
}

long long	get_time()
{
	struct timeval current;
	gettimeofday(&current, NULL);

	unsigned long long currentTime = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (currentTime);
}

void	custom_sleep(unsigned int time)
{
	unsigned int	finish_time;

	finish_time = time + get_time();
	while (finish_time > (unsigned int)get_time())
	{
		usleep(100);
	}
}