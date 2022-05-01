/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:42:18 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 03:30:44 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_one(t_philo *philo)
{
	print_msg(philo, FORK_MSG);
	custom_sleep(philo->info->time_to_die);
	print_die(philo, DIE_MSG);
	philo->info->is_death = 1;
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->info->num_of_philo == 1)
	{
		philo_one(philo);
		return (NULL);
	}
	philo->last_eat_time = get_time();
	if (philo->id % 2 == 0)
		usleep(200);
	while (!philo->info->is_death)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
		usleep(10);
	}
	return (NULL);
}

void	*check_must_eat_routine(void *param)
{
	t_info	*info;

	info = (t_info *) param;
	while (!info->is_death)
	{
		if (!check_must_eat(info))
		{	
			pthread_mutex_lock(&info->must_mutex);
			info->is_death = 1;
			pthread_mutex_unlock(&info->must_mutex);
			return (NULL);
		}	
	}
	return (NULL);
}

void	*check_routine(void *param)
{
	t_philo		*philo;
	int			death;

	philo = (t_philo *)param;
	death = 0;
	usleep(100);
	while (!philo->info->is_death)
	{	
		pthread_mutex_lock(&philo->info->die_mutex);
		pthread_mutex_lock(&philo->info->check_mutex);
		death = check_death(philo, philo->last_eat_time);
		pthread_mutex_unlock(&philo->info->check_mutex);
		if (!death && philo->info->num_of_philo > 1)
		{
			print_die(philo, DIE_MSG);
			pthread_mutex_lock(&philo->info->check_mutex);
			philo->info->is_death = 1;
			pthread_mutex_unlock(&philo->info->check_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->die_mutex);
		usleep(1000);
	}
	return (NULL);
}
