#ifndef ECS_FORWARD_DECLARATIONS_H
# define ECS_FORWARD_DECLARATIONS_H

#include <stdint.h>

typedef struct s_ecs	t_ecs;

// Entity IDs allow associating components with one another
typedef uint32_t	t_entity_id;

typedef struct s_query	t_query;

typedef struct s_c	t_c;
typedef struct s_g	t_g;

#endif
