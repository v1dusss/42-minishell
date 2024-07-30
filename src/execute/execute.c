#include "minishell.h"

void	execute(t_token **token, char **envp)
{
	t_token	*temp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (DEBUG_MODE)
		printf("\033[1;37mexecute\033[0m\n");
	temp = tokenfirst(token);
	if (ft_strncmp(temp->content, "exit", 4) == 0)
	{
		if (DEBUG_MODE)
			printf("exit\n");
		exit(0);
	}
	else if (ft_strncmp(temp->content, "pwd", 3) == 0)
	{
		if (DEBUG_MODE)
			printf("pwd\n");
		while (ft_strncmp(envp[x], "PWD", 3) != 0)
			x++;
		y = 3;
		while (envp[x][++y])
			printf("%c", envp[x][y]);
		printf("\n");
	}
	else if (ft_strncmp(temp->content, "env", 3) == 0)
	{
		if (DEBUG_MODE)
			printf("env\n");
		while (envp[x])
			printf("%s\n", envp[x++]);
	}
	else if (ft_strncmp(temp->content, "echo", 4) == 0)
	{
		if (DEBUG_MODE)
			printf("echo\n");
		if (!temp->next)
		{
			if (DEBUG_MODE)
				printf("no ->next after echo");
			printf("\n");
			return ;
		}
		else
			temp = temp->next;
		while (temp->type == TOKEN_SPACE && temp->next)
			temp = temp->next;
		while (temp->content)
		{
			if (temp->type == TOKEN_WORD || temp->type == TOKEN_SPACE)
				printf("%s", temp->content);
			if (temp->next)
				temp = temp->next;
			else
				break;
			while (temp->type == TOKEN_SPACE && temp->next)
			{
				temp = temp->next;
			}
			if (temp->type == TOKEN_WORD)
				printf(" ");
		}
		printf("\n");
	}
	else
	{
		printf("minishell: command not found: %s\n", temp->content);	
	}
}

