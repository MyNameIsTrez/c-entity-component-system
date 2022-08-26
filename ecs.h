// Entity IDs are necessary for associating components with one another
typedef int64_t	t_entity_id;

void	ecs_init(t_ecs *ecs);

// Declares what the sizes of components are.
// This function can be called multiple times.
void	ecs_size(t_component_id component_id, size_t component_size, t_ecs *ecs);

// This function creates an entity and initializes the entity's mask to 0
// Entity masks are necessary for knowing whether a component being 0 means that it has a value of 0, or that that entity doesn't have that component
t_entity_id	ecs_entity(void);

void    ecs_component(t_entity_id entity_id, t_c types, t_c values, t_ecs *ecs);

/*
// This can also be used for writing to components
// Example:
// t_position   *position;
// position = ecs_get_2(player_id, TAG_PLAYER, ecs);
void    *ecs_get_2(t_entity_id entity_id, t_component_id component_id, t_ecs *ecs);
*/

typedef s_query
{
	t_entity_id	*entity_matches;
    size_t		index;
}   t_query;

// t_query contains a pointer to the data and an index for ecs_iterate()
t_query ecs_query(t_component_id components_id, t_ecs *ecs);

// This function is a lot like ft_iterate(), but increments query.index for ecs_get()
t_status    ecs_iterate(t_query *query);

// This reads query.index
void    *ecs_get(t_query *query, t_component_id component_id);
