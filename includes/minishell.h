/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 14:20:46 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE 1
# include <stddef.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h" 
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

//0 = no token
//1 = >>
//2 = >
//3 = <<
//4 = <

typedef struct s_fd
{
	int	fd_redirect_in;
	int	fd_redirect_out;
	int	fd_redirect_err;
}			t_fd;

typedef struct s_arg
{
	char			*str;
	struct s_arg	*next;
}			t_arg;

typedef struct s_redirect
{
	char				*red;
	int					token;
	int					fd_here_doc;
	struct s_redirect	*next;
}			t_redirect;

typedef struct s_info_fd
{
	int			fdpipe[2];
	int			fd_0;
	int			index;
	int			oldfd_in;
	int			oldfd_out;
	int			bool;
}				t_info_fd;

typedef struct s_command
{
	t_arg				**arg;
	t_redirect			**info;
	t_fd				fd_prio;
	int					oldfd_in;
	int					oldfd_out;
	pid_t				pid;
	struct s_command	*next_command;
}			t_command;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_exec_command
{
	char	**path_envp;
	char	*path_name;
	char	**my_envp;
	char	**my_argv;
}				t_exec;

typedef struct s_data
{
	t_command	**command;
	t_env		**env;
	int			status;
	int			ex_g_fd;
}				t_data;

/*----------------------------------------------------------------------------*/
//test
void		print_for_test(t_command **command);
void		print_env(char **envp);

/*----------------------------------------------------------------------------*/
//CONSTRUCTION ENV

//initialisation data
void		init_data(t_data **data);

//initialisation de la liste chainée envp
void		env_cpy(char **envp, t_data *data, int i, int j);
void		maj_pwd(t_data *data);

//envp_utils.c
t_env		*add_node(void);
void		get_nodded(char *var_1, char *value_1, t_data *data);
void		env_empty(char *var_1, char *value_1, t_data *data);
void		cpy_var_value(char *var_1, char *value_1, t_data *data, t_env *tmp);

/*----------------------------------------------------------------------------*/
//CONSTRUCTION TERMINAL

//loop.c
int			loop_minishell(t_data *data);
int			loop_bis(char *prompt_line, t_data *data, char **tmp);

//loop_utils.c
char		*find_endpwd(t_data *data);
char		*find_currentdir(t_data *data);
char		*find_home_dir(t_data *data);
char		*currentdir_null(t_data *data);

/*----------------------------------------------------------------------------*/
//LECTURE

//read_line.c
char		*read_until(char *prompt_line, t_data *data);
char		*check_readed_line(char *str, int *start, t_data *data);
char		*help_check_readed_line(char *str, int *st, t_data *data);
int			is_this_a_heredoc(char *tmp, int *st);
void		help_tmp_null(char *prompt_line, t_data *data);

//syntaxe management
int			syn_manag(char *str, t_data *data);
int			syn_manag_two(char *str, t_data *data);
int			syn_manag_three(char *str, t_data *data);
int			error_syn(char *check, int help, t_data *data);

//read_line_outils.c
int			help_double_quotes(char **tmp, char *str, int *start, t_data *data);
int			help_quotes(char **tmp, char *str, int *start, t_data *data);
char		*join_arg(char **old, char *new, char c, t_data *data);
void		*g_fd_is_not_minus_one(char *old, char *new, t_data *data);
void		help_strnstr(const char *big, size_t *j);
//
int			check_double_quotes(char **str, int *start, t_data *data);
int			check_quotes(char **str, int *start, t_data *data);
int			found_dollar(char **str, int *start);

//lecture HERE_DOC
int			help_here_doc(char **tmp, int *start, t_data *data);
char		*join_str_here_doc(char *old, char **new, char *limi, t_data *data);
void		*gf_d_not_minus_join(char **old, char **new, char **lim, t_data *d);
int			check_limite(char *limite, char *str, int j, int size);

//utils lecture here_doc
char		*get_limite(char **tmp, int *start, t_data *data, int size);
int			ft_get_size_limite(char **tmp, int *start);
char		*get_rest_after_pipe(char *limite, char **tmp, t_data *data);
char		*help_g_r_a_p(int size_rest, char *limite, char *tempo, char **tmp);
int			get_both_size(char *limit, char **tmp, int *s_first, int *s_rest);

/*----------------------------------------------------------------------------*/
//INTERPRETATION

//interpretation des $VAR : interpret.c
void		interpret(char **str, t_data *data);
char		*var_env(char **str, int *index, t_data *data);
void		fill_in(char **str, char *to_put_in, int *index, t_data *data);

