/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_feast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:53:07 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 19:53:15 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*food_counter(void *ptr)
{
	t_phils	*current;
	int		i;

	current = (t_phils *)ptr;
	i = 0;
	while (i != current->phil_n)
	{
		if (current->death->check)
			return (ptr);
		while (current->times_eaten != current->hungy)
			usleep(200);
		current = current->next;
		i++;
	}
	current->death->all_ate = 1;
	return (ptr);
}

void	good_soup(t_phils *info)
{
	if (info->death->check)
		return ;
	pthread_mutex_lock(&info->fork);
	stenographer(info, "has taken a fork");
	pthread_mutex_lock(&info->next->fork);
	stenographer(info, "has taken a fork");
	if (info->death->check)
	{
		pthread_mutex_unlock(&info->fork);
		pthread_mutex_unlock(&info->next->fork);
		return ;
	}
	info->last_ate = timer();
	stenographer(info, "is eating");
	seepy_cosy(info->eat_t, info);
	pthread_mutex_unlock(&info->fork);
	pthread_mutex_unlock(&info->next->fork);
	info->times_eaten += 1;
	if (info->death->check)
		return ;
}


void	*the_watcher(void *ptr)
{
	t_phils *current;
	t_phils	help;

	current = (t_phils *)ptr;
//	while (current->last_ate == 0)
		;
	help.death = current->death;
	pthread_create(&current->watch, NULL, &food_counter, ptr);
	seepy_cosy(current->die_t * 0.9, &help);
	while (37)
	{
		usleep(200);
		if (timer() - current->last_ate >= current->die_t && \
				current->times_eaten != current->hungy)
		{
			current->death->check = 1;
			stenographer(current, "died");
			pthread_mutex_unlock(&current->fork);
			pthread_mutex_unlock(&current->next->fork);
			break ;
		}
	//	if (current->times_eaten == current->hungy)
	//		break ;
		if (current->death->all_ate)
			break ;
		current = current->next;
	}
	return (ptr);
}

void	*the_phil_lifestyle(void *ptr)
{
	t_phils		*info;

	info = (t_phils *)ptr;
	while (info->death->check)
		;
	info->og_time = timer();
	stenographer(info, "is thinking");
	info->last_ate = timer();
//	pthread_create(&info->watch, NULL, &the_watcher, ptr);	
	if (!(info->ind % 2))
		seepy_cosy(info->eat_t, info);
	while (info->hungy == -1 || info->times_eaten < info->hungy)
	{
		if (info->phil_n == 1)
			seepy_cosy(info->die_t, info);
		good_soup(info);
		if (info->death->check || (info->hungy > 0 \
			&& info->times_eaten == info->hungy))
			break ;
		stenographer(info, "is sleeping");
		seepy_cosy(info->sleep_t, info);
		if (info->death->check)
			break ;
		stenographer(info, "is thinking");
		a_lil_nap();
	}
	return (ptr);
}
