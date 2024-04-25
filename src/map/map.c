/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:14:37 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/19 15:36:44 by dimarque         ###   ########.fr       */
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
