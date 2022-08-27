#include "ecs.h"
#include "ecs_struct_definitions.h"

void	ecs_init(t_ecs *ecs)
{
	bzero(ecs, sizeof(t_ecs));
}

void    ecs_size(t_c *sizes, t_ecs *ecs)
{
    size_t  field_index;
    size_t  field_count;

    field_index = 0;
    field_count = sizeof(*sizes) / sizeof(size_t);
    while (field_index < field_count)
    {
		field_value = ((size_t *)sizes)[field_index];
		if (field_value > 0)
			((size_t *)ecs->c)[field_index] = field_value;
        field_index++;
    }
}

t_entity_id	ecs_entity(t_ecs *ecs)
{
	// TODO: Let ecs contain a vector of entity IDs that have been removed and let this function use those first before incrementing ecs.entity_count
	return (ecs->entity_count++);
}
