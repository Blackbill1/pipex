/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:29:54 by tle-dref          #+#    #+#             */
/*   Updated: 2024/11/05 03:13:48 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void    display_cmd(t_pipex *data)
// {
//     int i;
//     int j;

//     i = 0;
//     ft_printf("Nombre total de commandes: %d\n", data->cmd_count);
//     while (i < data->cmd_count)
//     {
//         j = 0;
//         ft_printf("Commande %d: ", i + 1);
//         while (data->cmd[i][j] != NULL)
//         {
//             ft_printf("|%s|", data->cmd[i][j]);
//             j++;
//         }
//         ft_printf("\n");
//         i++;
//     }
// }

int	init_pipex(t_pipex *data, int ac, char **av, char **envp)
{
	int	i;

	i = 0;
	data->cmd_count = 0;
	data->infile = open(av[1], O_RDONLY, 0644);
	if (data->infile < 0)
		return (perror("Input file error"), 1);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile < 0)
		return (perror("Output file error"), 1);
	data->pids = malloc(sizeof(pid_t) * (ac - 3));
	data->pipe_fd = malloc(sizeof(int) * ((ac - 4) * 2));
	data->cmd = ft_calloc(ac - 3, sizeof(char **));
	while (i < ac - 3)
	{
		data->cmd[i] = ft_split(av[i + 2], ' ');
		data->cmd_count++;
		i++;
	}
	data->envp = envp;
	data->limiter = NULL;
	return (0);
}

int	init_pipex2(t_pipex *data, int ac, char **av, char **envp)
{
	int	i;

	i = 0;
	data->cmd_count = 0;
	data->infile = open("tmp", O_RDONLY, 0644);
	if (data->infile < 0)
		return (perror("Input file error"), 1);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile < 0)
		return (perror("Output file error"), 1);
	data->pids = malloc(sizeof(pid_t) * (ac - 4));
	data->pipe_fd = malloc(sizeof(int) * ((ac - 5) * 2));
	data->cmd = ft_calloc(ac - 4, sizeof(char **));
	while (i < ac - 4)
	{
		data->cmd[i] = ft_split(av[i + 3], ' ');
		data->cmd_count++;
		i++;
	}
	data->envp = envp;
	return (0);
}

void	handle_here_doc(t_pipex *data, char **av)
{
	int		tmp;
	char	*line;

	tmp = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp == -1)
	{
		perror("Open failed: ");
		clear_data(data);
		exit(1);
	}
	data->limiter = ft_strjoin(av[2], "\n");
	dup2(tmp, STDOUT_FILENO);
	line = get_next_line(0);
	while (ft_strcmp(line, data->limiter) != 0)
	{
		ft_putstr_fd(line, tmp);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(tmp);
}

void	clear_data(t_pipex *data)
{
	int	i;
	int	j;

	close(data->infile);
	close(data->outfile);
	free(data->pipe_fd);
	free(data->pids);
	free(data->limiter);
	if (data->cmd)
	{
		i = 0;
		while (i < data->cmd_count)
		{
			if (data->cmd[i])
			{
				j = 0;
				while (data->cmd[i][j])
					free(data->cmd[i][j++]);
				free(data->cmd[i]);
			}
			i++;
		}
		free(data->cmd);
	}
}
// void    display_cmd(t_pipex *data)
// {
//     int i;
//     int j;

//     i = 0;
//     ft_printf("Nombre total de commandes: %d\n", data->cmd_count);
//     while (i < data->cmd_count)
//     {
//         j = 0;
//         ft_printf("Commande %d: ", i + 1);
//         while (data->cmd[i][j] != NULL)
//         {
//             ft_printf("|%s|", data->cmd[i][j]);
//             j++;
//         }
//         ft_printf("\n");
//         i++;
//     }
// }