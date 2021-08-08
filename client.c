#include "minitalk.h"

void	receive_ack(int signal)
{
	static int	c;
	static int	bit;

	c += ((signal & 1) << bit);
	bit += 1;
	if (bit == 8)
	{
		if (c != ACK)
		{
			write(2, "receive ack error !\n", 17);
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
			exit(EXIT_FAILURE);
	}
}

void	send_str(int pid, char *msg, int msg_len)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	while (++i <= msg_len)
	{
		j = -1;
		while (++j < 8)
		{
			usleep(50);
			if ((msg[i] >> j) & 1)
				ret = kill(pid, SIGUSR2);
			else
				ret = kill(pid, SIGUSR1);
			if (ret)
				exit(EXIT_FAILURE);
		}
		/* 1文字ぶん送り終わったらeotを送る */
		send_eot(pid);
		/* ackを受け取る */
		while (--j >= 0)
		{
			signal(SIGUSR1, &receive_ack);
			signal(SIGUSR2, &receive_ack);
			pause();
		}
	}
	write(1, "SUCCESS!!!\n", 11);
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
		write(2, "Invalid pid.\n", 13);
		exit (EXIT_FAILURE);
	}
	i = -1;
	while (++i < len)
	{
		if (!ft_isdigit(str[i]))
		{
			write(2, "Invalid pid.\n", 13);
			exit (EXIT_FAILURE);
		}
		num = num * 10 + (str[i] - '0');
	}
	return (num);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (1);
	/* server側のpidを取得する */
	pid = (pid_t)check_pid(argv[1]);
	if (pid <= 1)
		return (1);
	/* シグナル0を送信してserverの生存確認 */
	if (kill(pid, 0))
		return (1);
	/* 文字列を送信する(1文字ずつ) */
	send_str(pid, argv[2], ft_strlen(argv[2]));

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
