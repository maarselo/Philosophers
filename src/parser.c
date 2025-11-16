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
    t_philo	*current;
    int		i;

    if (!data)
    {
        printf("Data is NULL.\n");
        return;
    }
	printf("Data Addres: %p\n", data);
    printf("Total Philosophers: %d\n", data->total_philos);
    printf("Time to Die: %ld\n", data->time_to_die);
    printf("Time to Eat: %ld\n", data->time_to_eat);
    printf("Time to Sleep: %ld\n", data->time_to_sleep);
    printf("Must Meals: %d\n", data->must_meals);
    printf("Stop Routines: %s\n", data->stop_routines ? "true" : "false");

    if (!data->philos)
    {
        printf("Philosophers list is NULL.\n");
        return;
    }

    current = data->philos;
    i = 0;
    do
    {
		printf("\nPhilosopher %d:\n", current->philo_number);
		printf("  Philo addres: %p\n", (void *)current);
        printf("  Total Meals: %d\n", current->total_meals);
        printf("  Last Meal: %lu\n", current->last_meal);
        printf("  Left Philosopher: %p\n", (void *)current->left_philo);
        printf("  Right Philosopher: %p\n", (void *)current->right_philo);
		printf(" Data address: %p\n", (void *)current->data);
        current = current->right_philo;
        i++;
    } while (current != data->philos && i < data->total_philos);
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
	data->philos = NULL;
	if (pthread_mutex_init(&write_mutex, NULL) != 0)
		return (free(data), NULL);
	data->write_mutex = write_mutex;
	data->stop_routines = false;
	return (data);
}

static t_philo	*ft_init_philo(int i, t_data *data)
{
	t_philo	*philo_created;

	philo_created = (t_philo *)malloc(sizeof(t_philo));
	if (!philo_created)
		return (NULL);
	philo_created->philo_number = i;
	if (pthread_mutex_init(&philo_created->fork, NULL) != 0)
		return (free(philo_created), NULL);
	philo_created->left_philo = NULL;
	philo_created->right_philo = NULL;
	philo_created->total_meals = 0;
	philo_created->data = data;
	return (philo_created);
}

int	ft_init_philos_data(t_data *data)
{
	int				i;
	t_philo			*top_philo;
	t_philo			*philo_created;

	i = 0;
	top_philo = NULL;
	while (++i <= data->total_philos)
	{
		philo_created = ft_init_philo(i, data);
		if (!philo_created)
			return (ft_free_philos_list(top_philo), ft_free_data(data), 1);
		if (!top_philo)
			top_philo = philo_created;
		else
		{
			ft_append_philo(philo_created, top_philo);
			ft_link_previous_philo(philo_created, top_philo);
		}
	}
	ft_linked_first_with_last_philo(top_philo);
	data->philos = top_philo;
	return (0);
}
