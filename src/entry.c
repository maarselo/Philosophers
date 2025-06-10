/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:14:45 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/09 12:14:46 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_is_digit(char c)
{
	return (48 <= c && c <= 57);
}

uint64_t	ft_atoi(char *str)
{
	int			i;
	uint64_t	total;

	i = 0;
	total = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (ft_check_is_digit(str[i]))
		total = total * 10 + (str[i++] - '0');
	return (total);
}

static int	ft_check_numbers(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atouint64(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_entry(char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (ft_check_numbers(argv))
		return (1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] && argv[i][j] == ' ')
			j++;
		while (argv[i][j] && ft_check_is_digit(argv[i][j]))
			j++;
		while (argv[i][j] && argv[i][j] == ' ')
			j++;
		if (argv[i][j] != '\0')
			return (1);
		i++;
	}
	return (0);
}
