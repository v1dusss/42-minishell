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

void initialize_randomizer(void)
{
	srand((unsigned int)getpid());
}

int get_random_number(void)
{
	return (rand() % 24);
}

void print_banner(void)
{
	int i;
	int x;

	initialize_randomizer();
	i = get_random_number();
	printf("\n");
	if (i % 3 == 0)
		printf("\033[0;3%d;7m", i / 3);
	else
	{
		if (i % 3 == 1)
		{
			x = 1;
			i -= 1;
		}
		else
		{
			x = 0;
			i -= 2;
		}
		printf("\033[%d;3%dm", x, i / 3);
	}
	printf(" ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf(" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf(" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
	printf(" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf(" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf(" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\033[0m\n");
	printf("\t\tMADE BY JMUHLBER & VISIVANAT\n");
	printf("\t\t    MADE AT 42 HEILBRONN\n");
	printf("\t\tMINISHELL PROJECT @ 42CURSUS\n\n");
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
