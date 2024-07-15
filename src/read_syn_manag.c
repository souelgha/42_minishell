/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_syn_manag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:43:37 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 10:16:07 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 
static char	*ft_strnstr_mini(const char *big, const char *little, size_t len);

int	syn_manag(char *str, t_data *data)
{
	if (syn_manag_two(str, data) == 1 || syn_manag_three(str, data) == 1)
		return (1);
	if (str[0] == '!' && str[1] == '\0')
	{
		data->status = 1;
		return (1);
	}
	else if (str[0] == ':' || str[0] == '#')
	{
		data->status = 0;
		return (1);
	}
	else if (str[0] == '|' || str[0] == '&' || str[0] == '('
		|| str[0] == ')' || str[0] == ';')
	{
		data->status = 2;
		ft_fprintf(2, "minishell: syntax error near"
			" unexpected token « %c »\n", str[0]);
		return (1);
	}
	return (0);
}

int	syn_manag_two(char *str, t_data *data)
{
	char	*check;

	check = NULL;
	check = ft_strnstr_mini(str, "| |", ft_strlen(str));
	if (check)
		return (error_syn(check, 1, data));
	check = ft_strnstr_mini(str, "&&", ft_strlen(str));
	if (check)
		return (error_syn(check, 1, data));
	check = ft_strnstr_mini(str, ">> >>", ft_strlen(str));
	if (check)
		return (error_syn(check, 1, data));
	check = ft_strnstr_mini(str, "<< <<", ft_strlen(str));
	if (check)
		return (error_syn(check, 1, data));
	check = ft_strnstr_mini(str, "> >", ft_strlen(str));
	if (check)
		return (error_syn(check, 3, data));
	check = ft_strnstr_mini(str, "< <", ft_strlen(str));
	if (check)
		return (error_syn(check, 3, data));
	return (0);
}

int	syn_manag_three(char *str, t_data *data)
{
	char	*check;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	check = NULL;
	check = ft_strnstr_mini(str, "< >", ft_strlen(str));
	if (check)
		return (error_syn(check, 2, data));
	check = ft_strnstr_mini(str, "> <", ft_strlen(str));
	if (check)
		return (error_syn(check, 2, data));
	check = ft_strnstr_mini(str, "||", ft_strlen(str));
	if (check)
		return (error_syn(check, 1, data));
	return (0);
}

int	error_syn(char *check, int help, t_data *data)
{
	if (help == 1)
		ft_fprintf(2, "minishell: syntax error near"
			" unexpected token « %c%c »\n", check[0], check[0]);
	else if (help == 2)
		ft_fprintf(2, "minishell: syntax error near"
			" unexpected token « %c »\n", check[2]);
	else if (help == 3)
		ft_fprintf(2, "minishell: syntax error near"
			" unexpected token « %c »\n", check[0]);
	data->status = 2;
	return (1);
}

static char	*ft_strnstr_mini(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	j = 0;
	while (j < len && big[j])
	{
		help_strnstr(big, &j);
		i = 0;
		while (j < len && little[i] && big[j] && little[i] == big[j])
		{
			++i;
			++j;
		}
		if (little[i] == '\0')
			return ((char *)&big[j - i]);
		j = j - i + 1;
	}
	return (0);
}
