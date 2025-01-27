/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:20 by halozdem          #+#    #+#             */
/*   Updated: 2024/12/06 17:05:07 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str[i])
		return (0);
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

size_t	get_current_time(void)
{
	size_t			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(size_t ms)
{
	size_t	time;

	time = get_current_time() + ms;
	while (get_current_time() < time)
		if (usleep(100) != 0)
			return ;
}

int	ft_print(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->t_data->message);
	pthread_mutex_lock(&philo->t_data->end_mutex);
	if (philo->t_data->end == false)
	{
		printf("%zu %d %s\n", get_current_time() - philo->t_data->start_time,
			philo->id, state);
	}
	pthread_mutex_unlock(&philo->t_data->end_mutex);
	pthread_mutex_unlock(&philo->t_data->message);
	return (EXIT_SUCCESS);
}
