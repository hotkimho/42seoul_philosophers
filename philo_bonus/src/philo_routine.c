/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:42:18 by hkim2             #+#    #+#             */
/*   Updated: 2022/04/28 01:59:37 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	routine(t_philo *philo)
{
	pthread_t	check_thread;

	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_eat_time = get_time();
	pthread_create(&check_thread, NULL, check_routine, (void*)philo);
	pthread_detach(check_thread);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
		usleep(100);
	}
//	pthread_join(check_thread, NULL);
	return ;
}


void	*check_routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	while (!philo->info->is_death)
	{
		sem_wait(philo->info->sem_die);	
		if (!check_death(philo))
		{
			print_die(philo, DIE_MSG);
			philo->info->is_death = 1;
			sem_post(philo->info->sem_die);
			break ;
		}
		sem_post(philo->info->sem_die);
		usleep(philo->info->time_to_eat);
	}
	return (NULL);
}

void	*check_must_eat_routine(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	while (!info->is_death)
	{
		if (!check_must_eat(info))
		{
			info->is_death = 1;
			return (NULL);
		}
	}
	return (NULL);
}

