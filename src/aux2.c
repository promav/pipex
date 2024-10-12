#include "pipex.h"

char **ft_spliter_path(char **env)
{
    int i;
    char *path;
    char *clean;
    char **cp_split_path;
    char **split_path;

    i = 0;
    while(env[i])
    {
        path = ft_strnstr(env[i], "PATH=/", 6);
        if(path)
            break;
        i++;
    }
    clean = ft_strnstr(env[i], "/home", 15);
    cp_split_path = ft_split(clean, ':');
    split_path = ft_fill_split_path(cp_split_path, clean);
    return (split_path);
}

char *ft_cmd_try(char **path, char **arg, char **argv, int *inoutfile)
{
    char *cmd;
    int i;
    int flag;

    i = 0;
    flag = -1;
    while(path[i])
    {
        cmd = ft_strjoin(path[i], arg[0]);
	    if (access(cmd, X_OK) == 0)
	    {
	    	flag = 0;
            return (cmd);
	    }
        free (cmd);
        cmd = NULL;
        i++;
    }
    if (flag == -1)
	{
		ft_free_path(path);
        ft_not_access_exit(argv, arg, inoutfile, cmd);
	}
    return NULL;
}

char *ft_cmd_action(char **path, char *arg)
{
	int i;
	char *cmd;

	i = 0;
	while(path[i])
	{
		cmd = ft_strjoin(path[i], arg);
	    if (access(cmd, X_OK) == 0)
	        return (cmd);
        free (cmd);
        cmd = NULL;
        i++;
	}
	return NULL;
}

void	ft_access(int *inoutfile, char **argv, char **path)
{
	char	**arg;
	char	*cmd;

	arg = ft_split(argv[2], ' ');
	cmd = ft_cmd_try(path, arg, argv, inoutfile);
	ft_superfree(arg, cmd, argv[2]);
	arg = ft_split(argv[3], ' ');
	cmd = ft_cmd_try(path, arg, argv, inoutfile);
	ft_superfree(arg, cmd, argv[3]);
}
