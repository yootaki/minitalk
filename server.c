#include "minitalk.h"

void	send_ack(siginfo_t *siginf)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < 8)
	{
		usleep(50);
		if ((ACK >> i) & 1)
			ret = kill(siginf->si_pid, SIGUSR2);
		else
			ret = kill(siginf->si_pid, SIGUSR1);
		if (ret)
		{
			write(2, "send ack error !\n", 17);
			exit(EXIT_FAILURE);
		}
	}
}

void	signal_handler(int sig, siginfo_t *siginf, void *context)
{
	static char	buf[BUFF_MAX];
	static int	msg_len;
	static int	c;
	static int	bit;

	(void)context;
	c += ((sig & 1) << bit);
	bit += 1;
	if (bit == 8)
	{
		if (!c)
		{
			write(1, buf, ft_strlen(buf));
			write(1, "\n", 1);
			msg_len = 0;
		}
		else if (c == EOT)
			send_ack(siginf);
		else
			buf[msg_len++] = c;
		c = 0;
		bit = 0;
	}
	if (msg_len == BUFF_MAX)
	{
		write(1, buf, ft_strlen(buf));
		msg_len = 0;
	}
}

void	receive_msg(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL))
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &act, NULL))
		exit(EXIT_FAILURE);
}

int	main(void)
{
	pid_t	pid;
	char	*s_pid;

	pid = getpid();
	s_pid = ft_itoa(pid);
	if (!s_pid)
	{
		free(s_pid);
		exit(EXIT_FAILURE);
	}
	write(1, s_pid, ft_strlen(s_pid));
	write(1, "\n", 1);
	free(s_pid);
	while (1)
	{
		receive_msg();
		pause();
	}
	return (0);
}
