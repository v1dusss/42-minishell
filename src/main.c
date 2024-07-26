# include "minishell.h"

int	get_prompt(char **envp)
{
	t_token		*token;
	//t_ast_node	*ast;
	char		*input;
	char		*prompt;

	token = NULL;
	//ast = NULL;
	if (DEBUG_MODE)
		prompt = "\033[1;32m$ \033[0m";
	else
		prompt = "\033[1;31m$ \033[0m";
	input = readline(prompt); // input needs to be freed
	if (!input)
		return (1);
	if (input[0] == '\0')
		return (free(input), 0);
	if (DEBUG_MODE)
		printf("\033[0;37mYou entered: \033[1;37m%s\033[0m\n", input);
	tokenize(&token, input);
	// expander(&token, envp);
	add_history(input);
	// get_priority(&token);
	// get_ast(token, &ast);
	// print_ast(ast);
	rearrange(&token);
	execute(&token, envp);
	while (token && DEBUG_MODE)
	{
		if (token->content)
			printf("%s", token->content);
		if (token->next)
			token = token->next;
		else
		{
			printf("\n");
			break ;
		}
	}
	return (free(input), 0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	print_banner();
	if (DEBUG_MODE)
		printf("DEBUG_MODE: \033[1;32mON\033[0m\n");
	else
		printf("DEBUG_MODE: \033[1;31mOFF\033[0m\n");
	while (1)
	{
		get_prompt(envp);
	}
	return (0);
}
