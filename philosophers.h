/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:00:21 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/06 15:26:21 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> 
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_all
{
	long long		t_to_eat;
	long long		t_to_sleep;
	long long		t_to_die;
	long long		start;
	size_t			end;
	int				num_meals;
	pthread_mutex_t	lte;
	pthread_mutex_t	lock;
	pthread_mutex_t	time;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	meals_lock;
	int				n_philosophers;
	struct s_list	*head;
}				t_all;

typedef struct s_list
{
	int				content;
	struct s_list	*next;
	struct s_list	*prev;
	pthread_mutex_t	forchette;
	pthread_t		philo;
	long long		last_time_eat;
	int				number_meals;
	t_all			*all;
}				t_list;

int			parsing(t_all *a, int ac, char **av);
void		write_error(int n);
void		freestr(char **str);
t_list		*ft_lstnew(int c, t_all *all);
long		ft_atoi(const char *str);
void		ft_lstadd_back(t_list **lst, t_list *neww);
void		ft_sleep(int delay);
int			done_eating(t_list *philosopher, t_all *a);
void		test_death(t_all *a);
void		*routine(void *philo);
void		lets_start(t_list **a);
long long	get_time(void);
void		ft_sleep(int delay);
int			ft_strcmp(char *str1, char *str2);
void		print_it(t_list *philosopher, int n_philo, char *str2);

#endif
