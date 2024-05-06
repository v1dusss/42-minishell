#include "minishell.h"

int	get_prompt(void)
{
	char	*input;
	char	*prompt;

	prompt = "$ ";
	input = readline(prompt);
	if (!input)
		return (1);
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	printf("You entered: %s\n", input);
	add_history(input);
	free(input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		get_prompt();
	}
	return (0);
}
