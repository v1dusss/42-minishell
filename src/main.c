#include "minishell.h"

int	get_prompt(void)
{
	char	*input;
	char	*prompt;

	prompt = "$ ";
	input = readline(prompt); // input needs to be freed
	if (!input)
		return (1);
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	printf("\033[0;37mYou entered: \033[1;37m%s\033[0m\n", input);
	add_history(input);
	tokenize(input);
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
