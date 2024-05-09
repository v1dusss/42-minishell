#include "minishell.h"

t_token	*tokenfirst(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (!temp)
		return (NULL);
	while (temp->prev)
	{
		temp = temp->prev;
	}
	return (temp);
}

t_token	*tokenlast(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (!temp)
		return (NULL);
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

void	token_new(t_token **token)
{
	t_token	*new;
	t_token	*temp;

	temp = NULL;
	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc");
		exit(1);
	}
	new->next = NULL;
	if (!*token)
	{
		*token = new;
		new->prev = NULL;
	}
	else
	{
		temp = tokenlast(token);
		temp->next = new;
		new->prev = temp;
		temp = new;
	}
}
