#include "../include/philosophers.h"

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

void	print_msg(t_philo *philo, char *msg)
{
	int	time;

	if (philo->info->is_death)
		return;
	pthread_mutex_lock(&philo->info->print_mutex);
	time = get_time() - philo->info->start_time;
	printf("[%dms] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print_mutex);
	return;
}

void	take_forks(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	//philo->state = FORK;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, FORK_MSG);
	print_msg(philo, FORK_MSG);

}

void	eat(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	//philo->state = EAT;
	print_msg(philo, EAT_MSG);
	custom_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	//philo->state = SLEEP;
	print_msg(philo, SLEEP_MSG);
	custom_sleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	//philo->state = THINK;
	print_msg(philo, THINK_MSG);

}

//void	check_death(t_philo *philo)
//{

//}
void *routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo*) param;

	philo->last_eat_time = get_time();

	if (philo->id % 2 == 0)
		custom_sleep(philo->info->time_to_eat);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_info	info;

	if (parse_argv(argc, argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	info.start_time = get_time();


	int i = 0;
	while (i < info.num_of_philo)
	{
		pthread_create(&info.philos[i].thread, NULL, routine, (void *)&info.philos[i]);
		pthread_detach(info.philos[i].thread);
		i++;
	}
	usleep(100000000);
}


