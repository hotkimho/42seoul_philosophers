/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:14:02 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 03:55:30 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_info(t_info *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->num_of_philo)
	{
		info->philos[idx].id = idx + 1;
		info->philos[idx].info = info;
		info->philos[idx].num_of_eat = 0;
		info->philos[idx].is_death = 0;
		info->philos[idx].last_eat_time = get_time();
	}
	return (SUCCESS);
}

int	malloc_philo(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->num_of_philo);
	if (!(info->philos))
		return (FAILURE);
	return (SUCCESS);
}

int	init_sem(t_info *info)
{
	info->eat = "/sem_eat";
	info->print = "/sem_print";
	info->fork = "/sem_fork";
	info->die = "/sem_die";
	if (create_sem(&info->sem_fork, info->fork, info->num_of_philo))
		return (FAILURE);
	if (create_sem(&info->sem_eat, info->eat, 1))
		return (FAILURE);
	if (create_sem(&info->sem_print, info->print, 1))
		return (FAILURE);
	if (create_sem(&info->sem_die, info->die, 1))
		return (FAILURE);
	if (create_sem(&info->sem_stop, "/sem_stop", 1))
		return (FAILURE);
	if (create_sem(&info->sem_must_eat, "/sem_must_eat", 1))
		return (FAILURE);
	return (SUCCESS);
}

int	init_philo(t_info *info)
{
	if (malloc_philo(info))
		return (error_msg("init error"));
	if (init_info(info))
		return (error_msg("init error"));
	if (init_sem(info))
		return (error_msg("init error"));
	return (SUCCESS);
}
