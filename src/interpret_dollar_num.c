/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_dollar_num.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:22:37 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 10:09:16 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static char	*lp_isnum_dollar(char **str, int st_to, t_data *data, char *al_str);
static void	just_checking(char **str, t_data *data, char **fp, char **lp);

/**** gerer le cas ou on a $chiffre clean string******/
void	clean_isnum_dollar(char **str, t_data *data)
{
	int		i;
	char	*first_part;
	char	*last_part;

	i = 0;
	while ((*str)[i] != '$')
		i++;
	first_part = get_first_part_clear(str, i, data);
	last_part = lp_isnum_dollar(str, i, data, first_part);
	free(*str);
	just_checking(str, data, &first_part, &last_part);
}

static void	just_checking(char **str, t_data *data, char **fp, char **lp)
{
	if (!(*fp) && !(*lp))
	{
		*str = NULL;
		return ;
	}
	else if (!(*fp))
		(*str) = ft_strdup((*lp));
	else if (!(*lp))
		(*str) = ft_strdup((*fp));
	else
		(*str) = ft_strjoin((*fp), (*lp));
	if ((*fp))
		free((*fp));
	if ((*lp))
		free((*lp));
	if (!(*str))
		ex_malloc(NULL, NULL, data);
}

/*chercher le caractère "$" dans notre str de base*/
/**** gerer le cas ou on a $chiffre recup du last******/
//last_after_isnum_dollar(char **str, int start_to,
//t_data *data, char *alloc_char)
static char	*lp_isnum_dollar(char **str, int st_to, t_data *data, char *al_str)
{
	int		start;
	char	*last_part;

	if ((*str)[st_to] == '$')
		st_to++;
	while ((*str)[st_to] && (ft_isdigit((*str)[st_to])))
		st_to++;
	start = st_to;
	last_part = help_lp_dollar(str, start, data, al_str);
	return (last_part);
}
