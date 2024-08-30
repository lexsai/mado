#ifndef npcmove_H
#define npcmove_H

#include <lib/math3d.h>

typedef int entity_t;

typedef enum {
  BH_STOP,
  BH_TRAVEL,
  BH_CHASE,
  BH_RETREAT,
  BH_ORBIT
} behave_t;

typedef struct {
  behave_t  behave;
  vector    target;
  float     speed;
  float     time;
} npcmove_t;

inline static npcmove_t create_npcmove()
{
  return (npcmove_t) {
    .behave = BH_STOP,
    .target = vec2(0.0, 0.0),
    .speed = 1.0,
    .time = 0.0
  };
}

inline static void npcmove_stop(npcmove_t *bm)
{
  bm->behave = BH_STOP;
}

inline static void npcmove_chase(npcmove_t *bm, float speed)
{
  bm->behave = BH_CHASE;
  bm->speed = speed;
}

inline static void npcmove_retreat(npcmove_t *bm, float speed)
{
  bm->behave = BH_RETREAT;
  bm->speed = speed;
}

inline static void npcmove_travel(npcmove_t *bm, vector target, float speed)
{
  bm->behave = BH_TRAVEL;
  bm->target = target;
  bm->speed = speed;
}

inline static void npcmove_orbit(npcmove_t *bm, vector target, float speed)
{
  bm->behave = BH_ORBIT;
  bm->time = 0.0;
  bm->target = target; 
  bm->speed = speed;
}

#endif