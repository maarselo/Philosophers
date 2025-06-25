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

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_check_is_digit(char c)
{
	return (48 <= c && c <= 57);
}

static int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int64_t	ft_atoint64(char *str)
{
	int			i;
	int64_t	total;

	i = 0;
	total = 0;
	if (str[i] == '\0')
		return (-1); 
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] && ft_check_is_digit(str[i]))
		total = total * 10 + (str[i++] - '0');
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			if (ft_isascii(str[i]))
				return (-1);
		}
		i++;
	}
	return (total);
}

int	ft_check_entry(int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoint64(argv[i]) < 0)
			return (1);
		i++;
	}
	if (!ft_atoint64(argv[1]))
		return (1);	
	//Nose si debo viligar los otros y hacer exit o igual seguir
	if (argc == 6 && !ft_atoint64(argv[argc - 1]))
		return (1);
	return (0);
}
