#include <stdio.h>
#include <fcntl.h>           /* Pour les constantes O_* */
#include <sys/stat.h>        /* Pour les constantes « mode » */
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

	long			start_timestamp;
	int				is_dead;
	int				finished_philos;

	pthread_mutex_t	lock_fork;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_eat;
}					t_data;

long	ft_atoi(const char *str)
{
	long		result;
	int			i;
	int			n;

	n = 0;
	result = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] < '0' || str[i + 1] > '9')
			return (0);
		if (str[i] == '-')
			n = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (n)
		result = result * -1;
	return (result);
}

void kill_all_child(pid_t *pid, int philo_nbr)
{
	int i;

	i = 0;
	while (i < philo_nbr)
		kill(pid[i++], 1);
}

void	get_data(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	data->finished_philos = 0;
	if (argv[5])
	 	data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
}

void	*philo_check_death(void *p)
{

}

int child_func(sem_t *semaphore, t_data data, int index)
{
	struct timeval current_time;
	pthread_t philo_thread;

	//pthread_create(&philo_thread, NULL, philo_check_death, &data);
	if (index % 2 == 1)
		usleep(10000);
	while (1)
	{
		//if (i == 2)
		//	exit (1);
		sem_wait(semaphore);
		gettimeofday(&current_time, NULL);
		printf("%ld %d took a first fork\n", ((current_time.tv_sec * 1000000 + current_time.tv_usec) / 1000), index + 1);
		sem_wait(semaphore);
		gettimeofday(&current_time, NULL);
		printf("%ld %d took a second fork\n", ((current_time.tv_sec * 1000000 + current_time.tv_usec) / 1000), index + 1);
		printf("%ld %d is eating\n", ((current_time.tv_sec * 1000000 + current_time.tv_usec) / 1000), index + 1);
		usleep(data.time_to_eat * 1000);
		sem_post(semaphore);
		sem_post(semaphore);
		gettimeofday(&current_time, NULL);
		printf("%ld %d is sleeping\n", ((current_time.tv_sec * 1000000 + current_time.tv_usec) / 1000), index + 1);
		usleep(data.time_to_sleep * 1000);
		gettimeofday(&current_time, NULL);
		printf("%ld %d is thinking\n", ((current_time.tv_sec * 1000000 + current_time.tv_usec) / 1000), index + 1);
		//printf("%d droped first fork\n", index + 1);
		//printf("%d droped second fork\n", index + 1);
		//sleep(10);
	}
	return (0);
}

int create_childs(sem_t *semaphore, pid_t *pid, t_data data)
{
	int i;

	i = 0;
	while (i < data.number_of_philosophers)
	{
		pid[i] = fork();
		if (pid[i] == 0) 
			child_func(semaphore, data, i);
		i++;
	}
	return 0;
}

int main(int argc, char **argv)
{
	t_data data;
	sem_unlink("sem");
	sem_t *semaphore;
	int i = 0;
	pid_t *pid;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong input\n");
		return 1;
	}
	get_data(&data, argv);
	semaphore = sem_open("sem", O_CREAT, 0666, data.number_of_philosophers);
	pid = malloc(data.number_of_philosophers * sizeof(pid_t));
	create_childs(semaphore, pid, data);
	int status = 0;
	i = 0;
	while(waitpid(0, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			kill_all_child(pid, data.number_of_philosophers);
			printf("Exit code 1 received\n");
		}
		printf("Parent received child %d with status %d\n", i + 1, WEXITSTATUS(status));
		i++;
	}
	printf("Im the parent\n");
	sem_unlink("sem");
}