/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:10:28 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/23 21:08:06 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	normi_check_digits(int j)
{
	j++;
	printf("Error: list may only contain digits\n");
	exit (EXIT_FAILURE);
}

void	check_digits(char **argv)
{
	char	*c;
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		c = argv[i];
		j = 0;
		if (ft_strlen(c) == 0)
			normi_check_digits(j);
		if (ft_strlen(c) > 1 && c[0] == '-')
			j++;
		while (c[j] != '\0')
		{
			if (ft_isdigit(c[j]) == 0)
				normi_check_digits(j);
			j++;
		}
		i++;
	}
}

int	ft_handle_input_errors(int argc, char *argv[])
{
	check_digits(argv);
	if (argc != 5 && argc != 6)
	{
		printf("Error: too few or too many args entered\n");
		return (1);
	}

	return 0;
}
int		ft_init_vars(int argc, char *argv[], t_vars *vars)
{
	vars->number_of_philosophers = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->forks_on_table = vars->number_of_philosophers;
	if (argc == 6)
		vars->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (0);
}