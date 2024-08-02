#include "minishell.h"

void	expander(t_token **token, char **envp)
{
	t_token	*temp;
	int		i;
	char	*temp_content;

	temp_content = NULL;
	temp = tokenfirst(token);
	while (temp->content)
	{
		if (temp->type == TOKEN_WORD && temp->content[0] == '$')
		{
			i = 0;
			temp_content = ft_strtrim(ft_strdup(temp->content), "$");
			while (envp[i])
			{
				if (ft_strncmp(envp[i], temp_content, ft_strlen(temp_content)) == 0 && envp[i][ft_strlen(temp_content)] == '=')
				{
					free(temp->content);
					temp->content = ft_strdup(ft_strchr(envp[i], '=') + 1);
					break ;
				}
				i++;
			}
		}
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
}
