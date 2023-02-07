/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_feast_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:14:25 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/06 14:06:30 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	good_soup(t_phils *info)
{
	if (you_dead(info))
		return ;
	sem_wait(info->death->forks);
	stenographer(info, "has taken a fork");
	sem_wait(info->death->forks);
	stenographer(info, "has taken a fork");
	if (you_dead(info))
		return ;
	stenographer(info, "is eating");
	seepy_cosy(info->eat_t, info);
	sem_post(info->death->forks);
	sem_post(info->death->forks);
	if (you_dead(info))
		return ;
	info->last_ate = info->end_time;
	info->times_eaten += 1;
}

int	the_phil_lifestyle(t_phils *info)
{
	info->og_time = timer();
	stenographer(info, "is thinking");
	if (!(info->ind % 2))
		usleep(300);
	info->last_ate = timer();
	while (info->hungy == -1 || info->times_eaten < info->hungy)
	{
		if (info->phil_n == 1)
			seepy_cosy(info->die_t, info);
		good_soup(info);
		if (you_dead(info) || (info->hungy > 0 \
			&& info->times_eaten == info->hungy))
			break ;
		stenographer(info, "is sleeping");
		seepy_cosy(info->sleep_t, info);
		if (you_dead(info))
			break ;
		stenographer(info, "is thinking");
	}
	exit(1);
}
