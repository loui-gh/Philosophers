void	*ft_thread_philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		i;

	philo = (t_philo *)arg;
	table = philo->table;
	i = philo->id;
	while (1)
	{
		if (table->is_dead == 1)
			return (NULL);
		if (table->is_taken[i] == 1)
		{
			if (table->eat[i] == 1)
			{
				ft_eat(philo);
				table->eat[i] = 0;
			}
			else
			{
				ft_sleep(philo);
				table->eat[i] = 1;
			}
		}
		else
		{
			ft_think(philo);
			ft_take_fork(philo);
			table->is_taken[i] = 1;
			table->eat[i] = 1;
		}
	}
	return (NULL);
}