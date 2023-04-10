#include "ecs.h"
#include "ecs_struct_definitions.h"

#include <string.h>

void	update_new_entity_archetype(t_archetype *old_entity_archetype, t_c *added_component, t_ecs *ecs)
{
	size_t  field_index;
	size_t  field_value;

	memcpy(ecs->new_entity_archetype->c, old_entity_archetype->c, ecs->t_c_size);
	memcpy(ecs->new_entity_archetype->g, old_entity_archetype->g, ecs->t_c_size);

	field_index = 0;
	while (field_index < ecs->t_c_count)
	{
		field_value = ((size_t *)added_component)[field_index];
		if (field_value == 1)
			((size_t *)ecs->new_entity_archetype->c)[field_index] = field_value;
		field_index++;
	}
}
