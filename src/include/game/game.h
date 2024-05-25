#ifndef GAME_H
#define GAME_H

#include <game/transform.h>
#include <game/sprite.h>
#include <game/rigidbody.h>
#include <game/actor.h>
#include <game/bullet.h>
#include <lib/input.h>
#include <lib/map.h>

#define ENTITY_MAX 512

typedef int entity_t;

typedef enum {
  C_transform = 1 << 0,
  C_sprite    = 1 << 1,
  C_rigidbody = 1 << 2,
  C_actor     = 1 << 3,
  C_bullet    = 1 << 4
} component_t;

typedef struct game_s {
  transform_t transform[ENTITY_MAX];
  sprite_t    sprite[ENTITY_MAX];
  rigidbody_t rigidbody[ENTITY_MAX];
  actor_t     actor[ENTITY_MAX];
  bullet_t    bullet[ENTITY_MAX];
  entdata_t   entdata[ENTITY_MAX];
  component_t entdict[ENTITY_MAX];
  int         num_entities;
  
  map_t       map;
  entity_t    player;
  
  vector      view_position;
  vector      view_rotation;
  
  float       time;
} game_t;

void game_init(game_t *gs);
void game_load_map(game_t *gs, map_t map);
void game_update(game_t *gs, const input_t in);

entity_t  entity_add(game_t *gs, entname_t name);
void      entity_kill(game_t *gs, entity_t e);
void      entity_bind(game_t *gs, entity_t e, invoke_t invoke);
void      entity_invoke(game_t *gs, entity_t e, event_t ev);
entname_t entity_get_name(game_t *gs, entity_t e);

#define entity_add_component(gs, e, component) \
{\
  (gs)->component[e] = create_##component();\
  (gs)->entdict[e] |= C_##component;\
}

#define entity_get_component(gs, e, component) (&(gs)->component[e])
#define entity_match(gs, e, mask) (((gs)->entdict[e] & (mask)) == (mask))

#endif
