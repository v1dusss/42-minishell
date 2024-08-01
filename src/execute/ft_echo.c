#include "minishell.h"

bool	n_check(t_token *temp)
{
	int		i;

	i = 1;
	while (temp->content[i])
	{
		if (temp->content[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	newline_check(t_token *temp)
{
	bool	newline_flag;

	newline_flag = true;
	while (temp->content)
	{
		if (temp->type == TOKEN_WORD || temp->type == TOKEN_WORD_IN_QUOTE)
		{
			if (ft_strncmp(temp->content, "-n", 2) == 0)
			{
				if (n_check(temp))
					newline_flag = false;
				else
					return (newline_flag);
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
	while (ft_strncmp(temp->content, "-n", 2) == 0 && temp->next)
	{
		if (n_check(temp))
			temp = temp->next;
		else
			break;
	}
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
