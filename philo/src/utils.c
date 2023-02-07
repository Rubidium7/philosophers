/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:23:04 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 20:01:07 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	a_lil_nap(void)
{
	struct timeval	cur_tim;

	gettimeofday(&cur_tim, NULL);
	usleep(cur_tim.tv_usec % 500);
}

void	seepy_cosy(int sleep_time, t_phils *info)
{
	info->start_time = timer();
	while (37)
	{
		info->end_time = timer();
		if (info->death->check || info->death->all_ate)
		{	
			pthread_mutex_unlock(&info->fork);
			pthread_mutex_unlock(&info->next->fork);
			break ;
		}
		if (info->end_time - info->start_time >= sleep_time)
			break ;
		usleep(500);
	}
}

int	you_dead(t_phils *info)
{
	if (info->end_time - info->last_ate >= info->die_t)
	{
		info->death->check = 1;
		stenographer(info, "died");
		pthread_mutex_unlock(&info->fork);
		pthread_mutex_unlock(&info->next->fork);
		return (1);
	}
	else
		return (0);
}

void	stenographer(t_phils *info, char *str)
{
	info->end_time = timer();
	if (info->death->check && ph_strncmp(str, "died", 4))
		return ;
	pthread_mutex_lock(&info->death->writing);
	printf("%lld %d %s\n", info->end_time - info->og_time, info->ind, str);
	if (ph_strncmp(str, "died", 4))
		pthread_mutex_unlock(&info->death->writing);
	info->end_time = timer();
}

int	timer(void)
{
	struct timeval	cur_tim;

	gettimeofday(&cur_tim, NULL);
	return ((cur_tim.tv_sec * 1000) + (cur_tim.tv_usec / 1000));
}
