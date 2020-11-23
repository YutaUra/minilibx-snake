/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:16:31 by yura              #+#    #+#             */
/*   Updated: 2020/11/23 18:47:37 by yura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int main()
{
	t_game game;

	window_init(&game);
	snake_apple_init(&game);
	put_init_game(&game);
	mlx_key_hook(game.win, &handle_key, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
