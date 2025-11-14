/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:59:51 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 19:59:54 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_valid_arguments(argc, argv))
		return (1);
	data = ft_init_data(argc, argv);
	if (!data)
		return (ft_error_handler(CREATING_VARIABLES));
	//ft_init_philos()
}
