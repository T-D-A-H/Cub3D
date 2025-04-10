/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:04:02 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/10 15:30:51 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	*play_music(void *arg)
{
	t_cub *cubed;
	
	cubed = (t_cub *)arg;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	if (!SDL_LoadWAV("./assets/level1.wav", &cubed->sounds->wav_spec,
					&cubed->sounds->wav_buffer, &cubed->sounds->wav_length))
	{
		printf("Failed to load WAV: %s\n", SDL_GetError());
		return (NULL);
	}
	SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0,
			&cubed->sounds->wav_spec, NULL, 0);
	if (dev == 0)
	{
		printf("Failed to open audio device: %s\n", SDL_GetError());
		SDL_FreeWAV(cubed->sounds->wav_buffer);
		SDL_Quit();
		return (NULL);
	}
 	SDL_PauseAudioDevice(dev, 0);
	while (1)
	{

		if (SDL_GetQueuedAudioSize(dev) == 0)
		{
			SDL_QueueAudio(dev, cubed->sounds->wav_buffer, cubed->sounds->wav_length);
		}
		
	}
	SDL_FreeWAV(cubed->sounds->wav_buffer);
	SDL_CloseAudioDevice(dev);
	SDL_CloseAudio();
	SDL_Quit();
	return (NULL);
}



int init_sounds(t_cub *cubed)
{
	if (pthread_create(&cubed->sounds->music_thread, NULL, play_music, (void *)cubed) == -1)
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