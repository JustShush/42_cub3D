/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		return (pe(INVALID_IDENTIFIER), free_array(split), false);
	if (identifier == NORTH_TEXTURE || identifier == SOUTH_TEXTURE
		|| identifier == WEST_TEXTURE || identifier == EAST_TEXTURE)
	{
		if (!parse_wall_texture(map, split[1], identifier))
			return (free_array(split), false);
	}
	else if (identifier == FLOOR_COLOR || identifier == CEILING_COLOR)
	{
		if (identifier == FLOOR_COLOR && map->sprites.floor != -1)
			return (pe(DUPLICATE_IDENTIFIER), free_array(split), false);
		if (!parse_color(map, split[1], identifier))
			return (free_array(split), false);
	}
	return (free_array(split), true);
}

bool	handle_tilemap_char(t_map *map, int i, int j)
{
	if (map->file[i][j] == ' ')
		map->tilemap.map[i - TILEMAP_FIRST_INDEX][j] = -1;
	else if (char_in_set(map->file[i][j], PLAYER_DIRS))
	{
		if (char_in_set(map->player_dir, PLAYER_DIRS))
			return (pe(MULTIPLE_PLAYERS), false);
		map->tilemap.map[i - TILEMAP_FIRST_INDEX][j] = 0;
		map->player_dir = map->file[i][j];
		map->player_pos = (t_v2){j, i - TILEMAP_FIRST_INDEX};
	}
	else
		map->tilemap.map[i - TILEMAP_FIRST_INDEX][j] = map->file[i][j] - '0';
	return (true);
}

unsigned int	create_color(int r, int g, int b)
{
	r = r & 0xFF;
	g = g & 0xFF;
	b = b & 0xFF;
	return ((r << 16) | (g << 8) | b);
}
