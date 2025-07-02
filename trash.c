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