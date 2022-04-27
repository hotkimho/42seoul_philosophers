/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:40:55 by hkim2             #+#    #+#             */
/*   Updated: 2022/04/28 02:00:14 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	run_process(t_info *info)
{
	int			idx;
	
	idx = -1;
	while (++idx < info->num_of_philo)
	{
		info->philos[idx].pid = fork();
		if (info->philos[idx].pid == 0)
		{
			routine(&info->philos[idx]);
			exit(SUCCESS);
		}
		usleep(100);
	}
	idx = -1;

	return (SUCCESS);
}

void	philo_free(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		printf("%d %d exit\n", info->philos[idx].id, info->philos[idx].pid);
		waitpid(-1, NULL, 0);
		kill(info->philos[idx].pid, SIGKILL);
		
		
		idx++;
	}

	free(info->philos);
}


int	main(int argc, char **argv)
{
	t_info	info;

	if (parse_argv(argc, argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	info.start_time = get_time();
	//sem_wait(info.sem_stop);
	run_process(&info);
	//sem_wait(info.sem_stop);
	philo_free(&info);
	printf("finish\n");
	return (SUCCESS);
}
