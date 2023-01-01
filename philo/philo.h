/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:32:14 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/12/23 09:38:23 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# define START 0
# define ERROR 1
# define STDERR	2
# define EAT 2
# define SLEEP 3
# define THINK 1
# define DEAD 4
# define LEFT_FORK 5
# define RIGHT_FORK 6

typedef struct s_dbase
{
	int				dead;
	int				n_philos;
	int				some_die;
	long long		t_init;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				n_eats;
	int				all_eat;
	long long		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*output;
}	t_dbase;

typedef struct s_philo
{
	int				id;
	long long		curr_time;
	long long		last_eat;
	long long		verify_death;
	int				eat_count;
	int				state;
	int				flag;
	int				f_right;
	int				f_left;
	t_dbase			*dbase;
	pthread_t		td;
}	t_philo;
/*auxs*/
void			exit_free(t_dbase *dbase, t_philo *philo);
void			print_log(t_philo *philo, int state);
int				verify_state(t_philo *philo);
/*init_control*/
int				init(t_dbase *dbase, t_philo **philo, int argc, char *argv[]);
/*philo*/
void			drop_fork(t_philo *philo, int flag);
/*utils*/
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *s);
long long int	get_time_now(void);
#endif
