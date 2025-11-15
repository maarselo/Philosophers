/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:59:51 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 19:59:54 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//tengo que pasarlo algo de algunamanera que si stopde data que salga 
//errores tanto para que acabe

void	ft_free_philos_list(t_philo *philo_list)
{
	t_philo	*philo_free;
	t_philo	*philo_next;

	if (!philo_list)
		return ;
	philo_free = philo_list;
	while (philo_free)
	{
		philo_next = philo_free->right_philo;
		philo_free->left_philo = NULL;
		pthread_join(philo_free->pthread, NULL);
		pthread_mutex_destroy(&philo_free->fork);
		philo_free->data = NULL;
		free(philo_free);
		philo_free = philo_next;
	}
}

void	ft_free_data(t_data *data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->write_mutex);
		if (data->philos)
			ft_free_philos_list(data->philos);
		free(data);
	}
}



void	ft_free_specified_philos(int philos_numbers, t_data *data)
{

}
