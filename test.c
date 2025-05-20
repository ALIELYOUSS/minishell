#include "inc/minishell.h"

int	its_token(t_tokens *tokens, t_type type)
{
	if (tokens->type == type)
		return (1);
	return (0);
}

int	find_token(t_tokens *tokens, t_type type)
{
	t_tokens	*tmp;
	
	tmp = tokens;
	while (tmp)
	{
		if (its_token(tmp, type))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

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
	return (0);
}
