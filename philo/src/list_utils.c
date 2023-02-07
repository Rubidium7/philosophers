/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:45:09 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 16:09:22 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	the_after_party(t_phils *beginning, int var)
{
	t_phils	*current;
	t_phils	*latter;

	pthread_mutex_destroy(&beginning->fork);
	if (!var)
		return ;
	current = beginning->next;
	pthread_mutex_destroy(&beginning->death->writing);
	free(beginning->death);
	while (current != beginning && current)
	{
		latter = current;
		current = current->next;
		pthread_mutex_destroy(&latter->fork);
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
	pthread_mutex_init(&new_dude->fork, NULL);
	pthread_mutex_init(&new_dude->writing, NULL);
	return (new_dude);
}
