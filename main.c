# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>

void	*ft_negro(void *hola)
{
	int	counter = 0;
	while (true)
	{
		if (counter == 4)
			return (NULL);
		usleep(1000);
		printf("negro");
		counter++;
		malloc(1000);
	}
}

void	ft_nigga(int i)
{
	pthread_t pthread;
	printf("saludo desde proceso %d.\n", i);
	pthread_create(&pthread, NULL, ft_negro, NULL);
}


int	main(void)
{
	pid_t	pid[50];

	for (int i= 0; i < 1; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			ft_nigga(i);
	}
	sleep(5);
	//setpgid(getpid(), 10000);
	//kill(-getpid(), SIGKILL);
	//printf("todos los nigga muertos\n");
	//kill(pid[0], SIGKILL);
	printf("matado por primera vez.\n");	
	kill(pid[0], SIGKILL);
	//printf("fin del programa\n");	
	/*for (int i= 0; i < 50; i++){
		if (pid[i] != 0)
		{
			kill(pid[i], SIGKILL);
			printf("acabado pid: %d index ->%d.\n", pid[i], i);
		}
	}
	printf("eliminado tdo.\n");
	printf("pid del padre->%d", getpid());*/
}