/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:33 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/17 13:17:34 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"
//pensar en un static y si muere uno no imprimir nada mas nucna
void	ft_display_message(int message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (message == TAKEN_FORK)
		printf("%lu\t%ld has taken a fork\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	if (message == DROP_FORK)
		printf("%lu\t%ld has droped a fork\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == EATING)
		printf("%lu\t%ld is eating\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == SLEEPING)
		printf("%lu\t%ld is sleeping\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == THINKING)
		printf("%lu\t%ld is thinking\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == ALL_MEALS)
		printf("%lu\t%ld reached the total number of meals\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	else if (message == DIE)
		printf("%lu\t%ld died\n", ft_get_time() - philo->data->start_time, philo->philo_number);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
