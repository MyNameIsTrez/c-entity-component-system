#include "ecs.h"
#include "ecs_struct_definitions.h"

t_entity_id	ecs_entity(t_ecs *ecs)
{
	t_archetype *empty_archetype;

	empty_archetype = &ecs->archetypes[0];
	// TODO: Let ecs contain a vector of entity IDs that have been removed and let this function use those first before incrementing ecs.next_highest_entity_id
	(void)empty_archetype;
	// ft_vector_push(&ecs->entity_id_archetype_pairs, &empty_archetype);
	return (ecs->next_highest_entity_id++);
}
