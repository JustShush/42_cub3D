/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:14:37 by dimarque          #+#    #+#             */
/*   Updated: 2024/05/02 16:52:01 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	map_init(t_map	*map)
{
	if (!calc_map_size(map))
		return (pe(MAP_NOT_FOUND), false);
	if (map->size.x < 3 || map->size.y < 8)
		return (pe(INVALID_MAP), false);
	map->file = malloc(sizeof(char *) * (map->size.y + 1));
	if (!map->file)
		return (pe(MALLOC_ERROR), false);
	ft_memset(map->file, 0, sizeof(char *) * (map->size.y + 1));
	if (!readmap(map))
		return (false);
	if (!parse_map_file(map))
		return (false);
	return (true);
}

// Because readmap was too big
static bool	readmap_line(t_map *map, int i, char *line)
{
	if (i <= (TILEMAP_FIRST_INDEX - 1))
		map->file[i] = ft_strtrim(line, " \n\t");
	else
		map->file[i] = ft_strtrim(line, "\n\t");
	free(line);
	if (!map->file[i])
		return (pe(MALLOC_ERROR), false);
	return (true);
}

bool	readmap(t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(map->filename, O_RDONLY);
	if (fd < 0)
		return (pe(MAP_NOT_FOUND), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (i < (TILEMAP_FIRST_INDEX + 1) && empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!readmap_line(map, i, line))
			return (false);
		i++;
		line = get_next_line(fd);
	}
	map->file[i] = NULL;
	close(fd);
	return (true);
}

/* Calculates the file height and width */
bool	calc_map_size(t_map *map)
{
	int		fd;
	char	*str;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		return (false);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (map->size.y < TILEMAP_FIRST_INDEX && empty_line(str))
		{
			free(str);
			str = NULL;
			continue ;
		}
		map->size.y++;
		if (ft_strlen(str) > (size_t) map->size.x)
			map->size.x = ft_strlen(str);
		free(str);
	}
	return (close(fd), true);
}

/* Calculates the tilemap height and width */
bool	calculate_tilemap_size(t_map *map)
{
	int		i;
	int		empty_line_c;

	i = TILEMAP_FIRST_INDEX;
	empty_line_c = 0;
	while (i < map->size.y && map->file[i])
	{
		if (empty_line(map->file[i]))
			empty_line_c++;
		else
		{
			if (empty_line_c > 0)
				return (pe(MAP_HAS_EMPTY_LINE), false);
		}
		map->tilemap.size.y++;
		if (ft_strlen(map->file[i]) > (size_t) map->tilemap.size.x)
			map->tilemap.size.x = ft_strlen(map->file[i]);
		i++;
	}
	if (map->tilemap.size.x > TILEMAP_MAX_WIDTH
		|| map->tilemap.size.y > TILEMAP_MAX_HEIGHT)
		return (pe(INVALID_TILEMAP_SIZE), false);
	return (true);
}
