// Entity IDs are necessary for associating components with one another
typedef t_u32   t_entity_id;

// The reason why all components need to be declared at the start is so entities can have their components all bunched up so no dereferencing has to occur
void	ecs_init(size_t component_count, size_t *component_sizes, t_ecs *ecs);

/*
// This tells *ecs what the stride of each component is
void    ecs_declare(t_component_id component_id, size_t component_size, t_ecs *ecs);
*/

// This function creates an entity and initializes the entity's mask to 0
// Entity masks are necessary for knowing whether a component being 0 means that it has a value of 0, or that that entity doesn't have that component
t_entity_id	ecs_create(void);

// Under the hood this function will add both data and its entity_id right next to one another
// Note that data isn't referring to the static data struct that most of my programs store their global state in!
void    ecs_add(t_entity_id entity_id, t_component_id component_id, void *data, t_ecs *ecs);

/*
// This can also be used for writing to components
// Example:
// t_position   *position;
// position = ecs_get_2(player_id, COMPONENT_PLAYER, ecs);
void    *ecs_get_2(t_entity_id entity_id, t_component_id component_id, t_ecs *ecs);
*/

typedef s_query
{
	t_entity_id	*entity_matches;
    size_t		index;
}   t_query;

// Returns t_query which contains a vector of entities which each have all of the component_ids
// Note: The simple implementation of this function doesn't support nested calls of this function,
// it just has a single entity vector in *ecs!
// Nested fix: In order not to allocate the result every call,
//   *ecs can reuse past allocated query vectors when they have been marked finished by a query iterator
//   Otherwise, another query vector shall be allocate
t_query ecs_query(t_component_id *component_ids, size_t component_id_count, t_ecs *ecs);

// This function is a lot like ft_iterate(), but increments query.index for ecs_get()
t_status    ecs_iterate(t_query *query);

// This reads query.index
void    *ecs_get(t_query *query, t_component_id component_id);
