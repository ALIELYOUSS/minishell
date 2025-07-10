#include "inc/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env	*env_list;
	t_env	*tmp;
	env_list = fill_env_list(env);
	tmp = env_dup(env_list);
	sort_env(&tmp);
	print_env(tmp, "hello -x  ");
	return (0);
}
