/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:40:32 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/11 23:04:12 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"

void			ft_close(int a, int b, int c, int d);
void			ft_superfree(char **arg, char *cmd, char *argv);
void			ft_access(int *inoutfile, char **argv, char **path);
void			ft_open(char **argv, int *inoutfile);
void			ft_waitpid(pid_t *pid);
char 			**ft_spliter_path(char **env);
char 			*ft_cmd_try(char **path, char **arg, char **argv, int *inoutfile);
void			ft_free_path(char **path);
char            *ft_cmd_action(char **path, char *arg);
unsigned int	p_mallocsize(char const *s, char c);
void	        *p_freessplit(char **ssplit, int k);
char            **ft_fill_split_path(char **cp_split_path, char *clean);
void            ft_not_access_exit(char **argv, char **arg, int *inoutfile, char *cmd);

#endif
