/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:53:12 by tle-dref          #+#    #+#             */
/*   Updated: 2024/11/05 03:53:45 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_pipes(t_pipex *data)
{
	int	i;
	int	total_pipes;

	total_pipes = (data->cmd_count - 1) * 2;
	i = 0;
	while (i < total_pipes)
	{
		close(data->pipe_fd[i]);
		i++;
	}
}

void	create_pipes(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count - 1)
	{
		if (pipe(data->pipe_fd + (2 * i)) == -1)
		{
			perror("Pipe error");
			clear_data(data);
			exit(1);
		}
	}
}

void	execute_commands(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
		exec_cmd(data, data->cmd[i], i);
	close_all_pipes(data);
}

void	wait_process(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
		waitpid(data->pids[i], NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;

	ft_memset(&data, 0, sizeof(t_pipex));
	if (ac < 5)
		return (ft_putstr_fd("Invalid args\ntry input <cmd> <cmd2> output\n",
				2), 1);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		handle_here_doc(&data, av);
		if (init_pipex2(&data, ac, av, envp) == 1)
			return (ft_putstr_fd("Init fail\n", 2), clear_data(&data), 1);
	}
	else if (init_pipex(&data, ac, av, envp) == 1)
		return (ft_putstr_fd("Init fail\n", 2), clear_data(&data), 1);
	create_pipes(&data);
	execute_commands(&data);
	wait_process(&data);
	clear_data(&data);
	return (0);
}
