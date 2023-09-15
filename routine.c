/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:48:09 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/06 15:03:17 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	done_eating(t_list *philosopher, t_all *a)
{
	int		cp;
	t_list	*tmp;

	if (!a->num_meals)
		return (1);
	tmp = philosopher;
	cp = 0;
	while (1)
	{
		pthread_mutex_lock(&philosopher->all->meals_lock);
		if (tmp->number_meals >= a->num_meals)
			cp++;
		pthread_mutex_unlock(&philosopher->all->meals_lock);
		tmp = tmp->next;
		if (tmp == philosopher)
			break ;
	}
	if (cp == a->n_philosophers)
		return (0);
	return (1);
}

void	test_death(t_all *a)
{
	t_list	*philosopher;

	philosopher = (t_list *)a->head;
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(&philosopher->all->lte);
		if (!done_eating(philosopher, a))
			return ;
		if (get_time() - philosopher->last_time_eat
			> (philosopher->all->t_to_die / 1000))
		{
			print_it(philosopher, philosopher->content, "is died\n");
			return ;
		}
		pthread_mutex_unlock(&philosopher->all->lte);
		philosopher = philosopher->next;
	}
}

void	ft_odd(t_list *philo)
{
	if (!(philo->content % 2))
		usleep(100);
}

void	*routine(void *philo)
{
	t_list	*philosopher;

	philosopher = (t_list *)philo;
	while (1)
	{
		ft_odd(philosopher);
		pthread_mutex_lock(&philosopher->forchette);
		print_it(philosopher, philosopher->content, " is taking a fork1\n");
		pthread_mutex_lock(&philosopher->next->forchette);
		print_it(philosopher, philosopher->content, " is taking a fork2\n");
		pthread_mutex_lock(&philosopher->all->lte);
		philosopher->last_time_eat = get_time();
		pthread_mutex_unlock(&philosopher->all->lte);
		print_it(philosopher, philosopher->content, " is eating\n");
		pthread_mutex_lock(&philosopher->all->meals_lock);
		philosopher->number_meals++;
		pthread_mutex_unlock(&philosopher->all->meals_lock);
		usleep(philosopher->all->t_to_eat);
		pthread_mutex_unlock(&philosopher->forchette);
		pthread_mutex_unlock(&philosopher->next->forchette);
		print_it(philosopher, philosopher->content, " is sleeping\n");
		usleep(philosopher->all->t_to_sleep);
		print_it(philosopher, philosopher->content, " is thinking\n");
	}
	return (NULL);
}

void	lets_start(t_list **a)
{
	t_list	*tmp;

	tmp = *a;
	while (1)
	{
		pthread_mutex_lock(&tmp->all->start_lock);
		tmp->all->start = get_time();
		pthread_mutex_unlock(&tmp->all->start_lock);
		tmp->last_time_eat = get_time();
		pthread_create(&tmp->philo, NULL, &routine, tmp);
		pthread_detach(tmp->philo);
		tmp = tmp->next;
		if (tmp == *a)
			break ;
	}
}
