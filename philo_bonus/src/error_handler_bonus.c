/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_error_handler(int error)
{
	if (error == ARGUMENTS_NUMBER)
		printf("Invalid number of arguments.\n");
	else if (error == ARGS_NOT_NUMERIC)
		printf("Args can only be a digits.\n");
	else if (error == NEGATIVE_NUMBERS)
		printf("The args must be apositive numbers.\n");
	else if (error == CREATING_VARIABLES)
		printf("Error while creating variables.\n");
	else if (error == CREATING_PROCESSES)
		printf("Error while creating processes.\n");
	else if (error == CREATING_THREADS)
	{
		printf("Error while creating variables.\n");
		return ;
	}
	exit(ERROR);
}
