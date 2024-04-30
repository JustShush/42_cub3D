/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:14:37 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/30 20:47:13 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// TODO: change return type to bool
int	readmap(t_map *map)
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
		if (empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (i <= 5)// first 6 valid lines are textures
			map->file[i] = ft_strtrim(line, " \n\t");
		else
			map->file[i] = ft_strtrim(line, "\n\t");/* do not remove spaces */
		free(line);
		if (!map->file[i])
			return (pe(MALLOC_ERROR), 1);
		printf("map[%d]:|%s|\n", i, map->file[i]);
		i++;
		line = get_next_line(fd);
	}
	map->file[i] = NULL;
	close(fd);
	return (0);
}

int	numberoflines(char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}


bool	map_init(t_map	*map)
{
	if (!calc_map_size(map))
		return (pe(MAP_NOT_FOUND), false);
	printf("map size: %d %d\n", map->size.x, map->size.y);
	if (map->size.x < 3 || map->size.y < 8)
		return (pe(INVALID_MAP), false);
	map->file = malloc(sizeof(char *) * (map->size.y + 1));
	if (!map->file)
		return (pe(MALLOC_ERROR), false);
	ft_memset(map->file, 0, sizeof(char *) * (map->size.y + 1));
	if (readmap(map))
		return (false);
	if (!parse_map_file(map))
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
		//printf("parse_map_file_textures:%s|\n", map->file[i]);
		identifier = line_matches_identifier(map->file[i]);
		if (identifier == INVALID)
			return (pe(INVALID_IDENTIFIER), false);
		//printf("identifier:%d\n", identifier);
		if (!parse_identifier(map, map->file[i], identifier))
			return (false);
		i++;
	}
	return (true);
}

bool	handle_tilemap_char(t_map *map, int i, int j)
{
	//printf("handle_tilemap_char:%c|\n", map->file[i][j]);
	if (map->file[i][j] == ' ')
		map->tilemap.map[i - TILEMAP_FIRST_INDEX][j] = -1;
	else if (char_in_set(map->file[i][j], PLAYER_DIRS))
	{
		printf("player_dir:%c\n", map->file[i][j]);
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
	return (true);
}

bool	parse_map_file(t_map *map)
{
	int	i;

	map->sprites.ceiling = -1;
	map->sprites.floor = -1;
	if (!parse_map_file_textures(map))
		return (false);
	if (!calculate_tilemap_size(map))
		return (false);
	map->tilemap.map = malloc(sizeof(int *) * map->tilemap.size.y + 1);
	if (!map->tilemap.map)
		return (pe(MALLOC_ERROR), false);
	i = 0;
	while (i < map->tilemap.size.y)
	{
		map->tilemap.map[i] = malloc(sizeof(int) * map->tilemap.size.x + 1);
		if (!map->tilemap.map[i])
			return (pe(MALLOC_ERROR), false);
		ft_memset(map->tilemap.map[i], -1, sizeof(int) * map->tilemap.size.x + 1);
		i++;
	}
	if (!parse_map_file_tilemap(map))
		return (false);
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
		if (empty_line(str))
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

	i = TILEMAP_FIRST_INDEX;
	while (i < map->size.y)
	{
		if (empty_line(map->file[i]))
			return (pe(MAP_HAS_EMPTY_LINE), false);
		map->tilemap.size.y++;
		if (ft_strlen(map->file[i]) > (size_t) map->tilemap.size.x)
			map->tilemap.size.x = ft_strlen(map->file[i]);
		i++;
	}
	printf("tilemap size: %d %d\n", map->tilemap.size.x, map->tilemap.size.y);
	return (true);
}
