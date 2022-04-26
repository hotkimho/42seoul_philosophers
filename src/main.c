#include "../include/philosophers.h"

int		check_must_eat(t_info *info)
{
	int	idx;
	int	must_eat;

	must_eat = info->must_eat;
	idx = 0;
	while (idx < info->num_of_philo)
	{
		if (info->philos[idx].num_of_eat < must_eat)
			return (FAILURE);
		idx++;
	}
	return (SUCCESS);
}

void	*check_must_eat_routine(void *param)
{
	t_info	*info;

	info = (t_info*) param;
	while (!info->is_death)
	{
		if (!check_must_eat(info))
		{
			info->is_death = 1;
			printf("Finish\n");
			return (NULL);
		}
	}
	return (NULL);
}
void	*check_routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo*) param;
	custom_sleep(200);
	while (!philo->info->is_death)
	{
		pthread_mutex_lock(&philo->info->die_mutex);
		if (!check_death(philo))
		{
			print_die(philo, DIE_MSG);
			break ;
		}
		pthread_mutex_unlock(&philo->info->die_mutex);
	}
	return (NULL);
}

int	run_thread(t_info *info)
{
	int	idx;
	int	error;
	pthread_t	check_thread;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		error = pthread_create(&info->philos[idx].thread, NULL, routine, (void *)&info->philos[idx]);
		if (error)
			return (FAILURE);
		error = pthread_create(&check_thread, NULL, check_routine, (void *)&info->philos[idx]);
		if (error)
			return (FAILURE);
		pthread_detach(check_thread);
		idx++;
	}
	if (info->must_eat > 0)
	{
		pthread_create(&check_thread, NULL, check_must_eat_routine, (void *)info);
		pthread_detach(check_thread);
	}
	idx = 0;
	while (idx < info->num_of_philo)
		pthread_join(info->philos[idx++].thread, NULL);
	return (SUCCESS);
}

//int	philo_free(t_info *info)
//{

//}
int main(int argc, char **argv)
{
	t_info	info;
	
	if (parse_argv(argc, argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	info.start_time = get_time();
	if (run_thread(&info))
		return (FAILURE);
	printf("exit\n");
	
	return (SUCCESS);
	//usleep(100000000);
}


