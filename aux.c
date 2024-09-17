/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:56:41 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/17 15:22:34 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_close(int a, int b, int c, int d)
{
	close(a);
	close(b);
	if (c != 99)
		close(c);
	if (d != 99)
		close(d);
}

void	ft_superfree(char **arg, char *cmd, char *argv)
{
	freessplit(arg, mallocsize(argv, ' '));
	free(cmd);
}

void	ft_access(int *inoutfile, char **argv)
{
	char	**arg;
	char	*cmd;

	arg = ft_split(argv[2], ' ');
	cmd = ft_strjoin("/usr/bin/", arg[0]);
	if (access(cmd, X_OK) != 0)
	{
		ft_printf("%s: command not found\n", arg[0]);
		ft_superfree(arg, cmd, argv[2]);
		ft_close(inoutfile[0], inoutfile[1], 99, 99);
		exit(EXIT_FAILURE);
	}
	ft_superfree(arg, cmd, argv[2]);
	arg = ft_split(argv[3], ' ');
	cmd = ft_strjoin("/usr/bin/", arg[0]);
	if (access(cmd, X_OK) != 0)
	{
		ft_printf("%s: command not found\n", arg[0]);
		ft_superfree(arg, cmd, argv[3]);
		ft_close(inoutfile[0], inoutfile[1], 99, 99);
		exit(EXIT_FAILURE);
	}
	ft_superfree(arg, cmd, argv[3]);
}

void	ft_open(char **argv, int *inoutfile)
{
	if (inoutfile[0] < 0)
	{
		ft_printf("-bash: %s: No such file or directory\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (inoutfile[1] < 0)
	{
		ft_printf("-bash: %s: No such file or directory\n", argv[5]);
		close(inoutfile[0]);
		exit(EXIT_FAILURE);
	}
}

void	ft_waitpid(pid_t *pid)
{
	int	status;

	waitpid(pid[0], &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_printf("Fallo en el primer comando\n");
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_printf("Fallo en el segundo comando\n");
}