//interpret_2.c
char		*recept_exist(char **recept);
int			check_end(char **str, int i, char *limite);
char		*choose(int *i, char **str, t_data *data);

//clean str interpret $: clean_str_inter_dollar.c
void		clean_str_after_dollar(char **str, t_data *data, int *index);
char		*get_first_part_clear(char **str, int until, t_data *data);
char		*help_lp_dollar(char **str, int start, t_data *data, char *al_str);

//interprete $ avec num : interpret_dollar_num.c
void		clean_isnum_dollar(char **str, t_data *data);

//interpret_utils
char		*help_last_part(char **str, int start, t_data *data, char *s);
char		*get_first_part(char **str, int until, t_data *data);
char		*get_last_part(char **str, int start_to, t_data *data, char *s);
char		*find_var(char *name_var, t_data *data);
char		*replace(int status);
int			help_interpret_dollar(char **str, t_data *data, int *index);

//interpret_pipe.c
void		check_value(char **value, t_data *data, char **str);

/*----------------------------------------------------------------------------*/
//PARSING

//
void		parsing(char *str, t_data *data);
char		**parsing_split(char const *s, char c);
void		add_node_command(t_command **command, t_arg **arg, t_redirect **i);
t_command	*new_node_command(void);
int			start_parsing(t_arg	**pa, t_redirect **inf, char **str, t_data *da);

//parsing 2/3.c
void		help_parsing_q(char ***str, int *i, t_arg ***parsed, int *status);
void		help_parsing_dq(char ***str, int *i, t_arg ***parsed, int *status);
void		help_parsing_s(char ***str, int *i, t_arg ***parsed, int *status);
void		help_while_bcl(char ***str, int *i, t_arg ***parsed, int *status);

//parsing_argument // parsing_arg.c
int			space_parsing(t_arg	**parsed, char *str, int *index);
void		get_full_size_of_arg(char *str, int *start, int *size);
int			quotes_parsing(t_arg **parsed, char *str, int *index);
int			double_quotes_parsing(t_arg **parsed, char *str, int *index);

//initialisation node_arg // node_arg.c
t_arg		*add_node_arg(t_arg **parsed, int size);
t_arg		*help_node_arg(t_arg **parsed, int size);
t_arg		*new_node(void);

//parsing_redirection
int			redirection_parsing(t_redirect **in, char **s, int *i, t_data *da);
int			redirection_here_doc(t_redirect *c, char **str, int *i, int size);
int			create_temp_file(char *bla);
int			complete_here_doc(char *limite, char *str, int *i, int fd_origin);
void		clear_str(char **str, int *index, char *limite);
char		*get_last_part_clear_str(char **str, int index);
int			get_redir_size(char **str, int *index, int *start);
int			get_size_redir(char **str, int *start);
int			get_clic(char **str, int *start);
int			check_limite_v2(char *limite, char *str, int j, int size);

//token management
int			erreur_management(char *str, int *index, t_data *data);
int			erreur_management_bis(char *str, int *index, t_data *data);
int			erreur_management_bis_2(char *str, int *index, t_data *data);
int			token_management(char *str, int *index, t_data *data);
int			get_token(char *str, int finded_at);

//initialisation node_info // node_info.c
t_redirect	*new_node_info(void);
t_redirect	*add_node_info(t_redirect **info, int size);
t_redirect	*help_node_info(t_redirect **info, int size);

//parsing_utils
void		ft_strcpy_doubleq(char *dest, char *src, int start, int len);
void		ft_strcpy_space(char *dest, char *src, int start, int len);
void		ft_strcpy_quotes(char *dest, char *src, int start, int len);
void		ft_strcpy_redir(char *dest, char *src, int start, int len);

/*----------------------------------------------------------------------------*/
//FREE MANAGEMENT

void		get_free(char **splitted);
void		free_env(t_env **env);
void		free_arg_list(t_arg **parsed);
void		free_info_list(t_redirect **info);
void		free_command_list(t_command ***command);
void		free_all_object(char *str, char *str1, char *str2, t_data *data);
void		free_char(char *var, char *value);
void		free_data(t_data **data);

/*----------------------------------------------------------------------------*/
//EXECUTIONS DES COMMANDES

//exe_do_command.c
void		direct_command(t_data *data);
void		no_fork(t_command **cmd, t_data *data, t_command *c, t_info_fd *fd);
void		pid_waiting(t_command **command, t_data *data);

