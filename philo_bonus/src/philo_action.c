/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:41:17 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 03:45:29 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->info->sem_fork);
	print_msg(philo, FORK_MSG);
	sem_wait(philo->info->sem_fork);
	print_msg(philo, FORK_MSG);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->info->sem_eat);
	print_msg(philo, EAT_MSG);
	philo->num_of_eat++;
	philo->last_eat_time = get_time();
	sem_post(philo->info->sem_eat);
	custom_sleep(philo->info->time_to_eat);
	sem_post(philo->info->sem_fork);
	sem_post(philo->info->sem_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, SLEEP_MSG);
	custom_sleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_msg(philo, THINK_MSG);
}
