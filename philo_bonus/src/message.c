/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_display_message(int message, t_philo *philo)
{
	sem_wait(philo->data->writer);
	if (message == TAKEN_FORK)
		printf("%lu\t%ld has taken a fork\n",
			ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == EATING)
		printf("%lu\t%ld is eating\n",
			ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == SLEEPING)
		printf("%lu\t%ld is sleeping\n",
			ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == THINKING)
		printf("%lu\t%ld is thinking\n",
			ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == ALL_MEALS)
		printf("%lu\t%ld reached the total number of meals\n",
			ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == DIE)
		printf("%lu\t%ld died\n",
			ft_get_time() - philo->data->start_time, philo->philo_number);
	sem_post(philo->data->writer);
}
