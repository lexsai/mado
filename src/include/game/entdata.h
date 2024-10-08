#ifndef ENTDATA_H
#define ENTDATA_H

#define ENT_CONTEXT_WORD_MAX 8

struct game_s;

typedef enum {
  EV_ACT,
  EV_TRANSITION,
  EV_MAP_COLLIDE,
  EV_ENTITY_COLLIDE,
  EV_HIT,
  EV_NO_HEALTH
} event_type_t;

typedef struct {
  union {
    struct { int damage; } hit;
    struct { int name; } act;
    struct { int e; } col;
    struct { int state; } transition;
  };
  event_type_t type;
} event_t;

typedef void (*invoke_t)(struct game_s *gs, int e, event_t ev);

typedef enum {
  ENT_ANY,
  ENT_PLAYER,
  ENT_ENEMY,
  ENT_BULLET
} entname_t;

typedef struct {
  entname_t name;
  invoke_t  invoke;
  int       context[ENT_CONTEXT_WORD_MAX];
} entdata_t;

#endif
