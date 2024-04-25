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

int	check_map_closed(t_map map, char **bmap)
{
	int		i;
	//int		j;
	char	**copy;
	(void)map;

	//j = 0;
	i = get_start_map(bmap);
	copy = copy_array(bmap);
	if (i + 1 < 0 || !bmap[i + 1] || first_str(bmap[i + 1], "1"))
	{
		free_array(copy);
		return (1);
	}
	//if (support_check_map(copy, i, j, map) == 1)
	//	return (1);
	free_array(copy);
	return (0);
}
