/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:48:03 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/03 21:47:43 by Loui :)          ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	minus;
	int	res;
	int	i;

	res = 0;
	minus = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * minus);
}

void	ft_putnbr(int c)
{
	if (c < 0)
	{
		write(1, "-", 1);
		c = -c;
	}
	if (c >= 10)
	{
		ft_putnbr(c / 10);
		ft_putnbr(c % 10); //else ft_putchar((c % 10 + '0');
	}

	else
	{
		c = c + '0';
		write(1, &c, 1);
	}
}