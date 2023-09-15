/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:24 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/06 13:27:06 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_error(int n)
{
	write(n, "Eroor\n", 6);
	exit(1);
}

void	freestr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

t_list	*ft_lstnew(int c, t_all *all)
{
	t_list	*n;

	n = (t_list *)malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	pthread_mutex_init(&n->forchette, NULL);
	pthread_mutex_init(&all->lock, NULL);
	pthread_mutex_init(&all->lte, NULL);
	pthread_mutex_init(&all->time, NULL);
	pthread_mutex_init(&all->start_lock, NULL);
	pthread_mutex_init(&all->meals_lock, NULL);
	n->content = c + 1;
	n->next = NULL;
	n->prev = NULL;
	n->number_meals = 0;
	n->all = all;
	return (n);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	nakis;

	i = 0;
	res = 0;
	nakis = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			nakis *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * nakis);
}

void	ft_lstadd_back(t_list **lst, t_list *neww)
{
	t_list	*t;

	if (lst && neww)
	{
		if (!*lst)
		{
			*lst = neww;
			neww->next = *lst;
			neww->prev = *lst;
		}
		else
		{
			t = *lst;
			while (t->next != *lst)
				t = t->next;
			t->next = neww;
			neww->next = *lst;
			neww->prev = t;
			(*lst)->prev = neww;
		}
	}
}
