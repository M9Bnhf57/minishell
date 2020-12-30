/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:02 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/30 12:35:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

/*
**	Error handling.
*/

# define NONE 0
# define SUCCESSED 0
# define FAILED 1
# define ALLOCATION_FAILED -1

void error(char *message);

/*
**	Command table structures.
*/

typedef struct			s_sim_cmd
{
	int					argc;
	char				**args;
	int					is_append;
	char				*out_file;
	char				*in_file;
}						t_sim_cmd;

t_sim_cmd				*create_sim_cmd();
void					delete_sim_command(void *content);
int						insert_arg(t_sim_cmd *sim_cmd, char *arg);

typedef struct			s_cmd
{
	t_list				*sim_cmds;
}						t_cmd;

t_cmd					*g_cur_cmd;
t_sim_cmd				*g_cur_sim_cmd;

int						add_command(t_list **command);
void					delete_command(void *content);
int						insert_sim_cmd(t_cmd *cmd, t_sim_cmd *sim_cmd);
void					free_args(char **args);
int						enlarge_args(t_sim_cmd *sim_cmd, char *new_arg);
int						execute(t_cmd *command);

/*
**	Lexer
*/

# define STRONG_OPEN 256
# define WEAK_OPEN 257
# define SLASH_OPEN 258
# define SLASH_WEAK_OPEN 259
# define CLOSE 260
# define ENV_WEAK_OPEN 261

typedef struct	s_token
{
	char*		value;
	int			name;
}				t_token;

t_list	*run_lexer(const char *input);

/*
**	token.c
*/

int		add_token(t_list **tokens, int name, char *value);
void	delete_token(void *content);
int		try_add_word_token(t_list **tokens, char **tmp, int quote);

# define SEPARATOR 59
# define STRONG_QUOTE 39
# define WEAK_QUOTE 34
# define LESS 60
# define GREAT 62
# define GREATGREAT 63
# define PIPE 124
# define LAST_RESULT 37
# define ENV 36
# define WORD 127
# define ERROR 32
# define BLANK 33

/*
**	lexer_utils.c
*/

int	add_letter(char **str, char c);
int	get_word(char **src, char **dest, int quote);

/*
**	Parser
*/

t_list *run_parser(t_list *tokens);

/*
**	Enviroment
*/

typedef struct	s_env_var
{
	char		*name;
	char		*value;
}				t_env_var;

t_list			*g_env_vars;
int				g_last_result;

int				add_env_var(t_list **env_vars, char *name, char *value);
char			*find_env_var(t_list *env_vars, char *name);
char **list_to_array(t_list *list);

#endif
