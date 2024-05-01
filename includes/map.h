/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:17:02 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 20:16:46 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <vecs.h>
# include <img.h>

# define MAP_EXT ".cub"

# define MAP_NOT_FOUND "Error: Map not found\n"
# define WALL_TEXTURE_NOT_FOUND "Error: Wall texture not found\n"
# define INVALID_COLOR "Error: Invalid color\n"
# define INVALID_IDENTIFIER "Error: Invalid identifier\n"
# define MAP_HAS_EMPTY_LINE "Error: Map has empty line\n"
# define MULTIPLE_PLAYERS "Error: Multiple players found\n"
# define INVALID_TILEMAP_CHAR "Error: Invalid tilemap character\n"
# define INVALID_MAP_EXT "Error: Invalid map extension\n"
# define INVALID_MAP "Error: Invalid map\n"
# define DUPLICATE_IDENTIFIER "Duplicate identifier\n"
# define PLAYER_NOT_FOUND "Error: Player not found\n"
# define MAP_NOT_CLOSED "Error: Map not closed\n"
# define INVALID_TILEMAP_SIZE "Error: Invalid tilemap size\n"

# define NORTH_TEXTURE_IDENTIFIER "NO "
# define SOUTH_TEXTURE_IDENTIFIER "SO "
# define WEST_TEXTURE_IDENTIFIER "WE "
# define EAST_TEXTURE_IDENTIFIER "EA "
# define FLOOR_COLOR_IDENTIFIER "F "
# define CEILING_COLOR_IDENTIFIER "C "

# define TILEMAP_FIRST_INDEX 6
# define PLAYER_DIRS "NSWE"
# define TILEMAP_VALID_CHARS " 01NSWE"
# define TILEMAP_MAX_WIDTH 60
# define TILEMAP_MAX_HEIGHT 40

enum e_type_identifier
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR,
	INVALID,
	TYPE_IDENTIFIERS_NUM
};

typedef struct t_tilemap
{
	int		**map;
	t_v2	size;
}	t_tilemap;

typedef struct t_map
{
	char		**file;
	char		*filename;
	t_v2		size;
	t_tilemap	tilemap;
	t_sprites	sprites;
	char		player_dir;
	t_v2		player_pos;
}	t_map;

// Map
bool					map_init(t_map	*map);
bool					readmap(t_map *map);
bool					calc_map_size(t_map *map);
bool					calculate_tilemap_size(t_map *map);

// Map Parser
bool					parse_map_file(t_map *map);
bool					parse_map_file_textures(t_map *map);
bool					parse_map_file_tilemap(t_map *map);
bool					parse_wall_texture(t_map *map, char *filename,
							enum e_type_identifier identifier);
bool					parse_color(t_map *map, char *color,
							enum e_type_identifier identifier);

// Map Identifiers
enum e_type_identifier	line_matches_identifier(char *line);
bool					parse_identifier(t_map *map, char *line,
							enum e_type_identifier identifier);
bool					handle_tilemap_char(t_map *map, int i, int j);
unsigned int			create_color(int r, int g, int b);

// Map Check
bool					check_map_closed(t_map *map);
bool					check_map_tile(t_map *map, t_v2 pos);
bool					check_map_tile_value(t_tilemap *tilemap, t_v2 pos);

#endif