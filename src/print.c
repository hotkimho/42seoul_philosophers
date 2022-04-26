/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:41:21 by hkim2             #+#    #+#             */
/*   Updated: 2022/04/27 01:18:31 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_msg(t_philo *philo, char *msg)
{
	int	time;

	if (philo->info->is_death)
		return ;
	pthread_mutex_lock(&philo->info->print_mutex);
	time = get_time() - philo->info->start_time;
	printf("[%dms] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print_mutex);
	return ;
}

void	print_die(t_philo *philo, char *msg)
{
	int	time;

	pthread_mutex_lock(&philo->info->print_mutex);
	time = get_time() - philo->info->start_time;
	printf("[%dms] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print_mutex);
	return ;
}
