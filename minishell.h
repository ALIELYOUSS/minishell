/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:25:41 by yael-maa          #+#    #+#             */
/*   Updated: 2025/04/24 18:30:08 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_type {
	WORD,
	OUT,
	IN,
	APP,
	HRDOC,
	AND,
	OR,
	PIPE,
	LP,
	RP,
}	t_type;

typedef struct s_tokens {
	t_type				type;
	char				*content;
	struct	s_tokens	*next;
}	t_tokens;

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

#endif