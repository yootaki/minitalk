#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

void	send_ack(siginfo_t *siginf)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < 8)
	{
		usleep(50);
		if (('\006' >> i) & 1)
			ret = kill(siginf->si_pid, SIGUSR2);
		else
			ret = kill(siginf->si_pid, SIGUSR1);
		if (ret)
			exit(EXIT_FAILURE);
	}
}

void	signal_handler(int sig, siginfo_t *siginf, void *context)
{
	static char	buf[1000];
	static int	msg_len;
	static int	c;
	static int	size;

	(void)context;
	c += ((sig & 1) << size);
	size += 1;
	if (size == 8)
	{
		if (c == '\004')
			send_ack(siginf);
		else if (c)
			buf[msg_len++] = c;
		else
		{
			write(1, buf, ft_strlen(buf));
			msg_len = 0;
		}
		c = 0;
		size = 0;
	}
	if (msg_len == 1000)
	{
		write(1, buf, ft_strlen(buf));
		msg_len = 0;
	}
}

int	receive_msg(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL))
		return (1);
	if (sigaction(SIGUSR2, &act, NULL))
		return (1);
	return (0);
}

int	main(void)
{
	pid_t	pid;
	char	*s_pid;

	/* pidを取得 & ターミナルに表示 */
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

	/* シグナルを受け取るため待機 */
	while (1)
	{
		if(receive_msg())
		{
			free(s_pid);
			exit(EXIT_FAILURE);
		}
		pause();
	}

	return (0);
}

// __attribute__((destructor))
// void    destructor(void)
// {
//     int    status;

//     status = system("leaks server &> leaksout");
//     if (status)
//     {
//         write(2, "leak!!!\n", 8);
//         system("cat leaksout >/dev/stderr");
//         exit(1);
//     }
// }
