#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
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
void ft_access(int infile, int outfile, char **argv)
{
	char **arg;
	char *cmd;

	arg = ft_split(argv[2], ' ');
	cmd = ft_strjoin("/usr/bin/",arg[0]);
	if(access(cmd, X_OK) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		freessplit(arg, mallocsize(argv[2], ' '));
		free(cmd);
		ft_close(infile, outfile, 99, 99);
		exit(EXIT_FAILURE);
	}
	freessplit(arg, mallocsize(argv[2], ' '));
	free(cmd);
	arg = ft_split(argv[3], ' ');
	cmd = ft_strjoin("/usr/bin/",arg[0]);
	if(access(cmd, X_OK) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		freessplit(arg, mallocsize(argv[3], ' '));
		free(cmd);
		ft_close(infile, outfile, 99, 99);
		exit(EXIT_FAILURE);
	}
}

void ft_open(char **argv, int infile, int outfile)
{
	if(infile < 0)
	{
		printf("-bash: %s: No such file or directory\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(outfile < 0)
	{
		printf("-bash: %s: No such file or directory\n", argv[5]);
		close(infile);
		exit(EXIT_FAILURE);
	}
}

pid_t ft_pid1(char **argv, int *fd, int infile, int outfile)
{
	pid_t pid1;
	char **arg;
	char *cmd;

	arg = ft_split(argv[2], ' ');
	cmd = ft_strjoin("/usr/bin/",arg[0]);
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork");
		freessplit(arg, mallocsize(argv[2], ' '));
		free(cmd);
		ft_close(infile, outfile, fd[0], fd[1]);
		exit(EXIT_FAILURE);
	}
	if(pid1 == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		ft_close(infile, outfile, fd[0], fd[1]);
		execve(cmd, arg, NULL);
		perror("execve cmd1:");
		exit(EXIT_FAILURE);
	}
	return (pid1);
}

pid_t ft_pid2(char **argv, int *fd, int infile, int outfile)
{
	pid_t pid2;
	char **arg;
	char *cmd;

	arg = ft_split(argv[3], ' ');
	cmd = ft_strjoin("/usr/bin/",arg[0]);
	pid2 = fork();
	if(pid2 < 0)
	{
		perror("fork");
		freessplit(arg, mallocsize(argv[3], ' '));
		free(cmd);
		ft_close(infile, outfile, fd[0], fd[1]);
		exit(EXIT_FAILURE);
	}
	if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		ft_close(infile, outfile, fd[0], fd[1]);
		execve(cmd, arg, NULL);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
	}
	return (pid2);
}

int ft_pipex(int argc, char **argv)
{
	int infile;
	int outfile;
	int fd[2];
	pid_t pid1;
	pid_t pid2;
	int status;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_open(argv, infile, outfile);
	ft_access(infile, outfile, argv);
	if(pipe(fd) == -1)
	{
		perror("pipe");
		ft_close(infile, outfile, 99, 99);
		return EXIT_FAILURE;
	}
	pid1 = ft_pid1(argv, fd, infile, outfile);
	pid2 = ft_pid2(argv, fd, infile, outfile);
	ft_close(infile, outfile, fd[0], fd[1]);
	waitpid(pid1, &status, 0);
	if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
		printf("Fallo en el primer comando\n");
	waitpid(pid2, &status, 0);
	if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
		printf("Fallo en el segundo comando\n");
	/*freessplit(arg1, mallocsize(argv[2], ' '));
	free(cmd1);
	freessplit(arg2, mallocsize(argv[3], ' '));
	free(cmd2);*/
	printf("Hemos llegado hasta aqui\n");
	return (0);
}

int main(int argc, char **argv)
{
	if(argc != 5)
		return EXIT_FAILURE;
	return(ft_pipex(argc, argv));
	
}
