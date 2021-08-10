#include "includes/minitalk.h"

int	check_pid(const char *str)
{
	int	num;
	int	len;
	int	i;

	num = 0;
	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (!ft_isdigit(str[i]))
		{
			write(STDERR_FILENO, "Invalid pid.\n", 13);
			exit (EXIT_FAILURE);
		}
		num = num * 10 + (str[i] - '0');
	}
	return (num);
}

void	signal_handler(int signal)
{
	static int	c;
	static int	bit;

	c += ((signal & 1) << bit);
	bit += 1;
	if (bit == 8)
	{
		if (c != ACK)
		{
			write(STDERR_FILENO, "receive ack error !\n", 17);
			exit(EXIT_FAILURE);
		}
		c = 0;
		bit = 0;
	}
}

void	send_eot(int pid)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < 8)
	{
		usleep(50);
		if ((EOT >> i) & 1)
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret)
		{
			write(STDERR_FILENO, "kill error !\n", 17);
			exit(EXIT_FAILURE);
		}
	}
}

void	send_char(int pid, char c)
{
	int	j;
	int	ret;

	j = -1;
	while (++j < 8)
	{
		usleep(50);
		if ((c >> j) & 1)
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret)
			exit(EXIT_FAILURE);
	}
	send_eot(pid);
	while (--j >= 0)
	{
		signal(SIGUSR1, &signal_handler);
		signal(SIGUSR2, &signal_handler);
		pause();
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		msg_len;
	int		i;

	if (argc != 3)
		return (1);
	pid = (pid_t)check_pid(argv[1]);
	if (pid <= MIN_PID || pid > MAX_PID)
	{
		write(STDERR_FILENO, "Invalid pid.\n", 13);
		return (1);
	}
	if (kill(pid, 0))
	{
		write(STDERR_FILENO, "process does not exist.\n", 24);
		return (1);
	}
	msg_len = ft_strlen(argv[2]);
	i = -1;
	while (++i <= msg_len)
		send_char(pid, argv[2][i]);
	write(STDOUT_FILENO, "SUCCESS!!!\n", 11);
	return (0);
}
