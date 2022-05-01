/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:14:02 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 03:21:39 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_info(t_info *info)
{
	int	idx;

	info->is_death = 0;
	idx = -1;
	while (++idx < info->num_of_philo)
	{
		info->philos[idx].id = idx + 1;
		if (pthread_mutex_init(&info->forks[idx], NULL))
			return (error_msg("error"));
		if (idx == 0)
			info->philos[idx].l_fork = &info->forks[info->num_of_philo - 1];
		else
			info->philos[idx].l_fork = &info->forks[idx - 1];
		info->philos[idx].r_fork = &info->forks[idx];
		info->philos[idx].info = info;
		info->philos[idx].num_of_eat = 0;
	}
	return (SUCCESS);
}

int	malloc_philo(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->num_of_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!(info->philos) || !(info->forks))
		return (FAILURE);
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&info->die_mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&info->check_mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&info->must_mutex, NULL))
		return (FAILURE);
	return (SUCCESS);
}

int	init_philo(t_info *info)
{
	if (malloc_philo(info))
		return (FAILURE);
	if (init_info(info))
		return (FAILURE);
	return (SUCCESS);
}
