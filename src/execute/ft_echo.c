#include "minishell.h"

bool	newline_check(t_token *temp)
{
	bool	newline_flag;

	newline_flag = true;
	while (temp->content)
	{
		if (temp->type == TOKEN_WORD)
		{
			if (ft_strncmp(temp->content, "-n", 2) == 0)
			{
				newline_flag = false;
				if (DEBUG_MODE)
					printf("-n found\n");
			}
			else
				return (newline_flag);
			temp = temp->next;
		}
	}
	return (newline_flag);
}

bool	ft_echo(t_token **token)
{
	t_token	*temp;
	bool	newline_flag;

	newline_flag = true;
	temp = tokenfirst(token);
	if (!temp->next)
	{
		if (DEBUG_MODE)
			printf("no ->next after echo");
		return (newline_flag);
	}
	else
		temp = temp->next;
	if (DEBUG_MODE)
		printf("newline_flag: %d\n", newline_flag);
	newline_flag = newline_check(temp);
	if (DEBUG_MODE)
		printf("newline_flag: %d\n", newline_flag);
	while (temp->content)
	{
		if (temp->type == TOKEN_WORD || temp->type == TOKEN_WORD_IN_QUOTE)
			printf("%s", temp->content);
		if (temp->next)
			temp = temp->next;
		else
			break;
		if (temp->type == TOKEN_WORD || temp->type == TOKEN_WORD_IN_QUOTE)
			printf(" ");
	}
	return (newline_flag);
}
