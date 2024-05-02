/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map(t_map *map, void *mlx)
{
	int	i;

	free_array(map->file);
	map->file = NULL;
	unload_sprites(mlx, &map->sprites);
	if (map->tilemap.map && map->tilemap.size.x > 0)
	{
		i = 0;
		while (map->tilemap.map && i < map->tilemap.size.y
			&& map->tilemap.map[i] != NULL)
		{
			free(map->tilemap.map[i]);
			i++;
		}
		free(map->tilemap.map);
		map->tilemap.map = NULL;
	}
}
