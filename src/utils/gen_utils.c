/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//Returns 0 if s1's first non space chars are equal to s2
int	first_str(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 == ' ')
		s1++;
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}

bool	char_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

bool	only_digits(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

// print error to stderr
void	pe(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
}

// print error to stderr with msg ex:(Error: invalid map)
void	pe_msg(char *err, char *msg)
{
	pe(err);
	pe(msg);
	pe("\n");
}
