/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:26:39 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:26:40 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
void	ft_printf_data(t_data *data)
{
    int	i;

    if (!data)
    {
        printf("Data is NULL.\n");
        return;
    }

    // Imprimir información general de la estructura t_data
    printf("Total Philosophers: %d\n", data->total_philos);
    printf("Time to Die: %ld\n", data->time_to_die);
    printf("Time to Eat: %ld\n", data->time_to_eat);
    printf("Time to Sleep: %ld\n", data->time_to_sleep);
    printf("Must Meals: %d\n", data->must_meals);
    printf("Stop Routines: %s\n", data->stop_routines ? "true" : "false");

    // Imprimir información de cada filósofo
    if (!data->philos)
    {
        printf("Philosophers array is NULL.\n");
        return;
    }

    for (i = 0; i < data->total_philos; i++)
    {
        printf("\nPhilosopher %d:\n", data->philos[i].philo_number);
        printf("  Total Meals: %d\n", data->philos[i].total_meals);
        printf("  Last Meal: %lu\n", data->philos[i].last_meal);
        printf("  Left Philosopher: %p\n", (void *)data->philos[i].left_philo);
        printf("  Right Philosopher: %p\n", (void *)data->philos[i].right_philo);
    }
}*/

t_data	*ft_init_data(int argc, char **argv)
{
	t_data			*data;
	pthread_mutex_t	write_mutex;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_meals = ft_atol(argv[5]);
	else
		data->must_meals = 0;
	if (pthread_mutex_init(&write_mutex, NULL) != 0)
		return (free(data), NULL);
	data->write_mutex = write_mutex;
	data->stop_routines = false;
	return (data);
}
/*
int	ft_init_philos_routine(t_data *data)
{
	int	i;
	t_philo	*top_philo;
	t_philo	*tmp_philo;

	i = 0;
	top_philo = NULL;
	while (i < data->total_philos)
	{
		tmp_philo = (t_philo *)malloc(sizeof(t_philo));
		if 
	}

	
}*/