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
}						t_token_type;

typedef struct s_token
{
	char				*content;
	int					len;
	t_token_type		type;
	int					priority;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

# define PRINT_INPUT 0
# define PRINT_TOKENS 0

void					tokenize(t_token **token, char *input);
t_token					*tokenfirst(t_token **token);
t_token					*tokenlast(t_token **token);
void					token_new(t_token **token);
void					get_priority(t_token **token);
t_ast_node				*get_ast(t_token *token);

#endif
