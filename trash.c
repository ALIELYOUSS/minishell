// char	*parse_key(char *key)
// {
// 	char	*new_key;
// 	int		i;
// 	int		x;
	
// 	i = 0;
// 	x = 0;
// 	new_key = malloc(ft_strlen_value(key));
// 	if (!new_key)
// 		return (NULL);
// 	while (key && key[i])
// 	{
// 		if (char_state(key[i]) == 1)
// 			new_key[x++] = key[i];
// 		else
// 			return (NULL);
// 		i++;
// 	}
// 	return (new_key);
// }



// char	*join_data(char *str, char* str_cotes)
// {
// 	char	*goat;
// 	int		i;
// 	int		x;

// 	i = 0;
// 	x = 0;
// 	goat = malloc(cotes_len(str_cotes) + ft_strlen(str) + 1);
// 	if (!goat)
// 		return (goat);
// 	while (str_cotes[i])
// 	{
// 		if (str_cotes[i] != '$')
// 			goat[x++] = str[i];
// 		else if (str_cotes[i] == '$')
// 		{
// 			while (str[x++])
// 				goat[x] = str[x];
// 		}
// 		while (str_cotes[i] && str_cotes[i] > 65 && str_cotes[i] < 90)
// 			i++;
// 		i++;
// 	}
// 	goat[x] = '\0';
// 	return (goat);
// }

// char	*parser(char *str, char *new_val)
// {
// 	char	*new_input;
// 	int 	i;
// 	int 	x;
// 	int 	j;

// 	i = 0;
// 	x = 0;
// 	j = 0;
// 	new_input = malloc(count_expand_len(str) + ft_strlen(new_val) + 1);
// 	if (!new_input)
// 		return (NULL);
// 	while (x < count_expand_len(str) + ft_strlen(new_val))
// 	{
// 		if (str[i + 1] && !expand_format(str[i], str[i + 1]))
// 			new_input[x] = str[i];
// 		if (str[i] == '$' && !new_val)
// 		{
// 			while ((str[i] && str[i] != '\'') || (str[i] != '"' || str[i] != ' '))
// 				i++;
// 		}
// 		if (str[i] && str[i] == '$' && new_val != NULL)
// 		{
// 			while (new_val[j++])
// 				new_input[x++] = new_val[j];
// 		}
// 		x++;
// 		i++;
// 	}
// 	new_input[x] = '\0';
// 	return (new_input);
// }

// void	add_node_to_garbage_list(t_garbage **gb_list, t_garbage *new_node)
// {
// 	t_garbage	*tmp;

// 	tmp = NULL;
// 	if (!*gb_list)
// 	{
// 		*gb_list = new_node;
// 		return ;
// 	}
// 	else
// 	{
// 		tmp = *gb_list;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_node;
// 	}
// }

// t_garbage	*creat_garbage_node(void *content)
// {
// 	t_garbage	*new_node;

// 	new_node = malloc(sizeof(t_garbage));
// 	if (!new_node)
// 		error_msg("");
// 	if (content)
// 	{
// 		new_node->address = content;
// 		new_node->next = NULL;
// 	}
// 	return (new_node);
// }

// t_garbage	**get_garbage_list(int flag)
// {
// 	static t_garbage *gb_list;
	
// 	if (flag == GET)
// 		return (&gb_list);
// 	return (&gb_list);
// }

// void	* ft_malloc(void *ptr_to_free, size_t size)
// {
// 	t_garbage	**garbage_list;
// 	t_garbage			*new;
	
// 	garbage_list = get_garbage_list(GET);
// 	ptr_to_free = malloc(size);
// 	new = NULL;
// 	if (!ptr_to_free)
// 		error_msg("");
// 	new = creat_garbage_node(ptr_to_free);
// 	add_node_to_garbage_list(garbage_list, new);
// 	return (ptr_to_free);
// }

// void	free_garbage_coll(void)
// {
// 	t_garbage	**gb_list;
// 	t_garbage	*tmp;
// 	t_garbage	*current;

// 	tmp = NULL;
// 	gb_list = get_garbage_list(GET);
// 	current = *gb_list;
// 	while (current->next)
// 	{
// 		tmp = current->next;
// 		if (current && current->address)
// 			free(current->address);
// 		free(current);
// 		current = tmp;
// 	}
// 	*gb_list = NULL;
// }
