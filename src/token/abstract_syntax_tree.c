#include "minishell.h"

t_token	*get_highest(t_token **token)
{
	t_token	*temp;
	t_token	*highest;

	temp = tokenfirst(token);
	if (temp->next == NULL)
		return (temp);
	highest = temp->next;
	while (temp)
	{
		if (temp->priority >= highest->priority)
			highest = temp;
		temp = temp->next;
	}
	return (highest);
}

void	left_and_right(t_token **left, t_token **right, t_token **highest)
{
	if (!highest)
		return ;
	if ((*highest)->prev)
	{
		*left = (*highest)->prev;
		(*left)->next = NULL;
		(*highest)->prev = NULL;
		(*left) = tokenfirst(left);
		(*left) = get_highest(left);
	}
	else
		left = NULL;
	if ((*highest)->next)
	{
		*right = (*highest)->next;
		(*right)->prev = NULL;
		(*highest)->next = NULL;
		get_highest(right);
		(*right) = tokenfirst(right);
		(*right) = get_highest(right);
	}
	else
		right = NULL;
}

void	get_ast(t_token *token, t_ast_node **ast)
{
	t_ast_node	*temp_ast;
	t_token		*right;
	t_token		*left;
	t_token		*highest;

	if (!token || !ast)
		return ;
	if (*ast == NULL)
		*ast = malloc(sizeof(t_ast_node));
	temp_ast = NULL;
	highest = get_highest(&token);
	left_and_right(&left, &right, &highest);
	(*ast)->token = highest;
	printf("==========\n");
	printf("highest: %s\n", highest->content);
	if (highest->type == TOKEN_WORD || highest->type == TOKEN_SPACE)
		return ;
	if (left != NULL)
	{
		printf("*");
		printf(" l:%s\t  ", left->content);
	}
	if (right != NULL)
	{
		printf("*");
		printf(" r:%s", right->content);
	}
	printf("\n");
	get_ast(left, &temp_ast->left);
	get_ast(right, &temp_ast->right);
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
