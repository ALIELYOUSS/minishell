#include "../inc/minishell.h"
// o(n)
int	hrdoc_se(t_list *tokens)
{
	t_tokens	*tmp;

	if (tokens->head->type == HRDOC)
	{
		tmp = tokens->head->next;
		if (find_token(tmp, HRDOC))
			return (0);
	}
	return (1);
}

void	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;

	tmp = tokens->head;
	while (tmp)
	{
		tmp = tmp->next;
	}
}