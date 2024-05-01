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

bool	check_map_closed(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->tilemap.map && i < map->tilemap.size.y && map->tilemap.map[i])
	{
		j = 0;
		while (j < map->tilemap.size.x)
		{
			if (map->tilemap.map[i][j] != 0)
			{
				j++;
				continue ;
			}
			if (!check_map_tile(map, (t_v2){j, i}))
				return (pe(MAP_NOT_CLOSED), false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_map_tile(t_map *map, t_v2 pos)
{
	if (pos.x < 0 || pos.y < 0)
		return (false);
	if (pos.y >= map->tilemap.size.y || pos.x >= map->tilemap.size.x)
		return (false);
	if (!check_map_tile_value(&map->tilemap, (t_v2){pos.x, pos.y - 1}))
		return (false);
	if (!check_map_tile_value(&map->tilemap, (t_v2){pos.x, pos.y + 1}))
		return (false);
	if (!check_map_tile_value(&map->tilemap, (t_v2){pos.x + 1, pos.y}))
		return (false);
	if (!check_map_tile_value(&map->tilemap, (t_v2){pos.x - 1, pos.y}))
		return (false);
	return (true);
}

bool	check_map_tile_value(t_tilemap *tilemap, t_v2 pos)
{
	int	value;

	if (pos.y < 0 || pos.x < 0
		|| pos.y >= tilemap->size.y
		|| pos.x >= tilemap->size.x)
		return (false);
	value = tilemap->map[pos.y][pos.x];
	return (!(value == -1));
}
