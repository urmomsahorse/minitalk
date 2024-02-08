#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char *str;

void die(int sig, siginfo_t *info, void *nothing)
{
	exit(0);
}

void send(int sig, siginfo_t *info, void *nothing)
{
//	printf("%d\n", sig);
	static int pos = 0;
	static int i = 0;

	if (str[pos] != '\0')
	{
		if (i < 8)
		{
			if ((str[pos] >> i & 1) == 1)
			{
				kill(info->si_pid, SIGUSR1);
				printf("horse\n");
			}
			else
			{
				kill(info->si_pid, SIGUSR2);
				printf("hi\n");
			}
			i++;
		}
		if (i == 8)
		{
			i = 0;
			pos++;
		}
	}
	else if (str[pos] == '\0')
	{
		if (i < 8)
		{
			kill(info->si_pid, SIGUSR2);
			i++;
		}
	//	if (i == 8)
	//		exit(0);
	}
}

void send_message(int pid)
{
	int pid_c = getpid();
	printf("cl %d\n", pid_c);
	struct sigaction send_bit;
	struct sigaction kill_urself;

	send_bit.sa_handler = 0;
	send_bit.sa_sigaction = send;
	send_bit.sa_flags = SA_SIGINFO;

	kill_urself.sa_handler = 0;
	kill_urself.sa_sigaction = die;
	kill_urself.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &send_bit, NULL);
	sigaction(SIGUSR2, &kill_urself, NULL);
	printf("llego\n");
	kill(pid, SIGUSR1);
	printf("hi\n");
/*	if (check_time == 1)
	{
		printf("resend\n");
		exit;
	}*/
//	send_string(pid, str);
	while (1)
		pause();

}

int main(int argc, char **argv)
{
	str = malloc(1000*sizeof(char));
//	str = NULL;
	//if (str != NULL)
	//	free(str);
	printf("%s\n", argv[1]);
	str = argv[2];
	send_message(atoi(argv[1]));
	free(str);
}















/*
void send_bit(char *str)
{
	int i;

	i = 0;
	while (*str != '\0')
	{
		c = *str;
		while (i < 8)
		{
			if ( == 1)
				kill(pid, SIGUSR1);
			if ( == 0)
				kill (pid, SIGUSR2);
			pause();
			if (count_time == 1)
				exit; // resend
			i++;
		}
	}
}*/
