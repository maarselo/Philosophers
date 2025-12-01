# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>

void	ft_nigga(int i)
{
	while (true)
	{
		usleep(10);
		printf("saludo desde proceso %d.\n", i);
	}
}


int	main(void)
{
	pid_t	pid[50];

	for (int i= 0; i < 50; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			ft_nigga(i);
	}
	sleep(3);
	setpgid(getpid(), 10000);
	kill(-getpid(), SIGKILL);
	printf("todos los nigga muertos\n");
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