/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:09:14 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/07 11:56:46 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s3[i] == s4[i] && i < n && s3[i] != '\0' && s4[i] != '\0')
		i++;
	if (i == n && (s3[i] == '\0' || s4[i] == '\0'))
		return (0);
	if (i == n && s3[i - 1] == s4[i - 1])
		return (0);
	return (s3[i] - s4[i]);
}

static int	the_sign2(long int c)
{
	if (c == -1)
		return (0);
	else
		return (-1);
}

int	print_err(int var)
{
	if (var == 1)
		printf("Error: n/o philosophers");
	else if (var == 2)
		printf("Error: time to die");
	else if (var == 3)
		printf("Error: eat time");
	else if (var == 4)
		printf("Error: sleep time");
	else if (var == 5)
		printf("Error: times to eat");
	printf(" includes a non-numeric character\n");
	return (1);
}	

long int	ph_atol(const char *str, t_phils *info, int var)
{
	long int	n;
	long int	i;
	long int	c;

	c = 1;
	i = 0;
	n = 0;
	if (str[i] == '-')
		c = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
		if (n < 0)
			return (the_sign2(c));
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
	{
		info->check = 0;
		return (print_err(var));
	}
	return (n * c);
}
