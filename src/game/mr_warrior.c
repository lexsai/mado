#include <game/enemy.h>
#include <game/shoot.h>
#include <game/movement.h>
#include <game/game.h>
#include <stdio.h>

#define WARRIOR_CHASE_SPEED  1.5
#define WARRIOR_PIVOT_RADIUS 5.0
#define WARRIOR_PIVOT_TIME   2.5

static const animation_t mr_warrior_idle   = { .tx = 4, .ty = 6, .tw = 2, .th = 2, .framecount = 2, .frametime = 0.50 };
static const animation_t mr_warrior_attack = { .tx = 4, .ty = 4, .tw = 2, .th = 2, .framecount = 2, .frametime = 0.20 };

static shooter_t mr_warrior_shooter = {
  .tx = 3, .ty = 0,
  .tw = 1, .th = 1,
  .ttl = 1.0,
  .target = ENT_PLAYER,
  .damage = 20
};

static void mr_warrior_invoke(game_t *gs, entity_t e, event_t ev);
vector mr_warrior_movement(game_t *gs, entity_t e, float speed, float a2, float a3, float a4);

entity_t enemy_spawn_mr_warrior(game_t *gs)
{
  entity_t e = entity_add(gs, ENT_ENEMY);
  entity_add_component(gs, e, transform);
    transform_t *t = entity_get_component(gs, e, transform);
    t->scale = vec3(2.0, 2.0, 2.0);
    t->position = vec2(4, 4);
  entity_add_component(gs, e, sprite);
    sprite_t *s = entity_get_component(gs, e, sprite);
    sprite_repeat(s, &mr_warrior_idle);
  entity_add_component(gs, e, actor);
    actor_t *a = entity_get_component(gs, e, actor);
    actor_repeat(a, ACT0, 5.0, 0, 2.5);
    actor_repeat(a, ACT3, 5.0, 0, 10.0);
  entity_add_component(gs, e, rigidbody);
    rigidbody_t *rb = entity_get_component(gs, e, rigidbody);
    rb->radius = 0.8;
  entity_add_component(gs, e, health);
    health_t *h = entity_get_component(gs, e, health);
    h->hp = 100;
  entity_add_component(gs, e, botmove);
    botmove_t *m = entity_get_component(gs, e, botmove);
    m->a1 = WARRIOR_CHASE_SPEED;
    m->movement = movement_chase;
  entity_bind(gs, e, mr_warrior_invoke);
  return e;
}

void mr_warrior_invoke(game_t *gs, entity_t e, event_t ev)
{
  const transform_t *pt = entity_get_component(gs, gs->player, transform);
  
  transform_t *t = entity_get_component(gs, e, transform);
  sprite_t *s = entity_get_component(gs, e, sprite);
  actor_t *a = entity_get_component(gs, e, actor);
  botmove_t *m = entity_get_component(gs, e, botmove);
  
  vector forward = fdotv(3.0, normalize(vsubv(pt->position, t->position)));
  
  switch (ev.type) {
  case EV_ACT:
    switch (ev.act.name) {
    case ACT0:
      actor_repeat(a, ACT1, 0.0, 6, 0.3);
      break;
    case ACT1:
      sprite_play(s, &mr_warrior_attack);
      actor_do(a, ACT2, 0.15);
      break;
    case ACT2:
      shoot_shotgun(gs, &mr_warrior_shooter, t->position, forward, 5, M_PI / 3);
      break;
    case ACT3:
      m->a1 = WARRIOR_CHASE_SPEED;
      m->movement = movement_chase;
      actor_do(a, ACT4, 5.0);
      break;
    case ACT4:
      m->a1 = WARRIOR_PIVOT_RADIUS;
      m->a2 = WARRIOR_PIVOT_TIME;
      m->v1 = t->position;
      m->movement = movement_pivot;
      break;
    }
    break;
  case EV_HIT:
    bullet_t *b = entity_get_component(gs, ev.entcol.e, bullet);
    health_t *h = entity_get_component(gs, e, health);
    h->hp -= b->damage;
    break;
  case EV_NO_HEALTH:
    entity_kill(gs, e);
    break;
  }
}