#include "minishell.h"

void	redirect_found(t_token **token, t_token *temp)
{
	t_token	*prev;
	t_token	*next;
	t_token	*redirect_front;
	t_token	*redirect_back;
	int		i;

	i = 0;
	redirect_front = temp;
	if (redirect_front->prev)
		prev = redirect_front->prev;
	else
		prev = NULL;
	next = NULL;
	while (temp->next && i < 2)
	{
		if (temp->next)
			temp = temp->next;
		next = temp->next;
		if (temp->type == TOKEN_WORD)
			i++;
	}
	temp = temp->prev;
	if (i == 2)
	{
		redirect_back = temp;
		next = redirect_back->next;
		redirect_front->prev = NULL;
		redirect_back->next = NULL;
		if (prev)
			prev->next = next;
		if (next && prev)
			next->prev = prev;
		if (next && !prev)
			next->prev = NULL;
		temp = tokenlast(token);
		temp->next = redirect_front;
		redirect_front->prev = temp;
		redirect_back->next = NULL;
	}
}

void	rearrange(t_token **token)
{
	t_token *temp;

	temp = tokenfirst(token);
	while (temp)
	{
		printf("*");
		usleep(100);
		if (temp->type == TOKEN_REDIRECT_INPUT
			|| temp->type == TOKEN_REDIRECT_OUTPUT)
		{
			redirect_found(token, temp);
		}
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
}