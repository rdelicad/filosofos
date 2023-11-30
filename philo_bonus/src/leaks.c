/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:52:33 by rdelicad          #+#    #+#             */
/*   Updated: 2023/11/30 20:33:33 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

void	init_data_table(t_table *t)
{
	t->sem = NULL;
	t->forks = NULL;
	t->sem_meals_eaten = NULL;
	t->child_pids = NULL;
	t->arr_p = NULL;
	t->die_to_time = -1;
	t->eat_to_time = -1;
	t->sleep_to_time = -1;
	t->thing_to_time = -1;
	t->n_philo = -1;
	t->is_dead = 0;
	t->time_init = -1;
	t->cont_eat = 0;
	t->pid = -1;
	t->has_eaten = 0;
}

void	init_data_philos(t_philo *p, t_table *t)
{
	p->t = t;
	p->index = -1;
	p->meals = 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
