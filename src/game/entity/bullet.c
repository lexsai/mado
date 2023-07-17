#include "bullet.h"

void xact_bullet_die(entity_t entity, edict_t *edict);
void xhit_map_bullet(entity_t entity, edict_t *edict);
void xhit_bullet(entity_t entity, edict_t *edict, entity_t hit);

void bullet_shoot(edict_t *edict, vec2_t pos, float angle, float live_time, c_tag_t target)
{
  entity_t entity = edict_spawn(edict);
  edict->field[entity] |= COMPONENT_TRANSFORM;
  edict->field[entity] |= COMPONENT_MOTION;
  edict->field[entity] |= COMPONENT_SPRITE;
  edict->field[entity] |= COMPONENT_BULLET;
  edict->field[entity] |= COMPONENT_BOX;
  edict->field[entity] |= COMPONENT_ACTOR;
  
  edict->transform[entity].position = pos;
  edict->transform[entity].rotation = angle;
  
  edict->sprite[entity].uv = vec2_init(0, 7);
  edict->sprite[entity].rotation = angle - M_PI/2.0;
  edict->sprite[entity].orient = false;
  edict->sprite[entity].stand = false;
  
  edict->motion[entity].velocity = vec2_init(cos(angle) * 10, sin(angle) * 10);
  edict->box[entity].min = vec2_init(-0.2, -0.2);
  edict->box[entity].max = vec2_init(+0.2, +0.2);
  edict->box[entity].xhit = xhit_bullet;
  edict->box[entity].xhit_map = xhit_map_bullet;
  
  edict->actor[entity].act[0].xaction = xact_bullet_die;
  edict->actor[entity].act[0].time = live_time;
  edict->actor[entity].act[0].cooldown = live_time;
  edict->actor[entity].act[0].active = true;
  edict->actor[entity].num_act = 1;
  
  edict->bullet[entity].target = target;
}

void xhit_bullet(entity_t entity, edict_t *edict, entity_t hit)
{
  if (
    edict->field[hit] & COMPONENT_TAG &&
    edict->tag[hit] & edict->bullet[entity].target
  ) {
    printf("e(%i) hit player\n", entity);
    edict_kill(edict, entity);
  }
}

void xhit_map_bullet(entity_t entity, edict_t *edict)
{
  edict_kill(edict, entity);
}

void xact_bullet_die(entity_t entity, edict_t *edict)
{
  edict_kill(edict, entity);
}