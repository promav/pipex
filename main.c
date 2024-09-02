#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include <sys/wait.h>

void ft_close(int a, int b, int c, int d)
{
	close(a);
	close(b);
	if(c != 99);
		close(c);
	if(d != 99);
		close(d);
}

void ft_superfree(char **arg, char *cmd, char *argv)
{
	freessplit(arg, mallocsize(argv, ' '));
	free(cmd);
}

void ft_access(int *inoutfile, char **argv)
{
	char **arg;
	char *cmd;

	arg = ft_split(argv[2], ' ');
	cmd = ft_strjoin("/usr/bin/",arg[0]);
	if(access(cmd, X_OK) != 0)
	{
		ft_printf("%s: command not found\n", arg[0]);
		ft_superfree(arg, cmd, argv[2]);
		ft_close(inoutfile[0], inoutfile[1], 99, 99);
		exit(EXIT_FAILURE);
	}
	ft_superfree(arg, cmd, argv[2]);
	arg = ft_split(argv[3], ' ');
	cmd = ft_strjoin("/usr/bin/",arg[0]);
	if(access(cmd, X_OK) != 0)
	{
		ft_printf("%s: command not found\n", arg[0]);
		ft_superfree(arg, cmd, argv[3]);
		ft_close(inoutfile[0], inoutfile[1], 99, 99);
		exit(EXIT_FAILURE);
	}
	ft_superfree(arg, cmd, argv[3]);
}

void ft_open(char **argv, int *inoutfile)
{
	if(inoutfile[0] < 0)
	{
		ft_printf("-bash: %s: No such file or directory\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(inoutfile[1] < 0)
	{
		ft_printf("-bash: %s: No such file or directory\n", argv[5]);
		close(inoutfile[0]);
		exit(EXIT_FAILURE);
	}
}

pid_t ft_pid1(char **arg, char *cmd, int *fd, int *inoutfile)
{
	pid_t pid1;

	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork");
		freessplit(arg, sizeof(arg));
		free(cmd);
		ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
		exit(EXIT_FAILURE);
	}
	if(pid1 == 0)
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

pid_t ft_pid2(char **arg, char *cmd, int *fd, int *inoutfile)
{
	pid_t pid2;

	pid2 = fork();
	if(pid2 < 0)
	{
		perror("fork");
		freessplit(arg, sizeof(arg));
		free(cmd);
		ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
		exit(EXIT_FAILURE);
	}
	if(pid2 == 0)
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

void ft_waitpid(pid_t *pid)
{
	int status;

	waitpid(pid[0], &status, 0);
	if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_printf("Fallo en el primer comando\n");
	waitpid(pid[1], &status, 0);
	if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_printf("Fallo en el segundo comando\n");
}

void ft_action(char **argv, int *fd, int *inoutfile)
{
	char **arg1;
	char **arg2;
	char *cmd1;
	char *cmd2;
	pid_t pid[2];
	
	arg1 = ft_split(argv[2], ' ');
	cmd1 = ft_strjoin("/usr/bin/",arg1[0]);
	arg2 = ft_split(argv[3], ' ');
	cmd2 = ft_strjoin("/usr/bin/",arg2[0]);
	pid[0] = ft_pid1(arg1, cmd1, fd, inoutfile);
	pid[1] = ft_pid2(arg2, cmd2, fd, inoutfile);
	ft_close(inoutfile[0], inoutfile[1], fd[0], fd[1]);
	ft_waitpid(pid);
	freessplit(arg1, mallocsize(argv[2], ' '));
	free(cmd1);
	freessplit(arg2, mallocsize(argv[3], ' '));
	free(cmd2);
}

int ft_pipex(int argc, char **argv)
{
	int inoutfile[2];
	int fd[2];

	inoutfile[0] = open(argv[1], O_RDONLY);
	inoutfile[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_open(argv, inoutfile);
	ft_access(inoutfile, argv);
	if(pipe(fd) == -1)
	{
		perror("pipe");
		ft_close(inoutfile[0], inoutfile[1], 99, 99);
		return EXIT_FAILURE;
	}
	ft_action(argv, fd, inoutfile);
	return (0);
}

int main(int argc, char **argv)
{
	if(argc != 5)
		return EXIT_FAILURE;
	return(ft_pipex(argc, argv));	
}
