#include "minishell.h"

void	new_token(t_token **head)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc");
		exit(1);
	}
	while (*head)
		head = &(*head)->next;
	(*head)->next = new;
	new->prev = head;
}

void	input_spliter(char *input)
{
	int i;
	int type;
	int type2;
	int len;

	i = 0;
	len = ft_strlen(input);
	while (input[i])
	{
	}
	//need to check which character is which token_type
	// and then split the input into tokens with substring
	// and then tokenize the tokens
}

void	tokenize(char *input)
{
	t_token *token;
	int i;
	int first;
	int type;

	i = 0;
	first = 0;
	type = -1;
	while (input[i])
	{
		if (first == 0)
		{
			new_token(&token);
			token->content = ft_strdup(input[i++]);
		}
		else
		{
		}
	}
}