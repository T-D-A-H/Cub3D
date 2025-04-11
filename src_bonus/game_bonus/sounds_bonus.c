/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:04:02 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/11 17:18:42 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	*play_music(void *arg)
{
	t_cub				*cub;
	SDL_AudioDeviceID	dev;

	cub = (t_cub *)arg;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return (printf(ERR_SDL_INIT), NULL);
	if (!SDL_LoadWAV("./assets/level1.wav", &cub->sounds->wav_spec,
			&cub->sounds->buffer, &cub->sounds->wav_length))
		return (printf(ERR_SDL_OPEN_WAV), NULL);
	dev = SDL_OpenAudioDevice(NULL, 0, &cub->sounds->wav_spec, NULL, 0);
	if (dev == 0)
	{
		printf(ERR_SDL_OPEN);
		return (SDL_FreeWAV(cub->sounds->buffer), SDL_Quit(), NULL);
	}
	SDL_PauseAudioDevice(dev, 0);
	while (1)
	{
		if (SDL_GetQueuedAudioSize(dev) == 0)
			SDL_QueueAudio(dev, cub->sounds->buffer,
				cub->sounds->wav_length);
	}
	return (SDL_FreeWAV(cub->sounds->buffer), SDL_CloseAudioDevice(dev), NULL);
}

int	init_sounds(t_cub *cubed)
{
	if (pthread_create(&cubed->sounds->music_thread, NULL,
			play_music, (void *)cubed) == -1)
	{
		printf("Error: Failed to create Music Thread\n");
		return (1);
	}
	if (pthread_detach(cubed->sounds->music_thread) == -1)
	{
		printf("Error: Failed to detach Music Thread\n");
		return (1);
	}
	return (0);
}
