typedef t_u32   t_entity_id;

typedef enum e_component_id
{
	COMPONENT_ENTITY,
	COMPONENT_PLAYER,
}	t_component_id;

typedef struct s_component_entity
{
	t_tile	tile; // !Note that this should be moved into its own component if you have tiles that aren't in entities!
	t_u32	ticks_since_last_frame_change;
	t_u32	ticks_between_frame_changes;
	t_u32	ticks_since_last_update;
	t_u32	ticks_between_updates;
	bool	enabled;
}	t_component_entity;

// Note how unlike in so_long, the player doesn't store "t_entity *entity"
typedef s_component_player
{
	t_controls	controls;
	bool		dead;
}   t_component_player;

// This tells *ecs what the stride of each component is
// Example:
// ecs_declare(COMPONENT_PLAYER, sizeof(t_component_player), ecs);
void    ecs_declare(t_component_id component_id, size_t component_size, t_ecs *ecs);

// Entity IDs are necessary for associating components with one another
// Example:
// t_entity_id	player;
// player = ecs_create();
t_entity_id	ecs_create(void);

// Under the hood this function will add both data and its entity_id right next to one another
// Note that data isn't referring to the static data struct that most of my programs store their global state in!
// Example:
// ecs_add(player_id, COMPONENT_PLAYER, &(t_component_player){.controls = X, .dead=false}, ecs);
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
    size_t	index;
}   t_query;

// Returns a vector of entities which each have all of the component_ids
// Note: The simple implementation of this function doesn't support nested calls of this function,
// it just has a single entity vector in *ecs!
// Nested fix: In order not to allocate the result every call,
//   *ecs can reuse past allocated query vectors when they have been marked finished by a query iterator
//   Otherwise, another query vector shall be allocate
// Example:
// t_query  query;
// query = ecs_query((t_component_id []){COMPONENT_PLAYER, COMPONENT_ENTITY}, 2, ecs);
t_query ecs_query(t_component_id component_ids[], size_t component_id_count, t_ecs *ecs);

// This reads query.index
// Example:
// t_component_player   *player;
// player = ecs_get(&query, COMPONENT_PLAYER);
void    *ecs_get(t_query *query, t_component_id component_id);

// This function is a lot like ft_iterate(), but increments query.index for ecs_get()
// Example:
// t_component_player   *player;
// t_component_entity   *entity;
// while (ecs_iterate(&query) != FINISHED)
// {
//     player = ecs_get(&query, COMPONENT_PLAYER);
//     entity = ecs_get(&query, COMPONENT_ENTITY);
//     printf("%i, %i\n", player->dead, entity->tile.index);
// }
t_status    ecs_iterate(t_query *query);
