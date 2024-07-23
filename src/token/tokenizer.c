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
	else if (input[i] == '<' && input[i + 1] == '<')
		temp->type = TOKEN_DOUBLE_REDIRECT_INPUT;
	else if (input[i] == '<')
		temp->type = TOKEN_REDIRECT_INPUT;
	else if (input[i] == '>' && input[i + 1] == '>')
		temp->type = TOKEN_DOUBLE_REDIRECT_OUTPUT;
	else if (input[i] == '>')
		temp->type = TOKEN_REDIRECT_OUTPUT;
	fill_token(token, input, i, temp->type);
}

void	tokenize(t_token **token, char *input)
{
	t_token	*temp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	temp = NULL;
	while (input[i])
	{
		if (ft_strchr_i(" |'\"<>", input[i]) != -1)
			which_delimiter(token, input, i);
		else
		{
			token_new(token);
			temp = tokenlast(token);
			while (ft_strchr_i(" |'\"<>", input[i + x]) == -1 && input[i + x])
				x++;
			temp->content = ft_substr(input, i, x);
			temp->len = ft_strlen(temp->content);
			temp->type = TOKEN_WORD;
		}
		x = 0;
		temp = tokenlast(token);
		i += temp->len;
	}
	temp = tokenfirst(token);
	if (DEBUG_MODE)
		printf("Tokens:\n");
	while (temp && DEBUG_MODE)
	{
		printf("**********\n");
		printf("content: %s\n", temp->content);
		printf("len: %d\n", temp->len);
		printf("type: %d\n", temp->type);
		temp = temp->next;
	}
}
