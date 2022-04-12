/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:25:32 by wroyal            #+#    #+#             */
/*   Updated: 2021/11/06 16:45:10 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_data *data, int ind)
{
	pthread_mutex_init(&data->ph[ind].l_f, NULL);
	data->ph[ind].das = data;
	data->ph[ind].eat_tm = data->tm_to_eat;
	data->ph[ind].slp_tm = data->tm_to_sleep;
	data->ph[ind].ph_id = ind + 1;
	data->ph[ind].cnt_eat = 0;
	data->ph[ind].dead_flag = 0;
	data->ph[ind].life = -14;
	data->ph[ind].r_f = NULL;
	if (ind == data->cnt_of_ph - 1)
		data->ph[ind].r_f = &data->ph[0].l_f;
	else
		data->ph[ind].r_f = &data->ph[ind + 1].l_f;
}

void	*philosophing(void	*das)
{
	t_philo	*ph;

	ph = (t_philo *)das;
	if (ph->ph_id % 2)
		ft_sleep(10);
	ph->life = time_get();
	while (1)
	{
		forking(ph);
		eating(ph);
		sleeping(ph);
		ft_print("is thinking", ph);
	}
	return (NULL);
}

int	philo_make(t_data *data)
{
	int		i;

	i = 0;
	data->ph = malloc(sizeof(t_philo) * data->cnt_of_ph);
	if (!data->ph)
		return (ft_error("Error\nNot malloced\n"));
	pthread_mutex_init(&data->write_mutex, NULL);
	while (i < data->cnt_of_ph)
	{
		init_philo(data, i);
		if (pthread_create(&data->ph[i].thread, NULL, philosophing, \
		&data->ph[i]))
			return (ft_error("Error\nPthread create error"));
		i++;
	}
	ft_death(data);
	return (0);
}

int	args_pars(int argc, char **argv, t_data *data)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if ((check_args(argv[i])) != 0)
			return (-1);
		i++;
	}
	data->cnt_of_ph = ft_atoi(argv[1]);
	data->tm_to_die = ft_atoi(argv[2]);
	data->tm_to_eat = ft_atoi(argv[3]);
	data->tm_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc >= 5 && argc <= 6)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (ft_error("Error\nNot Malloced\n"));
		data->start_time = time_get();
		if (args_pars(argc, argv, data))
			return (ft_error("Error\nInvalid parameters\n"));
		philo_make(data);
		free(data);
	}
	else
		return (ft_error("Error\nCheck Arguments\n"));
	return (0);
}
