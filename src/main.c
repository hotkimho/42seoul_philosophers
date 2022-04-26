#include "../include/philosophers.h"

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


