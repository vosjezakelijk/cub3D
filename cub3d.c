/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:48:43 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 13:50:38 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	valid_input(t_param *param, int argc, char **argv)
{
	int	len;

	if (argc < 2)
		print_error("Error", "Not enough arguments. You need a map.");
	len = ft_strlen(argv[1]);
	if ((argv[1][len - 4] != '.') && (argv[1][len - 3] != 'c')
		&& (argv[1][len - 2] != 'u') && (argv[1][len - 1] != 'b'))
		print_error("Error", "Wrong extention of your map.");
	if (argc == 3)
	{
		if ((argv[2][0] != '-') || (argv[2][1] != '-')
		|| (argv[2][2] != 's') || (argv[2][3] != 'a')
		|| (argv[2][4] != 'v') || (argv[2][5] != 'e')
		|| (argv[2][6] != '\0'))
			print_error("Error", "You can't make a screenshot.");
		param->act.screen = 1; //define if screenshot needed
	}
	if (argc > 3)
		print_error("Error", "Extra arguments, you don't need so many.");
}

static void	parse_params(char *line, t_param *param)
{
	if (line[0] == 'R' && (line[1] == ' ' || line[1] == '\t'))
		parse_res(line, param);
	else if (line[0] == 'N' && line[1] == 'O'
		&& (line[2] == ' ' || line[2] == '\t'))
		parse_no(line, param);
	else if (line[0] == 'S' && line[1] == 'O'
		&& (line[2] == ' ' || line[2] == '\t'))
		parse_so(line, param);
	else if (line[0] == 'W' && line[1] == 'E'
		&& (line[2] == ' ' || line[2] == '\t'))
		parse_we(line, param);
	else if (line[0] == 'E' && line[1] == 'A'
		&& (line[2] == ' ' || line[2] == '\t'))
		parse_ea(line, param);
	else if (line[0] == 'S' && (line[1] == ' ' || line[1] == '\t'))
		parse_s(line, param);
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		parse_f(line, param);
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		parse_c(line, param);
	else if (line[0] != '\0') //empty line is OK, anything else -- KO
		print_error("Error", "Problems with parameters.");
}

static void	parse_file(t_param *param, int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		parse_params(line, param);
		free(line);
		if (params_filled(param)) //check when all 8 params found
			break ;
	}
	parse_map(fd, param);
}

static void	validate_map(t_param *param)
{
	int	i;
	int	j;

	i = 0;
	while (param->map.map[i])
	{
		j = 0;
		while (param->map.map[i][j])
		{
			check_space(param, i, j);
			check_player(param, i, j);
			check_valid_symb(param, i, j, 0);
			check_border(param, i, j);
			check_spr(param, i, j); // just count
			j++;
		}
		i++;
	}
	if (param->act.pos.x == 0 && param->act.pos.y == 0) //not a serious error
		print_error("Error", "Kek! No player on the map.");
	check_sprite(param, i, j); // remember position
}

int	main(int argc, char **argv)
{
	t_param	param;
	int		fd;

	init_data(&param); //init params(colors, position, counts)
	valid_input(&param, argc, argv); //check number of arguments and extension
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error("Error", "Can't open this file.");
	parse_file(&param, fd); // first parse params + parse map
	validate_map(&param); //check valid symbols(player, sprites, prohib. symbols, open spaces)
	get_texture(&param); //put texture
	start_mlx(&param); //action
	return (0);
}
