/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:42:18 by hkim2             #+#    #+#             */
/*   Updated: 2022/04/28 01:15:59 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->last_eat_time = get_time();
	if (philo->id % 2 == 0)
		usleep(200);
	while (!philo->info->is_death)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
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

void	*check_routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	usleep(100);
	while (!philo->info->is_death)
	{
		pthread_mutex_lock(&philo->info->die_mutex);
		if (!check_death(philo))
		{
			print_die(philo, DIE_MSG);
			philo->info->is_death = 1;
			pthread_mutex_unlock(&philo->info->die_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->die_mutex);
		usleep(philo->info->time_to_eat);
	}
	return (NULL);
}
