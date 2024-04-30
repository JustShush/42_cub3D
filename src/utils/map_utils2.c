/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_chrtrim(char *line, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] == c)
		i++;
	j = i;
	while (line[j] != c && line[j])
		j++;
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (line[i] != c && line[i] && line[i] != '\n')
	{
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

void	make_null(t_map map, char dir)
{
	if (dir == 'C')
	{
		free(map->textures->c);
		map->textures->c = NULL;
	}
	else if (dir == 'F')
	{
		free(map->textures->f);
		map->textures->f = NULL;
	}
}
