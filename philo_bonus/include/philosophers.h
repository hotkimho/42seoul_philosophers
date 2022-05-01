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
# include <semaphore.h>
# include <signal.h>
# define SUCCESS 0
# define FAILURE 1
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

typedef struct s_philo
{
	pthread_t		thread;
	pid_t			pid;
	int				id;
	int				state;
	int				num_of_eat;
	int				time_to_die;
	long long		last_eat_time;
	int				is_death;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	char			*fork;
	char			*eat;
	char			*print;
	char			*die;
	char			*stop;
	char			*must;
	sem_t			*sem_fork;
	sem_t			*sem_eat;
	sem_t			*sem_print;
	sem_t			*sem_die;
	sem_t			*sem_stop;
	sem_t			*sem_must_eat;
	t_philo			*philos;
}					t_info;

//parse
int			is_digit(char ch);
int			ft_atoi(const char *str);
int			validate(char **argv);
int			parse_argv(int argc, char **argv, t_info *info);
int			is_space(char c);

//error
int			error_msg(char *message);
int			ft_strlen(char *str);

//init_philo
int			init_info(t_info *info);
int			malloc_philo(t_info *info);
int			init_philo(t_info *info);

//print
void		print_msg(t_philo *philo, char *msg);
void		print_die(t_philo *philo, char *msg);

//philo_util
int			check_death(t_philo *philo);
long long	get_time(void);
void		custom_sleep(long long time);
int			check_must_eat(t_philo *philo);
int			init_sem(t_info *info);
//philo_action
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);

//philo_routine
void		routine(t_philo *philo);
void		*check_must_eat_routine(void *param);
void		*check_routine(void *param);

//philo_sem
int			create_sem(sem_t **sem, char *name, unsigned int value);

#endif