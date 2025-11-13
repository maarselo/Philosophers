/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:26:39 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:26:40 by mvillavi         ###   ########.fr       */
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

static int	ft_check_is_numeric(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] && ft_isspace(argv[i][j]))
			j++;
		while (argv[i][j] &&  (argv[i][j] == '+' || argv[i][j] == '-'))
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_check_positive_numbers(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (ft_atol(argv[i]) <= 0)
			return (1);
	return (0);
}

void	ft_valid_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error_handler(ARGUMENTS_NUMBER);
	else if (ft_check_is_numeric(argc, argv))
		ft_error_handler(ARGS_NOT_NUMERIC);
	else if (ft_check_positive_numbers(argc, argv))
		ft_error_handler(NEGATIVE_NUMBERS);
}		
