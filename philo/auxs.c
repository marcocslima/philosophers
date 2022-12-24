/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:07:44 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/12/24 00:32:01 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_free(t_dbase *dbase, t_philo *philo)
{
	free(dbase->forks);
	free(dbase->lock);
	free(philo);
	free(dbase);
}

void	print_log(t_philo *philo, int state)
{
	long long	now;
	long long	isdead;

	pthread_mutex_lock(&philo->dbase->output);
	isdead = get_time_now() - philo->last_eat;
	if (philo->dbase->some_die == 0 && isdead < philo->dbase->t_die)
	{
		now = get_time_now();
		if ((state == LEFT_FORK || state == RIGHT_FORK)
			&& philo->dbase->dead == 0)
			printf("%llu %d has taken a fork \n", now, philo->id);
		else if (state == THINK && philo->dbase->dead == 0)
			printf("%llu %d is thinking \n", now, philo->id);
		else if (state == EAT && philo->dbase->dead == 0)
			printf("%llu %d is eating \n", now, philo->id);
		else if (state == SLEEP && philo->dbase->dead == 0)
			printf("%llu %d is sleeping \n", now, philo->id);
		else if (state == DEAD)
			printf("%llu %d died \n", now, philo->id);
	}
	pthread_mutex_unlock(&philo->dbase->output);
}

int	verify_complement(t_philo *philo)
{
	if (philo->dbase->all_eat == philo->dbase->n_philos)
	{
		drop_fork(philo, 1);
		pthread_mutex_lock(&philo->dbase->sd);
		philo->dbase->some_die = philo->id;
		philo->dbase->t_death = get_time_now();
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->dbase->sd);
		return (ERROR);
	}
	else
	{
		print_log(philo, EAT);
		usleep(philo->dbase->t_eat * 1000);
		philo->last_eat = get_time_now();
		pthread_mutex_lock(&philo->dbase->lock[philo->id - 1]);
		philo->eat_count++;
		if (philo->eat_count == philo->dbase->n_eats)
			philo->dbase->all_eat++;
		pthread_mutex_unlock(&philo->dbase->lock[philo->id - 1]);
		drop_fork(philo, 0);
	}
	return (0);
}

int	verify_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->dbase->lock[philo->id - 1]);
	philo->verify_death = get_time_now() - philo->last_eat;
	if (philo->verify_death >= philo->dbase->t_die)
	{
		pthread_mutex_lock(&philo->dbase->sd);
		philo->dbase->some_die = philo->id;
		philo->dbase->t_death = get_time_now();
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->dbase->sd);
	}
	pthread_mutex_unlock(&philo->dbase->lock[philo->id - 1]);
	verify_complement(philo);
	return (0);
}
