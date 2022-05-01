/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:41:15 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 04:09:43 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_must_eat(t_philo *philo)
{
	int	must_eat;

	must_eat = philo->info->must_eat;
	if (philo->num_of_eat < must_eat)
		return (FAILURE);
	return (SUCCESS);
}

int	check_death(t_philo *philo)
{
	long long	time;

	sem_wait(philo->info->sem_eat);
	time = get_time() - philo->last_eat_time;
	if (time > (long long) philo->info->time_to_die)
	{
		philo->is_death = 1;
		sem_post(philo->info->sem_eat);
		return (SUCCESS);
	}
	sem_post(philo->info->sem_eat);
	return (FAILURE);
}

long long	get_time(void)
{
	struct timeval	current;
	long long		current_time;

	gettimeofday(&current, NULL);
	current_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_time);
}

void	custom_sleep(long long time)
{
	long long	finish_time;

	finish_time = time + get_time();
	while (finish_time > get_time())
	{
		usleep(100);
	}
}
