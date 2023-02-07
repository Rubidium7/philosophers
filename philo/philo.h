/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:21:49 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 19:56:59 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

# define INT_MAX 2147483647

typedef struct s_death
{
	int				all_ate;
	int				check;
	pthread_mutex_t	writing;
}	t_death;

typedef struct s_phils
{
	struct timeval	cur_tim;
	long long		og_time;
	long long		start_time;
	long long		end_time;
	long long		last_ate;
	pthread_t		name;
	pthread_t		watch;
	pthread_mutex_t	fork;
	pthread_mutex_t	writing;
	int				ind;
	long int		phil_n;
	long int		die_t;
	long int		eat_t;
	long int		sleep_t;
	long int		hungy;
	int				times_eaten;
	int				check;
	t_death			*death;
	struct s_phils	*next;
	struct s_phils	*prev;
}	t_phils;

void		the_feast(t_phils *info);
void		*the_watcher(void *info);
void		*the_phil_lifestyle(void *ptr);

void		the_after_party(t_phils *beginning, int var);
t_phils		*new_phil(int ind, t_phils *last, t_death *death);

void		a_lil_nap(void);
void		seepy_cosy(int sleep_time, t_phils *info);
int			you_dead(t_phils *info);
void		stenographer(t_phils *info, char *str);
int			timer(void);

void		input_validation(t_phils *info, int ac);

int			ph_strncmp(const char *s1, const char *s2, size_t n);
long int	ph_atol(const char *str, t_phils *info, int var);

#endif
