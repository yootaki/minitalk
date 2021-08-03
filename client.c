#include <libc.h>
#include "libft/libft.h"

int	g_ack;

void	receive_ack(int signal)
{
	static int	c;
	static int	size;

	c += ((signal & 1) << size);
	size += 1;
	if (size == 8)
	{
		if (c == '\006')
			g_ack = 1;
		c = 0;
		size = 0;
	}
}

void	send_eot(int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		usleep(50);
		if (('\004' >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
	}
}

void	send_str(int pid, char *msg, int msg_len)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= msg_len)
	{
		j = -1;
		while (++j < 8)
		{
			usleep(50);
			if ((msg[i] >> j) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
		}
		/* 1文字ぶん送り終わったらeotを送る */
		send_eot(pid);
		/* ackを受け取る */
		while (!g_ack || --j >= 0)
		{
			signal(SIGUSR1, &receive_ack);
			signal(SIGUSR2, &receive_ack);
		}
		if (g_ack)
			g_ack = 0;
		else
			exit(EXIT_FAILURE);
	}
}

int	check_pid(const char *str)
{
	int	num;
	int	len;
	int	i;

	num = 0;
	len = ft_strlen(str);
	if (len > 7)
	{
		write(1, "Invalid pid.\n", 13);
		exit (1);
	}
	i = -1;
	while (++i < len)
	{
		if (!ft_isdigit(str[i]))
		{
			write(1, "Invalid pid.\n", 13);
			exit (1);
		}
		num = num * 10 + (str[i] - '0');
	}
	return (num);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (0);

	pid = (pid_t)check_pid(argv[1]);
	if (pid <= 1)
		return (0);
	send_str(pid, argv[2], ft_strlen(argv[2]));

	// /* 文字列を送り終わったらeotを送る */
	// send_eot(pid);

	// /* ackを受け取る */
	// while (!g_ack)
	// {
	// 	signal(SIGUSR1, &receive_ack);
	// 	signal(SIGUSR2, &receive_ack);
	// }

	return (0);
}

// __attribute__((destructor))
// void    destructor(void)
// {
//     int    status;

//     status = system("leaks client &> leaksout");
//     if (status)
//     {
//         write(2, "leak!!!\n", 8);
//         system("cat leaksout >/dev/stderr");
//         exit(1);
//     }
// }
