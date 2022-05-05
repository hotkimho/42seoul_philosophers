/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:40:55 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 03:22:09 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
  
int	run_thread(t_info *info)
{
	int			idx;
	pthread_t	check_thread;

	idx = -1;
	while (++idx < info->num_of_philo)
	{
		if (pthread_create(&info->philos[idx].thread, NULL,
				routine, (void *)&info->philos[idx]))
			return (FAILURE);
		if (pthread_create(&check_thread, NULL,
				check_routine, (void *)&info->philos[idx]))
			return (FAILURE);
		pthread_detach(check_thread);
	}
	if (info->must_eat > 0)
	{
		if (pthread_create(&check_thread, NULL,
				check_must_eat_routine, (void *)info))
			return (FAILURE);
		pthread_detach(check_thread);
	}
	idx = 0;
	while (idx < info->num_of_philo)
		pthread_join(info->philos[idx++].thread, NULL);
	return (SUCCESS);
}

void	philo_free(t_info *info)
{
	int	idx;

	idx = 0;
	if (info->forks)
	{
		while (idx < info->num_of_philo)
		{
			pthread_mutex_destroy(&info->forks[idx]);
			info->philos->l_fork = NULL;
			info->philos->r_fork = NULL;
			idx++;
		}
	}
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->die_mutex);
	pthread_mutex_destroy(&info->check_mutex);
	pthread_mutex_destroy(&info->must_mutex);
	free(info->forks);
	if (info->philos)
		free(info->philos);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (parse_argv(argc, argv, &info))
		return (FAILURE);
	if (init_philo(&info))
	{
		philo_free(&info);
		return (FAILURE);
	}
	info.start_time = get_time();
	if (run_thread(&info))
	{
		philo_free(&info);
		return (FAILURE);
	}
	philo_free(&info);
	printf("Finish\n");
	return (SUCCESS);
}
