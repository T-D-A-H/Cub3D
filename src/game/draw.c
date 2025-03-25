/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:03:36 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/25 16:10:30 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, int colour, t_cub *cubed)
{
	int	index;

	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;
	index = y * cubed->game->size_line + x * cubed->game->bpp / 8;
	cubed->game->data[index] = colour & 0xFF;
	cubed->game->data[index + 1] = ((colour >> 8) & 0xFF);
	cubed->game->data[index + 2] = ((colour >> 16) & 0xFF);
}


void draw_3dmap(t_cub *cubed, int drawStart, int drawEnd, int x, int side)
{
	// CAMBIAR FUNCIONAMIENTO PARA PINTAR CARAS CORRECTAS
	// CAMBIAR PARA IMPRIMIR TEXTURAS
	// PILLAR VALORES DE TECHO Y SUELO
	int color = PURPLE;
	int colorf = 0;
	int colorc = 0;
	colorf += cubed->f_color[0] * (256 * 256);
	colorf += cubed->f_color[1] * (256);
	colorf += cubed->f_color[2];
	colorc += cubed->c_color[0] * (256 * 256);
	colorc += cubed->c_color[1] * (256);
	colorc += cubed->c_color[2];
	for (int y = 0; y <= drawStart; y++)
  	{
  	    if (y >= 0 && y < HEIGHT)
  	        put_pixel(x, y, colorc, cubed);
  	}
	for (int y = drawStart; y <= drawEnd; y++)
  	{
		if (side == 1)
			color = 0x690067;
  	    if (y >= 0 && y < HEIGHT)
  	        put_pixel(x, y, color, cubed);
  	}
	for (int y = drawEnd ; y <= WIDTH; y++)
  	{			
  	        put_pixel(x, y, colorf, cubed);
  	}
}

