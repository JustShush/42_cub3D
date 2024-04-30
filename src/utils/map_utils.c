/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/04/25 13:53:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	get_start_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	while (i > 0 && empty_line(map[i]) == 1)
		i--;
	while (i > 0 && empty_line(map[i]) == 0)
		i--;
	return (i);
}

int	get_y(char *file)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"));
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (!first_str(str, "1"))
			i++;
		free(str);
	}
	close(fd);
	return (i);
}

int	first_char(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == c)
		return (1);
	return (0);
}
