/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:12:40 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/28 20:20:51 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	normi_check_digits(int j)
{
	j++;
	printf("Error: list may only contain digits\n");
	exit (EXIT_FAILURE);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
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
		{
			printf("Error: list may only contain +ve numbers\n");
			exit (EXIT_FAILURE);
		}
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
	return (0);
}
