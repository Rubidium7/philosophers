/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:16:21 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/06 13:09:38 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	exit_with_style(t_phils *info, t_phils *current, int i)
{
	int		status;

	while (i < info->phil_n)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < info->phil_n)
			{
				kill(current->kiddo, 15);
				i++;
				current = current->next;
			}
			break ;
		}
		i++;
	}
	sem_close(info->death->forks);
	sem_close(info->death->writing);
	sem_unlink("phil_forks3737.tmp");
	sem_unlink("phil_writing3737.tmp");
}

void	the_after_party(t_phils *beginning)
{
	t_phils	*current;
	t_phils	*latter;

	current = beginning->next;
	free(beginning->death);
	while (current != beginning && current)
	{
		latter = current;
		current = current->next;
		free(latter);
	}
}

t_phils	*new_phil(int ind, t_phils *last, t_death *death)
{
	t_phils	*new_dude;

	new_dude = malloc(sizeof(t_phils));
	if (!new_dude)
		return (NULL);
	new_dude->check = 1;
	new_dude->times_eaten = 0;
	new_dude->phil_n = last->phil_n;
	new_dude->die_t = last->die_t;
	new_dude->eat_t = last->eat_t;
	new_dude->sleep_t = last->sleep_t;
	new_dude->hungy = last->hungy;
	new_dude->ind = ind;
	new_dude->prev = last;
	new_dude->next = NULL;
	new_dude->death = death;
	return (new_dude);
}
