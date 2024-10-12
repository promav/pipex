/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:56:41 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/11 22:49:20 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	p_freessplit(arg, p_mallocsize(argv, ' '));
	free(cmd);
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

void	ft_free_path(char **path)
{
	int i;

	i = 0;
	while(path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
