#include "minishell.h"

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
	int		index;
	int		i;
	int		x;

	index = 0;
	i = 0;
	x = 0;
	token = NULL;
	temp = NULL;
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
			while (ft_strchr_i(" |'\"<>", input[i + x]) == -1 && input[i + x])
				x++;
			temp->content = ft_substr(input, i, x);
			temp->len = ft_strlen(temp->content);
			temp->type = TOKEN_WORD;
			i += temp->len;
		}
		x = 0;
		temp = tokenlast(&token);
		temp->index = index++;
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
