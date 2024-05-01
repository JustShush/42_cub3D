/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:58:19 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 17:24:51 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	if (sprite->filename)
		return (pe(DUPLICATE_IDENTIFIER), false);
	sprite->filename = ft_strdup(filename);
	return (true);
}

/* TODO: handle mem leaks for split */
bool	parse_color(t_map *map, char *color, enum e_type_identifier identifier)
{
	char	**colors;
	int		r;
	int		g;
	int		b;
	int		i;

	colors = ft_split(color, ',');
	if (!colors || !colors[1] || !colors[2] || colors[3])
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
