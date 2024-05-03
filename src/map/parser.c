/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:58:19 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:29 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	parse_map_file(t_map *map)
{
	int	i;

	map->sprites.ceiling = -1;
	map->sprites.floor = -1;
	if (!parse_map_file_textures(map))
		return (false);
	if (!calculate_tilemap_size(map))
		return (false);
	map->tilemap.map = malloc(sizeof(int *) * (map->tilemap.size.y + 1));
	if (!map->tilemap.map)
		return (pe(MALLOC_ERROR), false);
	i = 0;
	while (i < map->tilemap.size.y)
	{
		map->tilemap.map[i] = malloc(sizeof(int) * map->tilemap.size.x);
		if (!map->tilemap.map[i])
			return (pe(MALLOC_ERROR), false);
		ft_memset(map->tilemap.map[i], -1, sizeof(int) * map->tilemap.size.x);
		i++;
	}
	if (!parse_map_file_tilemap(map))
		return (false);
	if (!check_map_closed(map))
		return (false);
	return (true);
}

bool	parse_map_file_textures(t_map *map)
{
	enum e_type_identifier	identifier;
	int						i;

	i = 0;
	while (i < TILEMAP_FIRST_INDEX && i < map->size.y)
	{
		identifier = line_matches_identifier(map->file[i]);
		if (identifier == INVALID)
			return (pe(INVALID_IDENTIFIER), false);
		if (!parse_identifier(map, map->file[i], identifier))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_map_file_tilemap(t_map *map)
{
	int		i;
	int		j;

	i = TILEMAP_FIRST_INDEX;
	while (map->file[i])
	{
		j = 0;
		while (j < map->tilemap.size.x && map->file[i][j])
		{
			if (!char_in_set(map->file[i][j], TILEMAP_VALID_CHARS))
				return (pe(INVALID_TILEMAP_CHAR), false);
			if (!handle_tilemap_char(map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	if (!char_in_set(map->player_dir, PLAYER_DIRS))
		return (pe(PLAYER_NOT_FOUND), false);
	return (true);
}

bool	parse_wall_texture(t_map *map, char *filename,
		enum e_type_identifier identifier)
{
	int			fd;
	t_sprite	*sprite;

	if (!ends_with(filename, IMG_FORMAT_EXT))
		return (pe(INVALID_SPRITE_EXT), false);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (pe(WALL_TEXTURE_NOT_FOUND), false);
	close(fd);
	if (identifier == NORTH_TEXTURE)
		sprite = &map->sprites.north;
	else if (identifier == SOUTH_TEXTURE)
		sprite = &map->sprites.south;
	else if (identifier == WEST_TEXTURE)
		sprite = &map->sprites.west;
	else if (identifier == EAST_TEXTURE)
		sprite = &map->sprites.east;
	else
		sprite = NULL;
	if (sprite->filename)
		return (pe(DUPLICATE_IDENTIFIER), false);
	sprite->filename = ft_strdup(filename);
	return (true);
}

bool	parse_color(t_map *map, char *color, enum e_type_identifier identifier)
{
	char	**colors;
	int		r;
	int		g;
	int		b;
	int		i;

	colors = ft_split(color, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (free_array(colors), pe(INVALID_COLOR), false);
	i = 0;
	while (colors[i])
	{
		if (!only_digits(colors[i]))
			return (free_array(colors), pe(INVALID_COLOR), false);
		i++;
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	free_array(colors);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (pe(INVALID_COLOR), false);
	if (identifier == FLOOR_COLOR)
		return (map->sprites.floor = create_color(r, g, b), true);
	return (map->sprites.ceiling = create_color(r, g, b), true);
}
