/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_map_closed(t_map map, char **bmap)
{
	int		i;
	//int		j;
	char	**copy;
	(void)map;

	//j = 0;
	i = get_start_map(bmap);
	copy = copy_array(bmap);
	if (i + 1 < 0 || !bmap[i + 1] || first_str(bmap[i + 1], "1"))
	{
		free_array(copy);
		return (1);
	}
	//if (support_check_map(copy, i, j, map) == 1)
	//	return (1);
	free_array(copy);
	return (0);
}

int	check_chars(char **map)
{
	int	i;
	int	j;
	int	check;

	i = get_start_map(map);
	check = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'N' || map[i][j] == 'S'))
				check++;
			else if (map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != '\n' && map[i][j] != ' ' && map[i][j] != '\t')
				return (printf(
						"Error\nInvalid character found\n"));
			j++;
		}
		i++;
	}
	if (check != 1)
		return (printf("Error\nWrong player count\n"));
	return (1);
}

/*int	check_valid_color(t_textures textures)
{
	if (textures.c->r > 255 || textures.c->r < 0)
		return (printf("Error\nInvalid color\n"));
	if (textures.c->g > 255 || textures.c->g < 0)
		return (printf("Error\nInvalid color\n"));
	if (textures.c->b > 255 || textures.c->b < 0)
		return (printf("Error\nInvalid color\n"));
	if (textures.f->r > 255 || textures.f->r < 0)
		return (printf("Error\nInvalid color\n"));
	if (textures.f->g > 255 || textures.f->g < 0)
		return (printf("Error\nInvalid color\n"));
	if (textures.f->b > 255 || textures.f->b < 0)
		return (printf("Error\nInvalid color\n"));
	return (0);
}*/

int	check_color(char *line, char **color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (color[i] == NULL)
			return (0);
		i++;
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			j++;
		if ((line[i] > '9' || line[i] < '0') && line[i] != ',')
			return (0);
		i++;
	}
	if (j != 2)
		return (0);
	return (1);
}
