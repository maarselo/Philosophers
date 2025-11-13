/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:36:37 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:36:38 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			sign = -sign;
		index++;
	}
	if (!ft_isdigit(str[index]))
        return (0);
	while (ft_isdigit(str[index]))
		number = number * 10 + str[index++] - '0';
	return (number * sign);
}
