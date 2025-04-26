#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_break(char *prompt)
{
	int	i;

	if (!prompt)
		return (0);
	i = 0;
	while (ft_isspace(prompt[i]))
		i++;
	if (prompt[i] && !ft_strncmp("exit", &prompt[i], 4))
	{
		i += 4;
		while (ft_isspace(prompt[i]))
			i++;
		if (!prompt[i])
			return (0);
	}
	return (1);
}

int	finish_prompt(char *prompt)
{
	if (!ft_break(prompt))
	{
		if (prompt)
			free(prompt);
		return (0) ;
	}
	return (1);
}