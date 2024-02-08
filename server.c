#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void make_server();

static int pid_c;

void add_bit(int pid, int bit)
{
	static char c = 0;
	static char le = 0;
	static int i = 0;
//	write(1, &bit, 1);

	if (i < 8)
	{
		//c = 2 * c + bit;
		c |= ((bit == 1) << i);
		i++;
	/*	if (i == 8)
		{
			write(1, &le, 1);
			i = 0;
			le = 0;
		}*/
	}
	if (i == 8 && c != 0)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
		kill(pid, SIGUSR1);
	}
	else if (i == 8 && c == 0)
	{
		kill(pid, SIGUSR2);
		i = 0;
		pid_c = 0;
		printf("pb: %d\n", pid_c);
		make_server();
	}
	else
		kill(pid, SIGUSR1);
}

void print_bit(int sig, siginfo_t *info, void *nothing)
{
	//printf("yeeyee\n");
	if (pid_c == 0)
	{
		pid_c = info->si_pid;
		printf("pidc %d\n", pid_c);
		kill(pid_c, SIGUSR1);
		return ;
	}
	else if (info->si_pid == pid_c)
	{
	//	printf("yeeyee\n");
		if (sig == SIGUSR1)
			add_bit(pid_c, 1);
		if (sig == SIGUSR2)
			add_bit(pid_c, 0);
	}
	else if (info->si_pid != pid_c)
	{
		printf("wrong c\n");
		kill(info->si_pid, SIGUSR2);
	}
}

void make_server()
{
	struct sigaction print;

	print.sa_handler = 0;
	print.sa_sigaction = &print_bit;
	print.sa_flags = SA_SIGINFO;
	printf("llego\n");
	sigaction(SIGUSR1, &print, NULL);
	sigaction(SIGUSR2, &print, NULL);
	while (1)
		pause();
}

int main()
{
	int pid;

	pid = getpid();
	printf("%d\n", pid);
	pid_c = 0;
	make_server();
}
