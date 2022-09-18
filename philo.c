#include "philo.h"

// void	*function(void *p)
// {
// 	// Print value received as argument:
// 	printf("Value recevied as argument in starting routine: ");
// 	printf("%i\n", *(int *)p);
// 	// Return reference to global variable:
// }

int	main(int argc, char **argv)
{
	// pthread_t t[argc - 1];
	// int i;
	t_data data;
	// if (argc != 5 && argc != 5)
	// {
	// 	printf("Wrong inputs\n");
	// 	exit(1);
	// }
	data.number_of_philosophers = atoi(argv[1]);
	// data.time_to_die = argv[2];
	// data.time_to_eat = argv[3];
	// data.time_to_sleep = argv[4];
	// if (argv[5])
	// 	data.number_of_times_each_philosopher_must_eat = argv[5];
	// i = 1;
	// while (argv[i])
	// {
	// 	int j = 10;
	// 	pthread_create(t[i - 1], NULL, function, &data);
	// 	pthread_join(t[i - 1], NULL);
	// }
	int *philos;
	philos = malloc(data.number_of_philosophers * sizeof(int));
	memset((void *)philos, 1, data.number_of_philosophers*sizeof(int));
	// int i = data.number_of_philosophers;
	// while (i)
	printf("%d\n", philos[0]);
}