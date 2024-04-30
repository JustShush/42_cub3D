/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	get_start_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	while (i > 0 && empty_line(map[i]) == 1)
		i--;
	while (i > 0 && empty_line(map[i]) == 0)
		i--;
	return (i);
}

enum e_type_identifier	line_matches_identifier(char *line)
{
	if (ft_strncmp(line, NORTH_TEXTURE_IDENTIFIER, 3) == 0)
		return (NORTH_TEXTURE);
	else if (ft_strncmp(line, SOUTH_TEXTURE_IDENTIFIER, 3) == 0)
		return (SOUTH_TEXTURE);
	else if (ft_strncmp(line, WEST_TEXTURE_IDENTIFIER, 3) == 0)
		return (WEST_TEXTURE);
	else if (ft_strncmp(line, EAST_TEXTURE_IDENTIFIER, 3) == 0)
		return (EAST_TEXTURE);
	else if (ft_strncmp(line, FLOOR_COLOR_IDENTIFIER, 2) == 0)
		return (FLOOR_COLOR);
	else if (ft_strncmp(line, CEILING_COLOR_IDENTIFIER, 2) == 0)
		return (CEILING_COLOR);
	return (INVALID);
}

bool	parse_identifier(t_map *map, char *line,
		enum e_type_identifier identifier)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[1] || split[2])
		return (free_array(split), false);
	if (identifier == NORTH_TEXTURE || identifier == SOUTH_TEXTURE
		|| identifier == WEST_TEXTURE || identifier == EAST_TEXTURE)
	{
		if (!parse_wall_texture(map, split[1], identifier))
			return (free_array(split), false);
	}
	else if (identifier == FLOOR_COLOR || identifier == CEILING_COLOR)
	{
		if (identifier == FLOOR_COLOR && map->sprites.floor != -1)
			return (pe_msg(DUPLICATE_IDENTIFIER, line), free_array(split), false);
		if (!parse_color(map, split[1], identifier))
			return (free_array(split), false);
	}
	return (free_array(split), true);
}

unsigned int	create_color(int r, int g, int b)
{
	r = r & 0xFF;
	g = g & 0xFF;
	b = b & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

bool	ends_with(char *s1, char *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (j >= 0)
	{
		if (s1[i] != s2[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}
