#include "ecs.h"
#include "ecs_struct_definitions.h"
#include "private/ecs_component/ecs_private_component.h"

void	ecs_component(t_entity_id entity_id, t_c *added_component, void *value, t_ecs *ecs)
{
	t_archetype	*old_entity_archetype;

	old_entity_archetype = ecs->entity_id_archetype_pairs[entity_id];
	update_new_entity_archetype(old_entity_archetype, added_component, ecs);

	// Checks whether new_entity_archetype.c and .g are already in ecs.archetypes
	// if (ecs->new_entity_archetype in ecs->archetypes)
	// 	ecs->entity_id_archetype_pairs[entity_id] = archetype
	// else
	// 	new_archetype = calloc();
	// 	ft_memcpy(new_archetype, ecs->new_entity_archetype, );
	// 	ecs->archetypes vector_push_back() new_archetype
	// 	ecs->entity_id_archetype_pairs[entity_id] = new_archetype

	(void)value;
}
