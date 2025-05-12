#include "inc/minishell.h"

int	main(int ac, char **av)
{
	char			*prompt;
	static char		*content;
	t_list			tokens;
    t_garbage       *garbage;
	int				i;

	(void)ac;
	(void)av;
	ft_bzero(&tokens, sizeof(t_list));
	tokens.size = 0;
	while (1)
	{
		prompt = readline("~/minishell$ ✗ ");
		if (!finish_prompt(prompt))
			break ;
		if (!prompt)
			break ;
		content = str_trim(prompt);
		free(prompt);
		if (!content || !*content)
		{
            write(2, "Memory Error\n", 13);
            if (tokens.size)
                clear_list(&tokens);
            exit(0);
        }
        garbage_collector(&garbage, add_garbage(content, NULL));
		i = 0;
		tokenizer(&tokens, content, &i);
        garbage_collector(&garbage, add_garbage(NULL, &tokens));
	}
	// print_list(&tokens);
	return (0);
}
