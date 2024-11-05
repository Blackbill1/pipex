/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:29:28 by tle-dref          #+#    #+#             */
/*   Updated: 2024/11/05 05:56:18 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_exec_error(char *cmd_path, char *cmd_name, t_pipex *data)
{
	char	*error;

	if (!cmd_path)
	{
		error = ft_strjoin("Command not found: ", cmd_name);
		error = clean_join(error, "\n");
		write(2, error, ft_strlen(error));
		free(error);
		clear_data(data);
		exit(1);
	}
	else if (access(cmd_path, X_OK) == -1)
	{
		error = ft_strjoin("Permission denied: ", cmd_name);
		error = clean_join(error, "\n");
		write(2, error, ft_strlen(error));
		free(error);
		clear_data(data);
		exit(1);
	}
}

static char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return(cmd);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static void	setup_pipes(t_pipex *data, int cmd_index)
{
	if (cmd_index == 0)
	{
		dup2(data->infile, STDIN_FILENO);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	}
	else if (cmd_index == data->cmd_count - 1)
	{
		dup2(data->pipe_fd[2 * (cmd_index - 1)], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(data->pipe_fd[2 * (cmd_index - 1)], STDIN_FILENO);
		dup2(data->pipe_fd[2 * cmd_index + 1], STDOUT_FILENO);
	}
}

static void	child_process(t_pipex *data, char **cmd, int cmd_index)
{
	char	*cmd_path;

	dprintf(2, "caca1\n");
	cmd_path = find_command_path(cmd[0], data->envp);
	dprintf(2, "%s\n", cmd_path);
	handle_exec_error(cmd_path, cmd[0], data);
	setup_pipes(data, cmd_index);
	close_all_pipes(data);
	execve(cmd_path, cmd, data->envp);
	perror("Execve error");
	free(cmd_path);
	exit(1);
}

void	exec_cmd(t_pipex *data, char **cmd, int cmd_index)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Fork error"));
	if (pid == 0)
		child_process(data, cmd, cmd_index);
	data->pids[cmd_index] = pid;
}
