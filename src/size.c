#include "ecs.h"
#include "src/ecs_struct_definitions.h"

void    ecs_size(t_c *sizes, t_ecs *ecs)
{
	size_t  field_index;
	size_t  field_value;

	field_index = 0;
	while (field_index < ecs->t_c_count)
	{
		field_value = ((size_t *)sizes)[field_index];
		((size_t *)ecs->component_sizes)[field_index] = field_value;
		field_index++;
	}
}
