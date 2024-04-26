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

void	assign_color(t_amp map, char dir, char **color)
{
	if (dir == 'C')
	{
		map->textures->c = (t_RGB *)malloc(sizeof(t_RGB));
		map->textures->c->r = ft_atoi(color[0]);
		map->textures->c->g = ft_atoi(color[1]);
		map->textures->c->b = ft_atoi(color[2]);
	}
	else if (dir == 'F')
	{
		map->textures->f = (t_RGB *)malloc(sizeof(t_RGB));
		map->textures->f->r = ft_atoi(color[0]);
		map->textures->f->g = ft_atoi(color[1]);
		map->textures->f->b = ft_atoi(color[2]);
	}
}

void	save_color(t_map map, char dir, char *line, int j)
{
	char	*path;
	char	**color;

	path = ft_chrtrim(&line[j], ' ');
	color = ft_split(path, ',');
	map->c_texture++;
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

void	save_textures(t_map map, int i, int j)
{
	if (map->file[i][j] == 'N' && map->file[i][j + 1] == 'O'
		&& map->file[i][j + 2] == ' ')
		save_img(map, "NO", map->file[i], j + 2);
	else if (map->file[i][j] == 'S' && map->file[i][j + 1] == 'O'
		&& map->file[i][j + 2] == ' ')
		save_img(map, "SO", map->file[i], j + 2);
	else if (map->file[i][j] == 'W' && map->file[i][j + 1] == 'E'
		&& map->file[i][j + 2] == ' ')
		save_img(map, "WE", map->file[i], j + 2);
	else if (map->file[i][j] == 'E' && map->file[i][j + 1] == 'A'
		&& map->file[i][j + 2] == ' ')
		save_img(map, "EA", map->file[i], j + 2);
	else if (map->file[i][j] == 'C' && map->file[i][j + 1] == ' ')
		save_color(map, 'C', map->file[i], j + 1);
	else if (map->file[i][j] == 'F' && map->file[i][j + 1] == ' ')
		save_color(map, 'F', map->file[i], j + 1);
	else if (line_empty(map->file[i]) == 0)
		exit_free_check(map, "Error\nInvalid line in file");
}

int	get_textures(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map->file[i])
	{
		j = 0;
		if (first_char(map->file[i], '1') == 1)
			break ;
		while (map->file[i][j])
		{
			while (map->file[i][j] == ' ')
				j++;
			save_textures(map, i, j);
			break ;
		}
		i++;
	}
	return (0);
}
