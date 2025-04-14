/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_effects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:44:43 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/14 13:20:04 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	get_pixel_color(int x, int y, t_cub *cubed)
{
	char	*dst;
	int		bpp;

	if (!cubed || !cubed->game || !cubed->game->data)
		return (0);
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	bpp = cubed->game->bpp / 8;
	if (bpp <= 0)
		return (0);
	dst = cubed->game->data + (y * cubed->game->size_line + x * bpp);
	return (*(unsigned int *)dst);
}

void	vhs_util1(t_cub *cubed, t_vhs *vhs)
{
	vhs->x = 0;
	while (vhs->x < WIDTH)
	{
		vhs->color = get_pixel_color(vhs->x, vhs->y, cubed);
		vhs->r = (((vhs->color >> 16) & 0xFF) + vhs->noise) % 256;
		if (vhs->r < 0)
			vhs->r = 0;
		vhs->g = (((vhs->color >> 8) & 0xFF) + vhs->noise) % 256;
		if (vhs->g < 0)
			vhs->g = 0;
		vhs->b = ((vhs->color & 0xFF) + vhs->noise + 15) % 256;
		if (vhs->b < 0)
			vhs->b = 0;
		put_pixel(vhs->x, vhs->y, ((vhs->r << 16) | (vhs->g << 8) | vhs->b),
			cubed);
		vhs->x += (rand() % 3 + 1);
	}
}

void	vhs_util2(t_cub *cubed, t_vhs *vhs)
{
	vhs->x = 0;
	while (vhs->x < WIDTH)
	{
		vhs->color = get_pixel_color(vhs->x, vhs->y, cubed);
		vhs->b = (vhs->color & 0xFF) + 40;
		if (vhs->b > 255)
			vhs->b = 255;
		put_pixel(vhs->x, vhs->y, (vhs->color & 0xFFFF00) | vhs->b, cubed);
		vhs->x++;
	}
}

void	apply_vhs_effect(t_cub *cubed)
{
	t_vhs		vhs;
	static int	scan_line = 0;
	static int	frame_counter = 0;

	if (!cubed || !cubed->game)
		return ;
	frame_counter++;
	scan_line = (scan_line + 1) % HEIGHT;
	if (frame_counter % 2 != 0)
		return ;
	vhs.y = 0;
	while (vhs.y < HEIGHT)
	{
		if (rand() % 5 == 0)
		{
			vhs.noise = (rand() % 50) - 25;
			vhs_util1(cubed, &vhs);
		}
		if (vhs.y >= scan_line && vhs.y < scan_line + 5)
			vhs_util2(cubed, &vhs);
		vhs.y++;
	}
}
