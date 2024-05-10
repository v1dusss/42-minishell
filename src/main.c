#include "minishell.h"

void	execute(t_token *token, char **envp)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = tokenfirst(&token);
	if (ft_strncmp(temp->content, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strncmp(temp->content, "pwd", 3) == 0)
	{
		i = 3;
		while (envp[0][++i])
			printf("%c", envp[0][i]);
		printf("\n");
	}
	if (ft_strncmp(temp->content, "env", 3) == 0)
	{
		while (envp && *envp)
			printf("%s\n", *envp++);
	}
}

int	get_prompt(char **envp)
{
	t_token	*token;
	char	*input;
	char	*prompt;

	token = NULL;
	prompt = "$ ";
	input = readline(prompt); // input needs to be freed
	if (!input)
		return (1);
	if (input[0] == '\0')
		return (free(input), 0);
	if (PRINT_INPUT)
		printf("\033[0;37mYou entered: \033[1;37m%s\033[0m\n", input);
	tokenize(&token, input);
	add_history(input);
	get_priority(&token);
	execute(token, envp);
	return (free(input), 0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	while (1)
	{
		get_prompt(envp);
	}
	return (0);
}
