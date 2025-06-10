/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:33:05 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/10 11:33:06 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/// No hya funcio nsol opara boorar los threads y falt aimplementar os dos tipos de free si falla mutex o mmientrs el fhilo se crea
void	ft_free_philo(int total_philos, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		/////////////pthread
	}
}

void	ft_free_data(t_data *data)
{
	pthread_mutex_destroy(&data->write_lock);
	ft_free_philo(data->num_philos, data->philo);
	free(data);
}