/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/17 16:05:50 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	on_keypress(struct mlx_key_data keydata, void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		error(cubed, NO_ERROR);
}

void	init_window(t_cub *cubed)
{
	cubed->mlx_ptr = mlx_init(WINDOW_W, WINDOW_H, WINDOW_NAME, true);
	if (!cubed->mlx_ptr)
		error(cubed, ERR_MLX_INIT);
	mlx_key_hook(cubed->mlx_ptr, on_keypress, cubed);
	mlx_loop(cubed->mlx_ptr);
}
