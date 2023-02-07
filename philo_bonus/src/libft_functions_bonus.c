/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:16:01 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/05 15:16:09 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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

static int	the_sign2(int c)
{
	if (c == -1)
		return (0);
	else
		return (-1);
}

int	ph_atoi(const char *str)
{
	int	n;
	int	i;
	int	c;

	c = 1;
	i = 0;
	n = 0;
	if (!(ph_strncmp(str + i, "-2147483648", 11)))
		return (-2147483648);
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
	return (n * c);
}
