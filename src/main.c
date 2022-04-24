#include "../include/philosophers.h"

int	get_time()
{
	struct timeval current;
	gettimeofday(&current, NULL);

	unsigned long long currentTime = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (currentTime);
}

void *routine(void *param)
{
	t_philo	*philo;
	int count;

	philo = (t_philo*) param;
	count = 0;
	while (count < 10)
	{
		printf("ID : %d(%ds)\n", philo->id, count);
		sleep(1);
		count++;
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
		sleep(1);
		i++;
	}


}


