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

void	assign_color(t_map map, char dir, char **color)
{
	if (dir == 'C')
	{
		map.textures.c = (t_RGB *)malloc(sizeof(t_RGB));
		map.textures.c->r = ft_atoi(color[0]);
		map.textures.c->g = ft_atoi(color[1]);
		map.textures.c->b = ft_atoi(color[2]);
	}
	else if (dir == 'F')
	{
		map.textures.f = (t_RGB *)malloc(sizeof(t_RGB));
		map.textures.f->r = ft_atoi(color[0]);
		map.textures.f->g = ft_atoi(color[1]);
		map.textures.f->b = ft_atoi(color[2]);
	}
}

void	save_color(t_map map, char dir, char *line, int j)
{
	char	*path;
	char	**color;

	path = ft_chrtrim(&line[j], ' ');
	color = ft_split(path, ',');
	map.c_texture++;
	if (check_color(path, color) == 0)
	{
		make_null(map, dir);
		free(path);
		free_array(color);
		return ;
	}
	assign_color(map, dir, color);
	free(path);
	free_array(color);
}

void	save_img(t_map map, char *dir, char *line, int j)
{
	char	*path;
	int		fd;

	map.c_texture++;
	path = ft_chrtrim(&line[j], ' ');
	fd = open(path, O_RDONLY);
	if (fd == -1 || check_suffix(path, ".xpm"))
	{
		if (check_suffix(path, ".xpm"))
			close(fd);
		free(path);
		return ;
	}
	close(fd);
	if (dir[0] == 'N' && dir[1] == 'O' && map->textures->so == NULL)
		map->textures->so = init_texture(map, path);
	else if (dir[0] == 'S' && dir[1] == 'O' && map->textures->no == NULL)
		map->textures->no = init_texture(map, path);
	else if (dir[0] == 'W' && dir[1] == 'E' && map->textures->ea == NULL)
		map->textures->ea = init_texture(map, path);
	else if (dir[0] == 'E' && dir[1] == 'A' && map->textures->we == NULL)
		map->textures->we = init_texture(map, path);
	free(path);
}

void	save_textures(t_map map, int i, int j)
{
	if (map.file[i][j] == 'N' && map.file[i][j + 1] == 'O'
		&& map.file[i][j + 2] == ' ')
		save_img(map, "NO", map.file[i], j + 2);
	else if (map.file[i][j] == 'S' && map.file[i][j + 1] == 'O'
		&& map.file[i][j + 2] == ' ')
		save_img(map, "SO", map.file[i], j + 2);
	else if (map.file[i][j] == 'W' && map.file[i][j + 1] == 'E'
		&& map.file[i][j + 2] == ' ')
		save_img(map, "WE", map.file[i], j + 2);
	else if (map.file[i][j] == 'E' && map.file[i][j + 1] == 'A'
		&& map.file[i][j + 2] == ' ')
		save_img(map, "EA", map.file[i], j + 2);
	else if (map.file[i][j] == 'C' && map.file[i][j + 1] == ' ')
		save_color(map, 'C', map.file[i], j + 1);
	else if (map.file[i][j] == 'F' && map.file[i][j + 1] == ' ')
		save_color(map, 'F', map.file[i], j + 1);
	else if (empty_line(map.file[i]) == 0)
		// exit free "Error Invalid line in file"
}

int	get_textures(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.file[i])
	{
		j = 0;
		if (first_char(map.file[i], '1') == 1)
			break ;
		while (map.file[i][j])
		{
			while (map.file[i][j] == ' ')
				j++;
			save_textures(map, i, j);
			break ;
		}
		i++;
	}
	return (0);
}

int	check_textures(t_map map)
{
	if (map.textures->no == NULL)
		return (printf("Error\nNO texture not found\n"));
	if (map.textures->so == NULL)
		return (printf("Error\nSO texture not found\n"));
	if (map.textures.we == NULL)
		return (printf("Error\nWE texture not found\n"));
	if (map.textures.ea == NULL)
		return (printf("Error\nEA texture not found\n"));
	if (map.textures.c == NULL)
		return (printf("Error\nC color not found\n"));
	if (map.textures.f == NULL)
		return (printf("Error\nF color not found\n"));
	return (0);
}
