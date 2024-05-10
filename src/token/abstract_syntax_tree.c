#include "minishell.h"

t_token	*get_highest(t_token **token)
{
	t_token	*temp;
	t_token	*highest;

	temp = tokenfirst(token);
	highest = temp;
	while (temp)
	{
		if (temp->priority > highest->priority)
			highest = temp;
		temp = temp->next;
	}
	return (highest);
}

t_ast_node	*get_ast(t_token *token)
{
	t_ast_node	*node;
	t_token		*temp;

	node = malloc(sizeof(t_ast_node));
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	temp = tokenfirst(&token);
	while (temp)
	{
		if (temp->priority == 2)
		{
			node->left = get_ast(temp->prev);
			node->right = get_ast(temp->next);
			break ;
		}
		temp = temp->next;
	}
	return (node);
}

void	get_priority(t_token **token)
{
	t_token	*temp;

	temp = tokenfirst(token);
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
			temp->priority = 3;
		else if (temp->type == TOKEN_REDIRECT_INPUT
			|| temp->type == TOKEN_REDIRECT_OUTPUT
			|| temp->type == TOKEN_DOUBLE_REDIRECT_INPUT
			|| temp->type == TOKEN_DOUBLE_REDIRECT_OUTPUT)
			temp->priority = 2;
		else
			temp->priority = 0;
		temp = temp->next;
	}
}
