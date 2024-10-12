#include "pipex.h"

unsigned int	p_mallocsize(char const *s, char c)
{
	int	ms;
	int	i;

	i = 0;
	ms = 0;
	if (s[0] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			ms++;
		i++;
	}
	if (s[i - 1] != c)
		ms++;
	return (ms);
}

void	*p_freessplit(char **ssplit, int k)
{
	while (k >= 0)
	{
		free(ssplit[k]);
		k--;
	}
	free(ssplit);
	return (NULL);
}

char **ft_fill_split_path(char **cp_split_path, char *clean)
{
	int i;
	char **split_path;

	split_path = (char **)malloc((1+p_mallocsize(clean, ':'))*sizeof(char*));
    if (!split_path)
		exit(EXIT_FAILURE);
	i = 0;
	while(cp_split_path[i])
    {
        split_path[i] = ft_strjoin(cp_split_path[i], "/");
        free(cp_split_path[i]);
        i++;
    }
    split_path[i] = NULL;
    free(cp_split_path);
    return (split_path);
}

void ft_not_access_exit(char **argv, char **arg, int *inoutfile, char *cmd)
{
	ft_printf("%s: command not found\n", arg[0]);
	ft_superfree(arg, cmd, argv[2]);
	ft_close(inoutfile[0], inoutfile[1], 99, 99);
	exit(EXIT_FAILURE);
}
