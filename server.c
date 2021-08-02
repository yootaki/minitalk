#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

#include <stdio.h>

// typedef struct __siginfo {
// 	int     si_signo;               /* signal number */
// 	int     si_errno;               /* errno association */
// 	int     si_code;                /* signal code */
// 	pid_t   si_pid;                 /* sending process */
// 	uid_t   si_uid;                 /* sender's ruid */
// 	int     si_status;              /* exit value */
// 	void    *si_addr;               /* faulting instruction */
// 	union sigval si_value;          /* signal value */
// 	long    si_band;                /* band event for SIGPOLL */
// 	unsigned long   __pad[7];       /* Reserved for Future Use */
// } siginfo_t;

void	signal_handler(int sig, siginfo_t *siginf, void *context)
{
	static char	buf[1000];
	static int	msg_len;
	static int	c;
	static int	size;

	(void)siginf;
	(void)context;
	c += ((sig & 1) << size);
	size += 1;
	if (size == 8)
	{
		if (c)
			buf[msg_len++] = c;
		else
		{
			buf[msg_len] = '\n';
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

void	receive_msg(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{
	pid_t	pid;
	char	*s_pid;

	pid = getpid();
	s_pid = ft_itoa(pid);
	write(1, s_pid, ft_strlen(s_pid));
	write(1, "\n", 1);
	free(s_pid);

	/* シグナルを受け取るため待機 */
	while (1)
		receive_msg();

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
