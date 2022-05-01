/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:41:21 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 03:57:15 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_msg(t_philo *philo, char *msg)
{
	int	time;

	if (philo->is_death)
		return ;
	sem_wait(philo->info->sem_print);
	time = get_time() - philo->info->start_time;
	if (!philo->is_death)
		printf("[%dms] %d %s\n", time, philo->id, msg);
	sem_post(philo->info->sem_print);
	return ;
}

void	print_die(t_philo *philo, char *msg)
{
	int	time;

	sem_wait(philo->info->sem_print);
	time = get_time() - philo->info->start_time;
	printf("[%dms] %d %s\n", time, philo->id, msg);
	sem_post(philo->info->sem_print);
	return ;
}
