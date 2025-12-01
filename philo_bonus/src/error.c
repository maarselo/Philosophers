/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error_handler(int error)
{
	if (error == ARGUMENTS_NUMBER)
		return (printf("Invalid number of arguments.\n"), 1);
	else if (error == ARGS_NOT_NUMERIC)
		return (printf("Args can only be a digits.\n"), 1);
	else if (error == NEGATIVE_NUMBERS)
		return (printf("The args must be apositive numbers.\n"), 1);
	else if (error == CREATING_VARIABLES)
		return (printf("Error while creating variables.\n"), 1);
	return (0);
}
