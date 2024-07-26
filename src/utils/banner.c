# include "minishell.h"

void	banner(void)
{
	printf(" ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf(" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf(" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
	printf(" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf(" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf(" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\033[0m\n");
	printf("\t\tMADE BY JMUHLBER & VISIVANAT\n");
	printf("\t\t    MADE AT 42 HEILBRONN\n");
	printf("\t\tMINISHELL PROJECT @ 42CURSUS\n\n");
}

void initialize_randomizer(void)
{
	srand((unsigned int)getpid());
}

int get_random_number(void)
{
	return (rand() % 24);
}

void print_banner(void)
{
	int i;
	int x;

	initialize_randomizer();
	i = get_random_number();
	printf("\n");
	if (i % 3 == 0)
		printf("\033[0;3%d;7m", i / 3);
	else
	{
		if (i % 3 == 1)
		{
			x = 1;
			i -= 1;
		}
		else
		{
			x = 0;
			i -= 2;
		}
		printf("\033[%d;3%dm", x, i / 3);
	}
	banner();
}
