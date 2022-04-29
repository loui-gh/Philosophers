/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:50:35 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/29 14:46:53 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

void	hello(int n)
{
	t_vars vars;
	pthread_mutex_lock(&vars.write);
	printf("Hello from thread %d\n", n);
	pthread_mutex_unlock(&vars.write);
}

void	ft_putnbr(long n)
{
	char	digit;

	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		digit = n + '0';
		write(1, &digit, 1);
	}
}
