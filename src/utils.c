/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:24:06 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/16 14:24:07 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	ft_atol(char *str)
{
	int		index;
	int		sign;
	long	number;

	index = 0;
	sign = 1;
	number = 0;
	while (ft_isspace(str[index]))
		index++;
	while (str[index] && (str[index] == '-' || str[index] == '+'))
	{
		if (str[index] == '-')
			sign = -1;
		else if (str[index] == '+')
			sign = 1;
		index++;
	}
	if (!ft_isdigit(str[index]))
		return (0);
	while (ft_isdigit(str[index]))
		number = number * 10 + str[index++] - '0';
	return (number * sign);
}

unsigned long	ft_get_time(void)
{
	struct timeval	time_struct;
	unsigned long	total_milisec;

	total_milisec = 0;
	gettimeofday(&time_struct, NULL);
	total_milisec = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
	return (total_milisec);
}
