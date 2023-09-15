/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:32:07 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/06 14:34:28 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	long long		time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

void	ft_sleep(int delay)
{
	long long	time;

	time = get_time();
	while (get_time() < time + delay)
		usleep(100);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

void	print_it(t_list *philosopher, int n_philo, char *str2)
{
	long long	time;

	pthread_mutex_lock(&philosopher->all->start_lock);
	time = get_time() - philosopher->all->start;
	pthread_mutex_unlock(&philosopher->all->start_lock);
	pthread_mutex_lock(&philosopher->all->lock);
	printf("%lld philosopher %d %s", time, n_philo, str2);
	if (ft_strcmp(str2, "is died\n") == 0)
		return ;
	pthread_mutex_unlock(&philosopher->all->lock);
}
