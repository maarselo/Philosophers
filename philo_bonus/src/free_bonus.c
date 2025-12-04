/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_free_philo(t_philo *philo)
{
	if (philo->name_sem_state)
		free(philo->name_sem_state);
	if (philo->name_sem_situation)
		free(philo->name_sem_situation);
	philo->left_philo = NULL;
	philo->right_philo = NULL;
	philo->data = NULL;
	free(philo);
}

void	ft_free_philo_list(t_philo *philo_list)
{
	t_philo	*philo_current;
	t_philo	*philo_next;

	philo_current = philo_list;
	philo_current->left_philo->right_philo = NULL;
	while (philo_current)
	{
		philo_next = philo_current->right_philo;
		ft_free_philo(philo_current);
		philo_current = philo_next;
	}
}

void	ft_free_data(t_data *data)
{
	if (data->forks && data->forks != SEM_FAILED)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	if (data->writer && data->writer != SEM_FAILED)
	{
		sem_close(data->writer);
		sem_unlink("/writer");
	}
	if (data->philos && data->total_philos == 1)
		ft_free_philo(data->philos);
	else if (data->philos)
		ft_free_philo_list(data->philos);
	free(data);
}
