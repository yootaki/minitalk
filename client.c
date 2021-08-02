#include <libc.h>
#include "libft/libft.h"

int	g_ack;

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
	}
}

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

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (0);

	pid = (pid_t)atoi(argv[1]);
	send_str(pid, argv[2], ft_strlen(argv[2]));

	/* 文字列を送り終わったらeotを送る */
	send_eot(pid);

	/* ackを受け取る */
	while (!g_ack)
	{
		signal(SIGUSR1, &receive_ack);
		signal(SIGUSR2, &receive_ack);
	}

	write(1, "ok\n", 3);

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
