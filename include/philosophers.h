/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:42:14 by marvin            #+#    #+#             */
/*   Updated: 2022/04/22 17:42:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct		s_philo
{
	pthread_t				id;
	int				state;
	int				eaten_num;
	int				time_to_die;
	long long	last_eat_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				is_die;
	struct t_info	*info;
}					t_philo;

typedef struct		s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_info;

//parse_util
int		is_digit(char ch);
int		ft_atoi(const char *str);
int		validate(char **argv);
int		parse_argv(int argc, char **argv, t_info *info);
int		is_space(char c);
//error
int		error_msg(char *message);
int		ft_strlen(char *str);



#endif