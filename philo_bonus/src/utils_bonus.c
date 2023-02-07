/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:17:09 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/06 14:06:32 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	seepy_cosy(int sleep_time, t_phils *info)
{
	info->start_time = timer();
	while (37)
	{
		if (you_dead(info))
			return ;
		info->end_time = timer();
		if (info->end_time - info->start_time >= sleep_time)
			break ;
		usleep(50);
	}
}

int	you_dead(t_phils *info)
{
	if (info->end_time - info->last_ate >= info->die_t || info->death->dead)
	{
		if (!info->death->dead)
			stenographer(info, "died");
		info->death->dead = 1;
		return (1);
	}
	else
		return (0);
}

void	stenographer(t_phils *info, char *str)
{
	info->end_time = timer();
	sem_wait(info->death->writing);
	printf("%lld #%d %s\n", info->end_time - info->og_time, info->ind, str);
	sem_post(info->death->writing);
	info->end_time = timer();
}

int	timer(void)
{
	struct timeval	cur_tim;

	gettimeofday(&cur_tim, NULL);
	return ((cur_tim.tv_sec * 1000) + (cur_tim.tv_usec / 1000));
}
