/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:06:21 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/12/23 09:29:59 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	load_base(t_dbase *dbase, int argc, char *argv[])
{
	dbase->n_philos = ft_atoi(argv[1]);
	dbase->t_die = ft_atoi(argv[2]);
	dbase->t_eat = ft_atoi(argv[3]);
	dbase->t_sleep = ft_atoi(argv[4]);
	dbase->n_eats = -1;
	dbase->some_die = 0;
	dbase->dead = 0;
	dbase->t_init = get_time_now();
	if (argc == 6)
		dbase->n_eats = ft_atoi(argv[5]);
	dbase->all_eat = 0;
}

void	init_philos(t_dbase *dbase, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < dbase->n_philos)
	{
		pthread_mutex_init(&dbase->forks[i], NULL);
		pthread_mutex_init(&dbase->lock[i], NULL);
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].dbase = dbase;
		philo[i].state = START;
		philo[i].flag = 0;
		philo[i].f_right = 0;
		philo[i].f_left = 0;
		philo[i].verify_death = 0;
		philo[i].last_eat = 1000;
	}
}

int	init(t_dbase *dbase, t_philo **philo, int argc, char *argv[])
{
	if (argc > 6 || argc <= 4)
	{
		ft_putstr_fd("ERROR :wrong number of arguments, it needs 5 or 6\n",
			STDERR);
		free(dbase);
		exit(1);
	}
	load_base(dbase, argc, argv);
	dbase->forks = malloc(sizeof(pthread_mutex_t) * dbase->n_philos);
	dbase->lock = malloc(sizeof(pthread_mutex_t) * dbase->n_philos);
	*philo = (t_philo *)malloc(sizeof(t_philo) * dbase->n_philos);
	if ((argc == 6 && dbase->n_eats <= 0) || (dbase->n_philos < 0
			|| dbase->t_die < 0 || dbase->t_eat < 0 || dbase->t_sleep < 0))
	{
		ft_putstr_fd("ERROR :arguments must be > 0\n", STDERR);
		exit_free(dbase, *philo);
		exit(1);
	}
	if (dbase->n_philos == 0)
		exit_free(dbase, *philo);
	init_philos(dbase, *philo);
	return (0);
}
