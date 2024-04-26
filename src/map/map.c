/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:14:37 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/26 19:34:07 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	readmap(char **map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nMap not found\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		map[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
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

int	tilemap(t_map map, char *map_path)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
	map.y = get_y(map_path);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"));
	map.map = malloc(sizeof(char *) * (map.y + 1));
	while (i < map.y)
	{
		buf = get_next_line(fd);
		if (!first_str(buf, "1"))
			map.map[i++] = ft_strdup(buf);
		free(buf);
	}
	map.map[i] = 0;
	close(fd);
	return (0);
}

char	**map_init(char *file)
{
	char	**map;

	map = malloc(sizeof(char *) * (numberoflines(file) + 1));
	if (!map)
		return (NULL);
	if (readmap(map, file))
	{
		free(map);
		return (NULL);
	}
	return (map);
}
