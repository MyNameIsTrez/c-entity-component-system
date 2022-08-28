#include "ecs.h"
#include "ecs_struct_definitions.h"
#include "ecs_internal.h"

void	ecs_init(t_ecs *ecs)
{
	bzero(ecs, sizeof(t_ecs));
}

void    ecs_size(t_c *sizes, t_ecs *ecs)
{
    size_t  field_index;
    size_t  field_count;
    size_t  field_value;

    field_index = 0;
    field_count = sizeof(*sizes) / sizeof(size_t);
    while (field_index < field_count)
    {
		field_value = ((size_t *)sizes)[field_index];
		((size_t *)ecs->component_sizes)[field_index] = field_value;
        field_index++;
    }
}

t_entity_id	ecs_entity(t_ecs *ecs)
{
	// TODO: Let ecs contain a vector of entity IDs that have been removed and let this function use those first before incrementing ecs.entity_count
	return (ecs->entity_count++);
}

void	ecs_component(t_entity_id entity_id, t_c *added_component, void *value, t_ecs *ecs)
{

}
