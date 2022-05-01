/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:41:04 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/02 04:05:38 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_digit(char ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long	value;
	int			sign;

	sign = 1;
	value = 0;
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10;
		value = value + *str - '0';
		str++;
	}
	return (value * sign);
}

int	validate(char **argv)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	i = 0;
	while (argv[++i])
	{
		len = ft_strlen(argv[i]);
		j = -1;
		while (++j < len)
		{
			if (is_digit(argv[i][j]))
				continue ;
			return (error_msg("Invalid argument\n"));
		}
	}
	return (SUCCESS);
}

int	parse_argv(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (error_msg("Invalid argument"));
	validate(argv);
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->num_of_philo < 1 || info->time_to_die < 1
		|| info->time_to_eat < 1 || info->time_to_sleep < 1)
		return (error_msg("Invalid argument"));
	if (argc == 6)
	{
		info->must_eat = ft_atoi(argv[5]);
		if (info->must_eat < 1)
			return (error_msg("Invalid argument"));
	}
	else
		info->must_eat = 0;
	return (SUCCESS);
}
