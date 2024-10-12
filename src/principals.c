/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:56:41 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/11 22:48:52 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	ft_pid1(char **arg, char *cmd, int *fd, int *inoutfile)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		p_freessplit(arg, sizeof(arg));
		free(cmd);
		ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(inoutfile[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
		execve(cmd, arg, NULL);
		perror("execve cmd1:");
		exit(EXIT_FAILURE);
	}
	return (pid1);
}

pid_t	ft_pid2(char **arg, char *cmd, int *fd, int *inoutfile)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		p_freessplit(arg, sizeof(arg));
		free(cmd);
		ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(inoutfile[1], STDOUT_FILENO);
		ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
		execve(cmd, arg, NULL);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	return (pid2);
}

void	ft_action(char **argv, int *fd, int *inoutfile, char **path)
{
	char	**arg1;
	char	**arg2;
	char	*cmd1;
	char	*cmd2;
	pid_t	pid[2];

	arg1 = ft_split(argv[2], ' ');
	cmd1 = ft_cmd_action(path, arg1[0]);
	arg2 = ft_split(argv[3], ' ');
	cmd2 = ft_cmd_action(path, arg2[0]);
	pid[0] = ft_pid1(arg1, cmd1, fd, inoutfile);
	pid[1] = ft_pid2(arg2, cmd2, fd, inoutfile);
	ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
	ft_waitpid(pid);
	p_freessplit(arg1, p_mallocsize(argv[2], ' '));
	free(cmd1);
	p_freessplit(arg2, p_mallocsize(argv[3], ' '));
	free(cmd2);
}


int	ft_pipex(char **argv, char **env)
{
	int		inoutfile[2];
	int		fd[2];
	char	**path;
	
	path = ft_spliter_path(env);
	inoutfile[0] = open(argv[1], O_RDONLY);
	inoutfile[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_open(argv, inoutfile);
	ft_access(inoutfile, argv, path);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		ft_close(inoutfile[0], inoutfile[1], 99, 99);
		return (EXIT_FAILURE);
	}
	ft_action(argv, fd, inoutfile, path);
	ft_free_path(path);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		return (EXIT_FAILURE);
	return (ft_pipex(argv, env));
}
