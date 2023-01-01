/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:54:48 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/12/23 09:37:07 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_fork(t_philo *philo, int flag)
{
	pthread_mutex_unlock(&philo->dbase->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->dbase->forks[philo->id
		% philo->dbase->n_philos]);
	philo->f_left = 0;
	philo->f_right = 0;
	if (flag == 0)
	{
		print_log(philo, SLEEP);
		usleep(philo->dbase->t_sleep * 1000);
		print_log(philo, THINK);
	}
}

int	get_forks(t_philo *philo)
{
	if (philo->dbase->n_philos == 1)
		return (1);
	if (pthread_mutex_lock(&philo->dbase->forks[philo->id - 1]) == 0)
	{
		print_log(philo, LEFT_FORK);
		philo->f_left = LEFT_FORK;
	}
	if (pthread_mutex_lock(&philo->dbase->forks
			[philo->id % philo->dbase->n_philos]) == 0)
	{
		print_log(philo, RIGHT_FORK);
		philo->f_right = RIGHT_FORK;
	}
	if (philo->f_left + philo->f_right == 11)
		if (verify_state(philo) == 1)
			return (1);
	return (0);
}

void	*simulation(void *var)
{
	t_philo	*philo;
	int		control;

	philo = var;
	control = 0;
	while (control == 0)
	{
		control = get_forks(philo);
		if (philo->dbase->some_die > 0)
			break ;
		if (control == 1)
			break ;
	}
	return (NULL);
}

void	*control(void *var)
{
	t_philo	**philo;
	int		i;
	int		flag;
	int		qphilos;

	i = -1;
	philo = var;
	flag = 0;
	qphilos = philo[0]->dbase->n_philos;
	if (qphilos == 1)
	{
		printf("%lld %d died\n", get_time_now(), philo[0]->dbase->some_die + 1);
		return (NULL);
	}
	while (1)
	{
		if (philo[0]->dbase->some_die > 0)
		{
			if (philo[0]->dbase->all_eat == philo[0]->dbase->n_philos)
				break ;
			printf("%lld %d died\n", get_time_now(), philo[0]->dbase->some_die);
			break ;
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_dbase		*dbase;
	t_philo		*philo;
	pthread_t	cont;
	int			i;

	i = -1;
	dbase = (t_dbase *)malloc(sizeof(t_dbase));
	if (init(dbase, &philo, argc, argv))
	{
		free(dbase);
		return (ERROR);
	}
	while (++i < dbase->n_philos)
	{
		pthread_create(&philo[i].td, NULL, &simulation, &philo[i]);
		usleep(100);
	}
	pthread_create(&cont, NULL, &control, &philo);
	i = -1;
	while (++i < dbase->n_philos)
		pthread_join(philo[i].td, NULL);
	pthread_join(cont, NULL);
	exit_free(dbase, philo);
	return (0);
}
