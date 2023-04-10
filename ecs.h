#ifndef ECS_H
# define ECS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ecs	t_ecs;

// Entity IDs allow associating components with one another
typedef uint32_t	t_entity_id;

typedef struct s_query	t_query;

typedef struct s_c	t_c;
typedef struct s_g	t_g;

typedef	struct s_archetype
{
	t_c	*c;
	t_g	*g;
}	t_archetype;

typedef struct s_ecs
{
	size_t		t_c_size;
	size_t		t_c_count;
	size_t		t_g_size;
	t_c			*component_sizes;
	t_entity_id	next_highest_entity_id;
	t_archetype	**entity_id_archetype_pairs;
	t_archetype	*archetypes; // Is a Set data type
	t_archetype	*new_entity_archetype;
	void		**archetypes_data; // A vector where each index corresponds with an index in the archetypes field, and the value is a pointer to archetype data
}	t_ecs;

// TODO: Typedef to t_iterator?
typedef struct s_query
{
	uint8_t	*data;
	size_t	entity_index;
}	t_query;

t_ecs   *ecs_init(size_t t_c_size, size_t t_g_size);

// Declares what the sizes of components and the size of t_c are
void	ecs_size(t_c *sizes, t_ecs *ecs);

// Creates an entity
t_entity_id	ecs_entity(t_ecs *ecs);

void	ecs_component(t_entity_id entity_id, t_c *added_component, void *value, t_ecs *ecs);

void	ecs_tag(t_entity_id entity_id, t_g *added_tags, t_ecs *ecs);

t_query	*ecs_query(t_c *components, t_g *tags, t_ecs *ecs);

// Increments query.entity_index for ecs_get()
bool	ecs_iterate(t_query *query);

// Returns a pointer to data + query.entity_index * block_size + component offset
void	*ecs_get(t_c *component, t_query *query);

/*
// This can't be used for writing to components since the data is duplicated
// Example:
// int *x = ecs_get_2(player_id, (t_c *)&{.x=1}, ecs);
void	*ecs_get_2(t_entity_id entity_id, t_c *component, t_ecs *ecs);

void	ecs_remove(t_entity_id entity_id, t_c *component, t_ecs *ecs);

void	ecs_destroy(t_entity_id entity_id, t_ecs *ecs);
*/

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

t_entity_id	ecs_entity(t_ecs *ecs)
{
	t_archetype *empty_archetype;

	empty_archetype = &ecs->archetypes[0];
	// TODO: Let ecs contain a vector of entity IDs that have been removed and let this function use those first before incrementing ecs.next_highest_entity_id
	(void)empty_archetype;
	// ft_vector_push(&ecs->entity_id_archetype_pairs, &empty_archetype);
	return (ecs->next_highest_entity_id++);
}

static void	update_new_entity_archetype(t_archetype *old_entity_archetype, t_c *added_component, t_ecs *ecs)
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

#endif
