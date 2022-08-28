#ifndef ECS_H
# define ECS_H

# include "libft.h"
# include "src/ecs_forward_declarations.h"

t_ecs   *ecs_init(size_t t_c_size, size_t t_g_size);

// Declares what the sizes of components and the size of t_c are
void	ecs_size(t_c *sizes, t_ecs *ecs);

// Creates an entity
t_entity_id	ecs_entity(t_ecs *ecs);

void	ecs_component(t_entity_id entity_id, t_c *added_component, void *value, t_ecs *ecs);

void	ecs_tag(t_entity_id entity_id, t_g *added_tags, t_ecs *ecs);

t_query	*ecs_query(t_c *components, t_g *tags, t_ecs *ecs);

// Increments query.entity_index for ecs_get()
t_iterator_status	ecs_iterate(t_query *query);

// Returns a pointer to data + query.entity_index * block_size + component offset
void	*ecs_get(t_c *component, t_query *query);

/*
// This can't be used for writing to components since the data is duplicated
// Example:
// int *x = ecs_get_2(player_id, (t_c *)&{.x=1}, ecs);
void	*ecs_get_2(t_entity_id entity_id, t_c *component, t_ecs *ecs);

void	ecs_remove(t_entity_id entity_id, t_c *component, t_ecs *ecs);

void	ecs_destroy(t_entity_id entity_id, t_ecs *ecs);
*/

#endif
