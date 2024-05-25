#include <game/enemy.h>
#include <game/shoot.h>
#include <game/game.h>
#include <stdio.h>

static const animation_t dummy_idle = { .tx = 4, .ty = 6, .tw = 2, .th = 2, .framecount = 2, .frametime = 0.50 };

static void dummy_invoke(game_t *gs, entity_t e, event_t ev);

entity_t enemy_spawn_dummy(game_t *gs)
{
  entity_t e = entity_add(gs);
  entity_add_component(gs, e, transform);
    transform_t *t = entity_get_component(gs, e, transform);
    t->scale = vec3(2.0, 2.0, 2.0);
    t->position = vec2(6, 4);
  entity_add_component(gs, e, sprite);
    sprite_t *s = entity_get_component(gs, e, sprite);
    sprite_repeat(s, &dummy_idle);
  entity_add_component(gs, e, collider);
    collider_t *c = entity_get_component(gs, e, collider);
    c->radius = 0.8;
    c->type = TARGET_ENEMY;
  entity_bind(gs, e, dummy_invoke);
  return e;
}

static void dummy_invoke(game_t *gs, entity_t e, event_t ev) {

}