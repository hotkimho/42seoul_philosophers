/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:42:18 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 04:08:33 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	routine(t_philo *philo)
{
	pthread_t	check_thread;

	if (philo->id % 2 == 0)
		usleep(100);
	philo->last_eat_time = get_time();
	pthread_create(&check_thread, NULL, check_routine, (void *)philo);
	pthread_detach(check_thread);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
		usleep(10);
	}
	return ;
}

void	*check_routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->info->sem_die);
		if (!check_death(philo) && philo->is_death == 1)
		{
			print_die(philo, DIE_MSG);
			sem_post(philo->info->sem_die);
			sem_post(philo->info->sem_stop);
			break ;
		}
		sem_post(philo->info->sem_die);
		sem_wait(philo->info->sem_die);
		if (philo->info->must_eat > 0 && !check_must_eat(philo))
		{
			sem_post(philo->info->sem_die);
			sem_post(philo->info->sem_must_eat);
			break ;
		}
		sem_post(philo->info->sem_die);
		usleep(1000);
	}
	return (NULL);
}

void	*check_must_eat_routine(void *param)
{
	t_info	*info;
	int		must_eat_count;

	info = (t_info *)param;
	must_eat_count = 0;
	while (1)
	{
		sem_wait(info->sem_must_eat);
		must_eat_count++;
		if (must_eat_count >= info->num_of_philo)
		{
			sem_post(info->sem_stop);
			return (NULL);
		}
	}
	return (NULL);
}
