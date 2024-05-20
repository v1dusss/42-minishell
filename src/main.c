#include "minishell.h"

// void	print_ast(t_ast_node *ast)
// {
// 	t_ast_node	*temp;

// 	temp = ast;
// 	if (!temp)
// 		return ;
// 	printf("***************\n");
// 	printf("root: %s\n", temp->token->content);
// 	if (temp->right)
// 	{
// 		printf("right: %s\n", temp->right->token->content);
// 		temp = temp->right;
// 	}
// 	if (temp->right)
// 	{
// 		printf("right: %s\n", temp->right->token->content);
// 		temp = temp->right;
// 	}
// 	if (temp->right)
// 	{
// 		printf("right: %s\n", temp->right->token->content);
// 	}
// 	else if (temp->right == NULL)
// 		printf("right: NULL\n");
// }

int	get_prompt(char **envp)
{
	t_token		*token;
	//t_ast_node	*ast;
	char		*input;
	char		*prompt;

	token = NULL;
	//ast = NULL;
	prompt = "$ ";
	input = readline(prompt); // input needs to be freed
	if (!input)
		return (1);
	if (input[0] == '\0')
		return (free(input), 0);
	if (PRINT_INPUT)
		printf("\033[0;37mYou entered: \033[1;37m%s\033[0m\n", input);
	printf("A\n");
	tokenize(&token, input);
	printf("B\n");
	// expander(&token, envp);
	printf("C\n");
	add_history(input);
	// get_priority(&token);
	// get_ast(token, &ast);
	// print_ast(ast);
	rearrange(&token);
	printf("D\n");
	execute(&token, envp);
	printf("E\n");
	while (token)
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
	while (1)
	{
		get_prompt(envp);
	}
	return (0);
}
