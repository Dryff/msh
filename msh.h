/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:47:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/07 14:31:57 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "ft_err_printf/ft_printf.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

# define NT_VALID_ID 1
# define SYNTAX_ERROR 2
# define IS_DIRECTORY 126
# define PERM_DENIED 126
# define CMD_NT_FND 127
# define CTRL_C 130
# define CTRL_SLASH 131

typedef struct s_cmd
{
	char	**param;
	int		here_doc;
}				t_cmd;

typedef struct s_env
{
	char	**tab;
	char	**sort_tab;
}				t_env;

typedef struct s_fildes
{
	int		input;
	int		output;
	int		infd;
	int		outfd;

	char *in_name;
	char	*out_name;

}				t_fildes;

typedef struct s_parse
{
	int		i;
	int		strt;
	int		arg_sz;
	char	q;
	char	*line;
}				t_parse;

typedef struct s_msh
{
	t_env		env;
	t_fildes	fildes;
	t_cmd		*cmd;
	int			cmd_nbr;
	int			pid;
	char		**paths;
	char		**historic;
	char		*prompt;
	char		*line;
	char		*ex_val;
} 				t_msh;
/* Minishell */
int		minishell(t_msh *msh);
void	free_things(t_msh msh);

/* DVD*/
char	*get_dvd_cmd(char *line);
void	ft_dvd(t_msh *msh, int cmd_id);

/* HISTORIC */
void	init_history(void);
void	custom_add_history(char *line);

/* Env */
t_env	init_env(char **envp);
void	ft_print_env(t_msh *msh);
void	ft_declare_print(t_env *env);
char	*get_export_cmd(char *line);
int		ft_export(t_msh *msh, int cmd_id);
int		*ft_bool_strnstr(const char *haystack, const char *needle, size_t len);
char	**add_comand_to_tab(char **tab, char *cmd);
char	**envp_dup(char **tab);
void	free_env(t_msh msh);
char **init_secret_env(char **envp);

/* Export*/
void	add_export(t_msh *msh, char *cmd);
void	add_invisible_export(t_msh *msh, char *cmd);
void	replace_export(t_msh *msh, char *cmd, int pos);
int		get_position(char **tab, char *cmd);
void	ft_export_print(char *str);
void	ft_strswap(char **str1, char **str2);
int		ft_strcmp(char *s1, char *s2);
void	replace_secret_export(t_msh *msh, char *cmd, int index);
int	complete_export(t_msh *msh, char *cmd);

/* UNSET attention ca va chauffer sa mere*/
char	*get_unset_cmd(char *line);
void	ft_unset(t_msh *msh, int cmd_id);

/* Expand */
char	*ft_expand(t_env *env, char *cmd);
char	*ft_expand_tab(char **tab, char *cmd);
char	*get_expand_cmd(char *str);

/* builtins */
int		exec_builtin_cmd(t_msh *msh);
int		is_builtin(char *cmd);
int		is_not_builtin_fd(char *cmd);
int		exec_builtins(t_msh *msh, int cmd_id, int builtin);

/* signal */
void signal_handler(int signal_num);

/* Cmd_utils */
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strstr(const char *str, const char *to_find);
char	*ft_strjoin(char const *s1, char const *s2);
int		commands(t_msh *msh);
char	**get_paths(char **envp);
char	*get_pathing(t_msh msh, int j);
int		here_doc(t_msh *msh);
char	*ft_itoa(int n);

/* Msh_utils */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	free_all(char **strs);

/* Parsing */
int		parse_line(t_msh *msh);
int 	get_cmd_nbr(char *str);
int 	open_fd(t_msh *msh);
int 	check_fd(t_msh *msh, int i, int j);
int 	get_quote(char *s, int i);
int 	is_in_quote(char *s, int i, char quote, int start);
int 	get_and_check_fd(t_msh *msh);
char	*replace_env_arg(t_msh *msh, t_parse *p, int cursor);
int		is_end_of_arg(int i, char *line, char q, int s);
char	*rm_quotes(t_msh msh, char *sub);
char	*get_dollar(t_msh *msh, t_parse *p);
char	*getline_rm_quote(t_parse p);
int		quote_rm_nbr(t_parse p);
char	*replace_spaces(t_parse p);
int		go_to_end_quote(int i, char *line, char q, int s);
int		parse_fd_data(t_msh *msh);
int		is_alpha(char c);

int		is_name_before_arrow(t_msh *msh, int i);
int		get_cmd_is_after_arrow(t_msh *msh, int i);
int		get_size_until_arrow(t_msh *msh, int i);

/* Basic utils */
char	**ft_split(char const *str, char c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);
int		ft_strlen_until(char *str, char c);
int		is_in_charset(char c, char *str);
void	sort_tab(t_env *env);
char	**tab_dup(char **tab);
void	free_tab(char **tab);

/* Parse_utils */
int		is_delimiter(char c);
int		is_white_space(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		get_size(char *s, int i);
char	*ft_strjoin_by_sep(char const *s1, char const *s2);

#endif