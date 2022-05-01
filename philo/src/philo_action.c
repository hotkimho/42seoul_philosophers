/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:41:17 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 02:50:02 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->info->is_death)
		return ;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, FORK_MSG);
	print_msg(philo, FORK_MSG);
}

void	eat(t_philo *philo)
{
	print_msg(philo, EAT_MSG);
	philo->num_of_eat++;
	philo->last_eat_time = get_time();
	custom_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->info->is_death)
		return ;
	print_msg(philo, SLEEP_MSG);
	custom_sleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo->info->is_death)
		return ;
	print_msg(philo, THINK_MSG);
}
