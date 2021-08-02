#include <libc.h>
#include "libft/libft.h"

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
			/* これがないと文字化けする */
			usleep(50);
			/* 1の場合USR2 */
			//USR2は31で基数で1桁目が1だから
			if ((msg[i] >> j) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (0);

	pid = (pid_t)atoi(argv[1]);
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
