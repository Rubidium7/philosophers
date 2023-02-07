/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:16:51 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/06 13:53:00 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	death_and_forks(t_phils *info)
{
	t_death	*death;

	death = malloc(sizeof(t_death));
	if (!death)
		exit (1);
	info->death = death;
	death->dead = 0;
	sem_unlink("phil_forks3737.tmp");
	sem_unlink("phil_writing3737.tmp");
	death->forks = sem_open("phil_forks3737.tmp", O_CREAT, 0644, info->phil_n);
	death->writing = sem_open("phil_writing3737.tmp", O_CREAT, 0644, 1);
	return (0);
}

void	invitee_list(t_phils *info, t_phils *current)
{
	int		i;

	i = 1;
	info->ind = 1;
	death_and_forks(info);
	while (i < info->phil_n)
	{
		i++;
		current->next = new_phil(i, current, info->death);
		if (!current->next)
		{
			printf("malloc failed\n");
			return (the_after_party(info));
		}
		current = current->next;
	}
	current->next = info;
	info->prev = current;
	info->check = 1;
}

void	init_values(t_phils *info, char **av, int ac)
{
	info->check = 1;
	info->times_eaten = 0;
	info->phil_n = ph_atoi(av[1]);
	info->die_t = ph_atoi(av[2]);
	info->eat_t = ph_atoi(av[3]);
	info->sleep_t = ph_atoi(av[4]);
	if (ac == 6)
		info->hungy = ph_atoi(av[5]);
	else
		info->hungy = -1;
	if ((ac == 6 && info->hungy < 0) || info->phil_n < 0 || info->die_t < 0)
		info->check = 0;
	else if (info->eat_t < 0 || info->sleep_t < 0 || info->phil_n > 200)
		info->check = 0;
	if (info->check)
	{
		info->check = 0;
		invitee_list(info, info);
		return ;
	}
	printf("incorrect input numbers\n");
	exit(0);
}

void	gathering_the_gang(t_phils *info)
{
	t_phils	*current;
	int		i;

	current = info;
	i = 0;
	while (i < info->phil_n)
	{
		current->kiddo = fork();
		if (current->kiddo < 0)
		{
			printf("%d:th fork didn't get created\n", i + 1);
			break ;
		}
		if (current->kiddo == 0)
			the_phil_lifestyle(current);
		else
			current = current->next;
		i++;
	}
	exit_with_style(info, info, 0);
}

int	main(int ac, char **av)
{
	t_phils	info;

	if (ac != 5 && ac != 6)
		return (printf("incorrect input\n") - 16);
	init_values(&info, av, ac);
	if (!info.check || info.phil_n == 0)
		return (1);
	gathering_the_gang(&info);
	the_after_party(&info);
	return (1);
}
