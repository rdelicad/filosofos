/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/10 17:03:47 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;

	t = (t_table *)args;
	ft_dead(t);
	return (NULL);
}

int	ft_dead(t_table *t)
{
	int	i;

	i = 0;
	while (t->is_dead != 1)
	{
		i = 0;
		while (i < t->n_philo)
		{
			pthread_mutex_lock(&t->table);
			if (t->n_philo == t->cont_eat)
			{
				pthread_mutex_unlock(&t->table);
				return (0);
			}
			else
				pthread_mutex_unlock(&t->table);
			pthread_mutex_lock(&t->table);
			if (time_start_prog() - t->arr_p[i].last_eat > t->die_to_time)
			{
				pthread_mutex_unlock(&t->table);
				ft_usleep(1);
				printf_action(&t->arr_p[i], "is_dead");
				pthread_mutex_lock(&t->table);
				t->is_dead = 1;
				pthread_mutex_unlock(&t->table);
				return (1);
			}
			else
				pthread_mutex_unlock(&t->table);
			i++;
		}
	}
	return (0);
}

void	printf_action(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->t->table);
	if (p->t->is_dead != 1)
	{
		printf("[%ld] %d %s\n" RESET, time_start_prog() - p->t->time_curr,
			p->index, str);
	}
	pthread_mutex_unlock(&p->t->table);
}

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	if (p->index % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&p->t->table);
		if (p->t->is_dead == 1)
		{
			pthread_mutex_unlock(&p->t->table);
			break ;
		}
		pthread_mutex_unlock(&p->t->table);
		taken_fork(p);
		if (p->t->n_philo == 1)
			return (NULL);
		ft_eat(p);
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(&*p->r_fork);
		if (p->meals == p->t->num_meals)
		{
			pthread_mutex_lock(&p->t->table);
			p->t->cont_eat++;
			pthread_mutex_unlock(&p->t->table);
			return (NULL);
		}
		ft_sleep(p);
		ft_thinking(p);
	}
	return (NULL);
}
