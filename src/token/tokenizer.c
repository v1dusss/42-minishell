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
	t_token		*new;
	t_token		*temp;
	static int	index;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc");
		exit(1);
	}
	new->next = NULL;
	if (index == 0)
	{
		new->index = index++;
		*token = new;
		new->prev = NULL;
	}
	else
	{
		new->index = index++;
		temp = tokenlast(token);
		temp->next = new;
		new->prev = *token;
		*token = new;
	}
}

void	fill_token(t_token **token, char *input, int i, t_token_type type)
{
	t_token	*temp;

	temp = tokenlast(token);
	if (type == TOKEN_DOUBLE_REDIRECT_INPUT
		|| type == TOKEN_DOUBLE_REDIRECT_OUTPUT)
		temp->len = 2;
	else
		temp->len = 1;
	temp->content = ft_substr(input, i, temp->len);
}

void	which_delimiter(t_token **token, char *input, int i)
{
	t_token	*temp;

	token_new(token);
	temp = tokenlast(token);
	if (input[i] == ' ')
		temp->type = TOKEN_SPACE;
	else if (input[i] == '|')
		temp->type = TOKEN_PIPE;
	else if (input[i] == '\'')
		temp->type = TOKEN_SINGLE_QUOTE;
	else if (input[i] == '\"')
		temp->type = TOKEN_DOUBLE_QUOTE;
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			temp->type = TOKEN_DOUBLE_REDIRECT_INPUT;
		else
			temp->type = TOKEN_REDIRECT_INPUT;
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			temp->type = TOKEN_DOUBLE_REDIRECT_OUTPUT;
		else
			temp->type = TOKEN_REDIRECT_OUTPUT;
	}
	fill_token(token, input, i, temp->type);
}

void	tokenize(char *input)
{
	t_token	*token;
	t_token	*temp;
	int		i;

	i = 0;
	while (input[i])
	{
		if (ft_strchr_i(" |'\"<>", input[i]) != -1)
		{
			which_delimiter(&token, input, i);
			i += tokenlast(&token)->len;
		}
		else
		{
			token_new(&token);
			temp = tokenlast(&token);
			temp->content = ft_substr(input, i, ft_strchr_i(" |'\"<>",
						input[i]));
			temp->len = ft_strlen(temp->content);
			temp->type = TOKEN_WORD;
			i += temp->len;
		}
	}
	temp = tokenfirst(&token);
	printf("Tokens:\n");
	while (temp)
	{
		printf("**********\n");
		printf("content: %s\n", temp->content);
		printf("len: %d\n", temp->len);
		printf("type: %d\n", temp->type);
		printf("index: %d\n", temp->index);
		temp = temp->next;
	}
}
