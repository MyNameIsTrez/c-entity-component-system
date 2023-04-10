#include "ecs.h"
#include "ecs_struct_definitions.h"

#include <stdlib.h>

t_ecs   *ecs_init(size_t t_c_size, size_t t_g_size)
{
	t_ecs   *ecs;

	ecs = calloc(1, sizeof(t_ecs));

	ecs->t_c_size = t_c_size;
	ecs->t_c_count = t_c_size / sizeof(size_t);
	ecs->t_g_size = t_g_size;

	ecs->component_sizes = calloc(1, t_c_size);
	// ecs->entity_id_archetype_pairs = ft_vector_new(sizeof(t_archetype *));

	// ecs->archetypes = ft_vector_new_reserved(sizeof(t_archetype), 1);
	ecs->archetypes[0].c = calloc(1, t_c_size);
	ecs->archetypes[0].g = calloc(1, t_g_size);

    ecs->new_entity_archetype = calloc(1, sizeof(t_archetype));
    ecs->new_entity_archetype->c = calloc(1, ecs->t_c_size);
	ecs->new_entity_archetype->g = calloc(1, ecs->t_g_size);

	return (ecs);
}
