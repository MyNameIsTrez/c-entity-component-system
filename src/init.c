#include "ecs.h"
#include "src/ecs_struct_definitions.h"

t_ecs   *ecs_init(size_t t_c_size, size_t t_g_size)
{
	t_ecs   *ecs;

	ecs = ft_calloc(1, sizeof(t_ecs));

	ecs->t_c_size = t_c_size;
	ecs->t_c_count = t_c_size / sizeof(size_t);
	ecs->t_g_size = t_g_size;

	ecs->component_sizes = ft_malloc(1, t_c_size);
	ecs->entity_id_archetype_pairs = ft_vector_new(sizeof(t_archetype *));

	ecs->archetypes = ft_vector_new_reserved(sizeof(t_archetype), 1);
	ecs->archetypes[0].c = ft_calloc(1, t_c_size);
	ecs->archetypes[0].g = ft_calloc(1, t_g_size);

    ecs->new_entity_archetype = ft_malloc(1, sizeof(t_archetype));
    ecs->new_entity_archetype->c = ft_malloc(1, ecs->t_c_size);
	ecs->new_entity_archetype->g = ft_malloc(1, ecs->t_g_size);

	return (ecs);
}
