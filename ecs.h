#ifndef ECS_H
# define ECS_H

# include "ecs_forward_declarations.h"

void	ecs_init(t_ecs *ecs);

// Declares what the sizes of components are
// This function can be called multiple times
void	ecs_size(t_c *sizes, t_ecs *ecs);

// Creates an entity
t_entity_id	ecs_entity(void);

void	ecs_component(t_entity_id entity_id, t_c *added_component, void *value, t_ecs *ecs);

t_query	ecs_query(t_c *queried_components, t_ecs *ecs);

// Increments query.entity_index for ecs_get()
t_status	ecs_iterate(t_query *query);

// Returns a pointer to data + query.entity_index * block_size + component offset
void	*ecs_get(t_c *component, t_query *query);

/*
// This can't be used for writing to components since the data is duplicated
// Example:
// int *x = ecs_get_2(player_id, (t_c *)&{.x=1}, ecs);
void	*ecs_get_2(t_entity_id entity_id, t_c *component, t_ecs *ecs);
*/

#endif
