#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// random comment (nicht entfernen)

# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_SPACE,
	TOKEN_PIPE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_DOUBLE_REDIRECT_INPUT,
	TOKEN_DOUBLE_REDIRECT_OUTPUT,
}					t_token_type;

typedef struct s_token
{
	char			*content;
	int				len;
	t_token_type	type;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

void				tokenize(char *input);

#endif
