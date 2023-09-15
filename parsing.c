/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:08:03 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/06 13:36:25 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_allint(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-')
			j++;
		while (str[i][j])
		{
			if (str[i][j] < 48 || str[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_overint(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) > INT_MAX || ft_atoi(str[i]) < INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

int	parsing(t_all *all, int ac, char **av)
{
	int		i;

	if (ac != 5 && ac != 6)
		return (0);
	all->head = NULL;
	i = 0;
	if (!ft_allint(av) || !ft_overint(av) || ft_atoi(av[1]) <= 0
		|| ft_atoi(av[1]) > 200)
		return (0);
	all->n_philosophers = ft_atoi(av[1]);
	all->t_to_die = ft_atoi(av[2]) * 1000;
	all->t_to_eat = ft_atoi(av[3]) * 1000;
	all->t_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		all->num_meals = ft_atoi(av[5]);
	while (i < all->n_philosophers)
		ft_lstadd_back(&all->head, ft_lstnew(i++, all));
	return (1);
}
