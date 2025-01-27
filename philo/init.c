/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:05 by halozdem          #+#    #+#             */
/*   Updated: 2024/12/06 17:56:05 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->message, NULL);
	return (EXIT_SUCCESS);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo - 1)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[i + 1];
		i++;
	}
	data->philo[i].l_fork = &data->forks[i];
	data->philo[i].r_fork = &data->forks[0];
	return (EXIT_SUCCESS);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].chair_no = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].t_data = data;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->nbr_of_times_eat = ft_atol(argv[5]);
	else
		data->nbr_of_times_eat = -1;
	data->completed_philos = 0;
	data->end = false;
	return (EXIT_SUCCESS);
}

int	init_all(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (EXIT_FAILURE);
	if (init_philos(data))
		return (EXIT_FAILURE);
	if (init_forks(data))
		return (EXIT_FAILURE);
	if (init_mutex(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
