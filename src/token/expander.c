#include "minishell.h"

void	expander(t_token **token, char **envp)
{
	t_token	*temp;
	int		i;

	temp = tokenfirst(token);
	while (temp->content)
	{
		if (temp->type == TOKEN_WORD && temp->content[0] == '$')
		{
			i = 0;
			while (envp && envp[i])
			{
				if (ft_strncmp(envp[i], temp->content + 1,
						ft_strlen(temp->content + 1)) == 0)
				{
					free(temp->content);
					temp->content = ft_strdup(envp[i]
							+ ft_strlen(temp->content));
					break ;
				}
				i++;
			}
			if (temp->content[0] == '$')
			{
				free(temp->content);
				temp->content = ft_strdup("");
			}
		}
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
}
