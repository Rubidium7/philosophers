/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:57:42 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 19:57:07 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int death_comes(t_phils *info)
{
	t_death	*death;
	
	death = malloc(sizeof(t_death));
	if (!death)
		return (0);
	info->death = death;
	death->check = 1;
	death->all_ate = 0;
	pthread_mutex_init(&death->writing, NULL);
	return (1);
}

void	invitee_list(t_phils *info, t_phils *current)
{
	int		i;

	i = 1;
	if (!death_comes(info))
		return (the_after_party(info, 0));
	info->ind = 1;
	while (i < info->phil_n)
	{
		i++;
		current->next = new_phil(i, current, info->death);
		if (!current->next)
		{
			printf("malloc failed\n");
			return (the_after_party(info, 1));
		}
			current = current->next;
	}
	current->next = info;
	info->prev = current;
	info->check = 1;
}

void	init_values(t_phils *info, char **av, int ac)
{
	pthread_mutex_init(&info->fork, NULL);
	info->check = 1;
	info->times_eaten = 0;
	info->phil_n = ph_atol(av[1], info, 1);
	info->die_t = ph_atol(av[2], info, 2);
	info->eat_t = ph_atol(av[3], info, 3);
	info->sleep_t = ph_atol(av[4], info, 4);
	if (ac == 6)
		info->hungy = ph_atol(av[5], info, 5);
	else
		info->hungy = -1;
	input_validation(info, ac);
	if (info->check)
	{
		info->check = 0;
		invitee_list(info, info);
		return ;
	}
	the_after_party(info, 0);
}

void	gathering_the_gang(t_phils *info)
{
	t_phils	*current;
	int		i;

	current = info;
	i = 0;
	while (i < info->phil_n)
	{
		if (pthread_create(&current->name, NULL, \
				&the_phil_lifestyle, (void *)(current)))
		{
			printf("%d:th thread didn't get created\n", i + 1);
			break ;
		}
		current = current->next;
		i++;
	}
	info->death->check = 0;
	info->last_ate = 0;
	the_watcher((void *)(info));
//	printf("\n\ncur dif is %lld\n\n\n\n", current->prev->end_time - current->prev->last_ate);
	while (i)
	{
		pthread_join(current->name, NULL);
		current = current->next;
		i--;
	}
}

int	main(int ac, char **av)
{
	t_phils	info;

	if (ac != 5 && ac != 6)
		return (printf("incorrect input\n") - 16);
	init_values(&info, av, ac);
	if (!info.check || info.phil_n == 0)
		return (0);
	gathering_the_gang(&info);
	the_after_party(&info, 1);
	return (1);
}
