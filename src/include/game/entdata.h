#ifndef ENTDATA_H
#define ENTDATA_H

struct game_s;

typedef enum {
  EV_ACT,
  EV_MAP_COLLIDE,
  EV_ENTITY_COLLIDE
} event_type_t;

typedef struct {
  union {
    struct { int name; } act;
    struct { int e; } entcol;
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
} entdata_t;

#endif