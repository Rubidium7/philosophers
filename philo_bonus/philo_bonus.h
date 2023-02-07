/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:04:24 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/06 14:05:24 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_death
{
	sem_t	*forks;
	sem_t	*writing;
	int		dead;
}	t_death;

typedef struct s_phils
{
	struct timeval	cur_tim;
	long long		og_time;
	long long		start_time;
	long long		end_time;
	long long		last_ate;
	pid_t			kiddo;
	int				ind;
	int				phil_n;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				hungy;
	int				times_eaten;
	int				check;
	int				brr;
	t_death			*death;
	struct s_phils	*next;
	struct s_phils	*prev;
}	t_phils;

void	the_feast(t_phils *info);
int		the_phil_lifestyle(t_phils *info);

void	exit_with_style(t_phils *info, t_phils *current, int i);
void	the_after_party(t_phils *beginning);
t_phils	*new_phil(int ind, t_phils *last, t_death *death);

void	seepy_cosy(int sleep_time, t_phils *info);
int		you_dead(t_phils *info);
void	stenographer(t_phils *info, char *str);
int		timer(void);

int		ph_strncmp(const char *s1, const char *s2, size_t n);
int		ph_atoi(const char *str);

#endif
