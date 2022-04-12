/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:29:26 by wroyal            #+#    #+#             */
/*   Updated: 2021/11/06 17:15:50 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char *str)
{
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		str++;
	}
	return (0);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (0);
}

int	check_death_dop(t_data *data, t_philo ph)
{
	if (ph.cnt_eat > data->must_eat && data->must_eat != -1)
		data->counter++;
	if (ph.das->tm_to_die < time_get() - ph.life && ph.life != -14)
	{
		ph.dead_flag = 1;
		ft_print("died", &ph);
		return (1);
	}
	return (0);
}

void	*check_death(void	*das)
{
	t_data	*data;
	int		i;

	data = (t_data *)das;
	data->counter = 0;
	while (1)
	{
		i = 0;
		while (i < data->cnt_of_ph)
		{
			if (check_death_dop(data, data->ph[i]))
				return (NULL);
			i++;
		}
		if (data->counter >= data->cnt_of_ph)
		{
			pthread_mutex_lock(&data->write_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_death(t_data *data)
{
	pthread_t	death;

	if (pthread_create(&death, NULL, check_death, data))
		return (ft_error("Error\nPthread create error"));
	pthread_join(death, NULL);
	free(data->ph);
	return (0);
}
