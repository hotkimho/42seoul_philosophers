/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:40:55 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 04:08:51 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	run_process(t_info *info)
{
	int			idx;
	pthread_t	must_thread;

	if (info->must_eat > 0)
	{
		if (pthread_create(&must_thread, NULL,
				check_must_eat_routine, (void *)info))
			return (FAILURE);
		pthread_detach(must_thread);
	}
	idx = -1;
	while (++idx < info->num_of_philo)
	{
		info->philos[idx].pid = fork();
		if (info->philos[idx].pid == 0)
		{
			routine(&info->philos[idx]);
			exit(SUCCESS);
		}
		usleep(10);
	}
	return (SUCCESS);
}

int	philo_free(t_info *info)
{
	int	idx;

	idx = 0;
	if (info->philos)
	{
		while (idx < info->num_of_philo)
		{
			kill(info->philos[idx].pid, SIGKILL);
			idx++;
		}
	}
	sem_unlink(info->fork);
	sem_unlink(info->die);
	sem_unlink(info->eat);
	sem_unlink(info->print);
	sem_unlink(info->stop);
	sem_unlink(info->must);
	free(info->philos);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (parse_argv(argc, argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (philo_free(&info));
	info.start_time = get_time();
	sem_wait(info.sem_must_eat);
	sem_wait(info.sem_stop);
	if (run_process(&info))
		return (philo_free(&info));
	sem_wait(info.sem_stop);
	philo_free(&info);
	usleep(1000);
	printf("finish\n");
	return (SUCCESS);
}
