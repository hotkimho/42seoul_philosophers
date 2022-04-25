#include "../include/philosophers.h"
void	check_death(t_philo *philo);

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
	//philo->state = SLEEP;
	print_msg(philo, SLEEP_MSG);
	custom_sleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo->info->is_death)
		return;
	print_msg(philo, THINK_MSG);
}

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
		check_death(philo);
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
		//pthread_detach(info.philos[i].thread);
		i++;
	}
	i = 0;
	while (i < info.num_of_philo)
		pthread_join(info.philos[i++].thread, NULL);
	printf("exit\n");
	//usleep(100000000);
}


