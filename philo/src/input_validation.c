/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:13:15 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 19:58:09 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	input_validation(t_phils *info, int ac)
{
	if (info->phil_n <= 0 || info->phil_n > INT_MAX)
	{
		printf("Error: n/o philosophers out of range\n");
		info->check = 0;
	}
	if (info->die_t <= 0 || info->die_t > INT_MAX)
	{
		printf("Error: time to die out of range\n");
		info->check = 0;
	}
	if (info->eat_t <= 0 || info->eat_t > INT_MAX)
	{
		printf("Error: eat time out of range\n");
		info->check = 0;
	}
	if (info->sleep_t <= 0 || info->sleep_t > INT_MAX)
	{
		printf("Error: sleep time out of range\n");
		info->check = 0;
	}
	if ((info->hungy < 0 && ac == 6) || info->hungy > INT_MAX)
	{
		printf("Error: times to eat out of range\n");
		info->check = 0;
	}
}
