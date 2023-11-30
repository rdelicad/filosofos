/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:56:34 by rdelicad          #+#    #+#             */
/*   Updated: 2023/11/30 20:42:44 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_last_eat(t_philo *p)
{
	sem_wait(p->t->sem);
	p->last_eat = time_start_prog();
	sem_post(p->t->sem);
}

void	ft_meals(t_philo *p)
{
	sem_wait(p->t->sem);
	p->meals++;
	sem_post(p->t->sem);
}

void	ft_exit_for_eat(t_table *t)
{
	/* if (t->num_meals == -1)
		return (0);
	sem_wait(t->sem);
	if (t->cont_eat == t->n_philo)
	{
		sem_post(t->sem);
		return (1);
	}
	else
		sem_post(t->sem); */
	for (int i = 0; i < t->n_philo * t->num_meals; i++)
    {
        sem_wait(t->sem_meals_eaten);
    }
    printf("Todos los filósofos han comido %d veces.\n", t->num_meals);
    exit(0);
	//return (0);
}

void	create_fork(t_table *t, t_philo *p)
{
	int i;

	i = 0;
	while (i < t->n_philo)
	{
		t->pid = fork();
		if (t->pid == 0)
		{
			p->index = i + 1;
			routine_philos(p);
			exit(0);
		}
		else
			set_arr_philos(t, p, i);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		waitpid(-1, NULL, 0);
}