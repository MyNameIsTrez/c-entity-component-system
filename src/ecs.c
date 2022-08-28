#include "ecs.h"
#include "ecs_struct_definitions.h"
// #include "ecs_internal.h"

t_ecs   *ecs_init(void)
{
    t_ecs   *ecs;

    ecs = ft_calloc(1, sizeof(t_ecs));
    return (ecs);
}

void    ecs_size(t_c *sizes, size_t t_c_size, t_ecs *ecs)
{
    size_t  field_index;
    size_t  field_count;
    size_t  field_value;

    field_index = 0;
    field_count = t_c_size / sizeof(size_t);
    while (field_index < field_count)
    {
		field_value = ((size_t *)sizes)[field_index];
		((size_t *)ecs->component_sizes)[field_index] = field_value;
        field_index++;
    }
}

t_entity_id	ecs_entity(t_ecs *ecs)
{
	// TODO: Let ecs contain a vector of entity IDs that have been removed and let this function use those first before incrementing ecs.highest_entity_id
	return (ecs->highest_entity_id++);
}

// void	ecs_component(t_entity_id entity_id, t_c *added_component, void *value, t_ecs *ecs)
// {

// }
