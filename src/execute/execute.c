#include "minishell.h"

void	execute(t_token **token, char **envp)
{
	t_token	*temp;
	int		i;

	i = 0;
	printf("execute\n");
	temp = tokenfirst(token);
	printf("test\n");
	if (ft_strncmp(temp->content, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strncmp(temp->content, "pwd", 3) == 0)
	{
		i = 3;
		printf("pwd\n");
		while (envp[0][++i])
			printf("%c", envp[0][i]);
		printf("\n");
	}
	if (ft_strncmp(temp->content, "env", 3) == 0)
	{
		printf("env\n");
		while (envp && *envp)
			printf("%s\n", *envp++);
	}
	if (ft_strncmp(temp->content, "echo", 4) == 0)
	{
		printf("echo\n");
		if (temp->next)
			temp = temp->next;
		while (temp->type == TOKEN_SPACE)
			temp = temp->next;
		while (temp->content[i])
			printf("%c", temp->content[i++]);
		printf("\n");
	}
	printf("end execute\n");
}
