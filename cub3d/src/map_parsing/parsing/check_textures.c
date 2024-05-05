/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:57:52 by fahmadia          #+#    #+#             */
/*   Updated: 2024/05/05 15:36:49 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	open_current_file(t_window_frame *gui, char *current_texture_dir)
{
	int	fd;

	fd = open(current_texture_dir, O_RDONLY | EISDIR);
	if (fd == -1)
	{
		gui->config_file.error = INVALID_TEXTURE_DIR;
		print_err_msg("Invalid texture directory", ": ", current_texture_dir);
		return (false);
	}
	close(fd);
	return (true);
}

bool	open_all_files(t_window_frame gui)
{
	int		i;
	char	*textures_dirs[4];

	textures_dirs[0] = gui.config_file.no_info;
	textures_dirs[1] = gui.config_file.ea_info;
	textures_dirs[2] = gui.config_file.so_info;
	textures_dirs[3] = gui.config_file.we_info;
	i = 0;
	while (i < 4)
	{
		if (!open_current_file(&gui, textures_dirs[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	textures_dirs_are_valid(t_window_frame gui)
{
	if (!open_all_files(gui))
		return (false);
	return (true);
}

bool	current_extension_valid(t_window_frame *gui, char *current_texture_dir)
{
	size_t	length;
	char	*extension;

	length = ft_strlen(current_texture_dir);
	extension = ft_substr(current_texture_dir, length - 1 - 3, 4);
	if (ft_strncmp(".png", extension, 4) != 0)
	{
		gui->config_file.error = INVALID_TEXTURE_EXTENSION;
		print_err_msg("Invalid texture extension", ": ", current_texture_dir);
		return (false);
	}
	free(extension);
	return (true);
}

bool	textures_extension_valid(t_window_frame gui)
{
	int		i;
	char	*textures_dirs[4];

	textures_dirs[0] = gui.config_file.no_info;
	textures_dirs[1] = gui.config_file.ea_info;
	textures_dirs[2] = gui.config_file.so_info;
	textures_dirs[3] = gui.config_file.we_info;
	i = 0;
	while (i < 4)
	{
		if (!current_extension_valid(&gui, textures_dirs[i]))
			return (false);
		i++;
	}
	return (true);
}
