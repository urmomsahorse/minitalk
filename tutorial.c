
void	executed_when_recieved(int sig, siginfo_t *info, void *trash)
{
	printf("i recieved a signal of type %i, yay!", sig);
	printf("the mtfckr with the PID %i, sent me the signal", info->si_pid);
	//your calculus here or something
	if (sig == SIGUSR1)	
}

int	main()
{
	struct sigaction my_action;
	
	my_action.sa_handler = 0;
	//thing that will be executed
	my_action.sa_sigaction = execute_when_recieved;
	//flags, sa_siginfo is needed in case you want to use the info on the funcitton
	my_action.sa_flags = SA_SIGINFO;
	//assing to wich signal will execute the function
	sigaction(SIGUSR1, &my_action, NULL);
	sigaction(SIGUSR2, &my_action, NULL);
	//this function sends the signal you want to the pid you want
	//these are placeholders
	kill(<PID>,<signal>);
	pause();
	printf("reponse arrived");
}

