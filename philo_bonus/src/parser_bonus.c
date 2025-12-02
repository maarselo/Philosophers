/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*void	ft_printf_data(t_data *data)
{
    t_philo	*current;
    int		i;

    if (!data)
    {
        printf("Data is NULL.\n");
        return;
    }

	printf("Data Addres: %p\n", data);
    printf("Total Philosophers: %ld\n", data->total_philos);
    printf("Time to Die: %ld\n", data->time_to_die);
    printf("Time to Eat: %ld\n", data->time_to_eat);
    printf("Time to Sleep: %ld\n", data->time_to_sleep);
    printf("Must Meals: %d\n", data->must_meals);
    printf("Sem forks: %s\n", data->forks ? "true" : "false");
    printf("Sem writer: %s\n", data->writer ? "true" : "false");
    printf("Init time: %ld\n", ft_get_time());

    if (!data->philos)
    {
        printf("Philosophers list is NULL.\n");
        return;
    }
    current = data->philos;
    i = 0;
    do
    {
		printf("\nPhilosopher %ld:\n", current->philo_number);
		printf("  Philo addres: %p\n", (void *)current);
    	printf("  Is eating: %s\n", current->is_eating ? "true" : "false");
        printf("  Total Meals: %d\n", current->meals);
        printf("  Limit time: %lu\n", data->start_time + data->time_to_die);
    	printf("  Sem state %s\n", current->sem_state ? "true": "false");
    	printf("  Sem name %s\n", current->sem_name);
		printf("  Thread: %s\n", current->thread ? "creado" : "null");
        printf("  Left Philosopher: %p\n", (void *)current->left_philo);
        printf("  Right Philosopher: %p\n", (void *)current->right_philo);
		printf(" Data address: %p\n", (void *)current->data);
        current = current->right_philo;
        i++;
    } while (current != data->philos && i < data->total_philos);
}*/

t_data	*ft_init_data(int argc, char **argv)
{
	t_data	*data;

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
	sem_unlink("/forks");
	sem_unlink("/writer");
	data->forks = sem_open("/forks", O_CREAT, 0644, ft_atol(argv[1]));
	if (data->forks == SEM_FAILED)
		return (free(data), NULL);
	data->writer = sem_open("/writer", O_CREAT, 0644, 1);
	if (data->writer == SEM_FAILED)
		return (ft_free_data(data), NULL);
	data->start_time = ft_get_time();
	return (data);
}

static t_philo	*ft_init_philo(long philo_number, t_data *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_number = philo_number;
	philo->is_eating = false;
	if (data->must_meals)
		philo->meals = 0;
	else
		philo->meals = -1;
	philo->sem_name = ft_get_semname(philo_number);
	if (!philo->sem_name)
		return (free(philo), NULL);
	philo->sem_state = NULL;
	philo->thread = NULL;
	philo->left_philo = NULL;
	philo->right_philo = NULL;
	philo->data = data;
	return (philo);
}

void	ft_init_philos_data(t_data *data)
{
	long		i;
	t_philo		*philo_top;
	t_philo		*philo_created;

	i = 0;
	philo_top = NULL;
	while (++i <= data->total_philos)
	{
		philo_created = ft_init_philo(i, data);
		if (!philo_created)
		{
			ft_free_data(data);
			ft_free_philo_list(philo_top);
			ft_error_handler(CREATING_VARIABLES);
		}
		if (!philo_top)
			philo_top = philo_created;
		else
		{
			ft_append_philo(philo_created, philo_top);
			ft_link_previous_philo(philo_created, philo_top);
		}
	}
	ft_linked_first_with_last_philo(philo_top);
	data->philos = philo_top;
}
