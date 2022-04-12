/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:25:32 by wroyal            #+#    #+#             */
/*   Updated: 2021/11/04 18:57:01 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_data *data, int ind)
{
	data->ph[ind].das = data;
	data->ph[ind].eat_tm = data->tm_to_eat;
	data->ph[ind].slp_tm = data->tm_to_sleep;
	data->ph[ind].ph_id = ind + 1;
	data->ph[ind].cnt_eat = 0;
	data->ph[ind].life = time_get();
}

int	ft_life(t_data *data, int i)
{
	pthread_t	ded;

	data->pids_mas[i] = fork();
	if (data->ph[i].pid < 0)
	{
		write(2, "bad fork\n", 9);
		exit(0);
	}
	if (data->pids_mas[i] == 0)
	{
		if (i % 2)
			ft_sleep(10);
		if (pthread_create(&ded, NULL, ft_dead, &data->ph[i]))
			return (ft_error("Error\nPthread create error"));
		while (1)
			activity(&data->ph[i]);
		exit(0);
	}
	if (i == data->cnt_of_ph - 1)
		ft_wait(data);
	return (0);
}

int	philo_make(t_data *data)
{
	int		i;

	i = 0;
	data->pids_mas = malloc(sizeof(pid_t) * data->cnt_of_ph);
	if (!data->pids_mas)
		return (ft_error("Not malloced"));
	data->ph = malloc(sizeof(t_philo) * data->cnt_of_ph);
	if (!data->ph)
		return (ft_error("Not malloced"));
	sem_unlink("/sema");
	data->sem_frk = sem_open("/sema", O_CREAT, 0666, data->cnt_of_ph);
	sem_unlink("/print");
	data->sem_wrt = sem_open("/print", O_CREAT, 0666, 1);
	sem_unlink("/dead");
	data->sem_dth = sem_open("/dead", O_CREAT, 0666, 1);
	while (i < data->cnt_of_ph)
	{
		init_philo(data, i);
		ft_life(data, i);
		i++;
	}
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
		data = (malloc(sizeof(t_data)));
		if (!data)
			return (ft_error("Error\nNot Malloced\n"));
		data->start_time = time_get();
		data->dead_flag = 0;
		if (args_pars(argc, argv, data))
			return (ft_error("Error\nInvalid parameters\n"));
		philo_make(data);
		free(data);
	}
	else
		return (ft_error("Error\nCheck Arguments\n"));
	return (0);
}