//do_command_utils
int			how_much_cmd(t_command **command);
void		init_info_fd(t_info_fd	*fd);

//exe_command
void		exec_command(t_arg **arg, t_data *data);

//exe_command_utils.c
char		**get_path_envp(t_data *data);
char		*find_pathnam(t_arg **ac, char ***tp, t_data *data);
int			check_directory(char *path_name);

//exe_arg_reading.c
void		read_args(t_command **c, t_arg **a, t_data *d, t_info_fd *fd);
int			should_i_fork(t_arg **arg);
void		read_args_bis(t_arg **arg, t_data *data);

//exe_fd_dup_help.c
void		helpdf(t_command *cur, t_info_fd *fd, t_data *data);

//exe_fp_dup.c
void		ex_cmd(t_data *data);
void		whd(t_redirect *tmp, t_info_fd *fd, t_data *data);
char		**erase_temp_file(char *to_erase, t_data *data);

//exe_forking.c
void		forkg(t_command **cmd, t_command *cur, t_info_fd *fd, t_data *data);

//redirection lors de l'execution
int			do_redirect(t_command *cur_cmd, t_data *data);

/*----------------------------------------------------------------------------*/
//ERROR MANAGEMENT

//error.c
int			ex_no_cmd(t_arg **current, t_data *data, t_exec *info);
int			exit_execve(t_arg **current, t_data *data, t_exec *info);
void		ex_pip(char *str);
void		ex_pid(char *str, int *pipefd);
void		exit_error(char	*str);
void		ex_fd(t_command *cu, t_data *data, char **tab);
void		ex_dup2(t_data *data);
void		ex_mallo_fail(t_data *data, char **t, t_arg **p, t_redirect **i);
void		ex_malloc(char **tab, char *str, t_data *data);
void		ex_malloc_bis(char *str_1, char *str_2, char *str_3, t_data *data);
void		ex_close_fail(t_data *data);
char		*syntax_error(char *tmp, int *st, t_data *data);
void		ex_pars(t_command ***c, char ***t, t_arg ***p, t_redirect ***i);
void		ex_direc(char **fil, char ***t_path, t_data *data);
void		ex_no_such(t_arg **a_c, t_data *data);

/*----------------------------------------------------------------------------*/
//SIGNAL HANDLING

//signal.c
void		signal_research(void);
void		signal_research_fork(void);
void		signal_read_line(void);
void		control_c_handler_readline(int num);
void		control_c_handler(int num);
void		ignore_sig(void);

/*----------------------------------------------------------------------------*/
//BUILTINS
/*---------------*/
//do_env.c
int			do_env(t_data *data);
int			check_var_path_exist(t_data *data);
int			check_env_isempty(t_data *data);

/*---------------*/
//do_cd.c

int			do_cd(t_arg **arg, t_data *data);
int			error_management_cd(t_arg **arg, t_data *data, char **getcwd_s);
char		*get_home_dir(t_data *data);
char		*get_old_pwd(t_data *data);
int			helping_cd(t_arg **arg, t_data *data, char **gs);
int			help_do_cd_oldpwd(t_arg **arg, t_data *data);

/*---------------*/
//do_echo.c
int			do_echo(t_arg **arg, t_data *data);
void		echo_no_arg(t_data *data);
void		echo_arg(t_data *data, t_arg *tmp);
int			check_n_char(char *str, char n);

/*---------------*/
//do_unset.c
int			do_unset(t_arg **argn, t_data *data);

/*---------------*/
//do_pwd.c
int			do_pwd(t_arg **arg, t_data *data);
int			find_pwd(t_data *data);

/*---------------*/
//do_export.c
int			do_export(t_arg **arg, t_data *data);

//do_export_arg.c
int			do_export_arg(t_arg **arg, t_data *data);

//do_export_maj.c
int			maj_env(t_arg *var, t_data *data);

//export_utils
int			get_size(char *str);
void		cpy_tab(char **tab_arg, char *str, int size);
char		**splitted_var(char	*str, t_data *data);
int			init_tab_arg(char **tab_arg, char *str, int size);
int			help_init_tab(char **tab_arg, char *str, int size, int i);

/*---------------*/
//check name var pour export et unset
int			while_check_name(t_arg *arg, char *built);
int			check_name_var(t_arg *arg, char *built);
int			check_first_char_var(t_arg *arg, char *built);

/*---------------*/
//exit
int			do_exit(t_arg **arg, t_data *data, t_info_fd *fd);

/*---------------*/

#endif
