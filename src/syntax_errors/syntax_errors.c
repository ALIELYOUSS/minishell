#include "../inc/minishell.h"

void	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;

	if (operator(tokens->head) || operator(tokens->tail) || tail_isredir(tokens))
		syntax_error_msg(tokens);
	tmp = tokens->head;
	while (tmp)
	{
		if (((operator(tmp) || is_redir(tmp)) && prev_node(tokens, tmp)) || (operator(tmp) && operator(tmp->next)))
			syntax_error_msg(tokens);
		else if (its_token(tmp, HRDOC))
		{
			if (tmp == tokens->tail || tmp->next->type != WORD)
				syntax_error_msg(tokens);
		}
		// else if (its_token(tmp, PIPE))
		// {
		// 	if (!pipe_se(tokens, tmp))
		// 		syntax_error_msg(tokens);
		// }
		tmp = tmp->next;
	}
}
