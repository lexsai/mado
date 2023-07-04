#include "game.h"

void game_init(game_t *game)
{
  *game = (game_t) { 0 };
  
  sprite_t *new_sprite = sprite_alloc(game->sprites);
  new_sprite->pos = vec2_init(0.0, 0.0);
  new_sprite->uv = vec2_init(0, 5);
  new_sprite->show = true;
  new_sprite->stand = true;
  new_sprite->used = true;
  
  player_init(&game->player, new_sprite);
}

void game_update(game_t *game, const usercmd_t *usercmd)
{
  game->time += 0.015;
  
  player_move(&game->player, game->map, game->time, usercmd);
  player_shoot(&game->player, game->bullets, game->sprites, usercmd);

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (game->bullets[i].used) {
      bullet_update(&(game->bullets[i]));
    }
  }
}

void game_load_map(game_t *game, map_t *map)
{
  game->map = map;
}
