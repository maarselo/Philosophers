/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:12:09 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/09 11:12:13 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments.\n"), 1);
	if (ft_check_entry(argv))
		return (printf("Invalid arguments.\n"), 1);
	data = ft_init_argv(argc, argv);
	if (!data)
		return (printf("Malloc fails.\n"), 1);
}
