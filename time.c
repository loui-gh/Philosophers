		struct timeval current_time;
gettimeofday(&current_time, NULL);
//arg[0] = time value (struct)
	//arg[1] = time zone, however obsolete and usually set to NULL
	long		start_time;
	 start_time= current_time.tv_usec;
	  ft_putnbr_fd(start_time);
	pthread_mutex_init(ptr.mutex, NULL);