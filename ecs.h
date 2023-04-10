#ifndef ECS_H
# define ECS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ecs		t_ecs;
// Entity IDs allow associating components with one another
typedef uint32_t			t_entity_id;
typedef struct s_iterator	t_iterator;
typedef struct s_c			t_c;
typedef struct s_g			t_g;

t_ecs   *ecs_init(size_t t_c_size, size_t t_g_size);

// Declares what the sizes of components and the size of t_c are
void	ecs_size(t_ecs *ecs, t_c *sizes);

// Creates an entity
t_entity_id	ecs_entity(t_ecs *ecs);

void	ecs_component(t_ecs *ecs, t_entity_id entity_id, t_c *added_component, void *value);

void	ecs_tag(t_ecs *ecs, t_entity_id entity_id, t_g *added_tags);

t_iterator	*ecs_query(t_ecs *ecs, t_c *components, t_g *tags);

// Increments iterator->entity_index for ecs_get()
bool	ecs_iterate(t_iterator *iterator);

// Returns a pointer to data + iterator->entity_index * block_size + component offset
void	*ecs_get(t_c *component, t_iterator *iterator);

void	ecs_cleanup(t_ecs *ecs);

/*
// This can't be used for writing to components since the data is duplicated
// Example:
// int *x = ecs_get_2(player_id, (t_c *)&{.x=1}, ecs);
void	*ecs_get_2(t_entity_id entity_id, t_c *component, t_ecs *ecs);

void	ecs_remove(t_entity_id entity_id, t_c *component, t_ecs *ecs);

void	ecs_destroy(t_entity_id entity_id, t_ecs *ecs);
*/

#endif // ECS_H

# ifdef ECS_IMPLEMENTATION
# define ECS_IMPLEMENTATION

# define VECTOR_IMPLEMENTATION
# include "vector.h"

typedef	struct s_archetype
{
	t_c	*c;
	t_g	*g;
}	t_archetype;

struct s_ecs
{
	size_t		t_c_size;
	size_t		t_c_count;
	size_t		t_g_size;
	t_c			*component_sizes;
	t_entity_id	next_highest_entity_id;

	// t_archetype **
	t_vector	*entity_id_archetype_pairs;

	// t_archetype *, is a Set.
	t_vector	*archetypes;

	t_archetype	*new_entity_archetype;

	// A vector where each index corresponds with an index
	// in the archetypes field, and the value is a pointer to archetype data.
	void		**archetypes_data;
};

struct s_iterator
{
	uint8_t	*data;
	size_t	entity_index;
};

t_ecs   *ecs_init(size_t t_c_size, size_t t_g_size)
{
	t_ecs   	*ecs;
	t_archetype	*archetype;

	ecs = calloc(1, sizeof(t_ecs));

	ecs->t_c_size = t_c_size;
	ecs->t_c_count = t_c_size / sizeof(size_t);
	ecs->t_g_size = t_g_size;

	ecs->component_sizes = calloc(1, t_c_size);
	ecs->entity_id_archetype_pairs = vector_new(sizeof(t_archetype *));

	ecs->archetypes = vector_new(sizeof(t_archetype));
	archetype = vector_grow(ecs->archetypes);
	archetype->c = calloc(1, t_c_size);
	archetype->g = calloc(1, t_g_size);

    ecs->new_entity_archetype = calloc(1, sizeof(t_archetype));
    ecs->new_entity_archetype->c = calloc(1, ecs->t_c_size);
	ecs->new_entity_archetype->g = calloc(1, ecs->t_g_size);

	return ecs;
}

void    ecs_size(t_ecs *ecs, t_c *sizes)
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
	t_archetype	**archetype_ptr;

	empty_archetype = vector_get(ecs->archetypes, 0);
	archetype_ptr = vector_grow(ecs->entity_id_archetype_pairs);
	*archetype_ptr = empty_archetype;
	return ecs->next_highest_entity_id++;
}

static void	_update_new_entity_archetype(t_archetype *old_entity_archetype, t_c *added_component, t_ecs *ecs)
{
	size_t  field_index;

	memcpy(ecs->new_entity_archetype->c, old_entity_archetype->c, ecs->t_c_size);
	memcpy(ecs->new_entity_archetype->g, old_entity_archetype->g, ecs->t_g_size);

	field_index = 0;
	while (field_index < ecs->t_c_count)
	{
		if (((size_t *)added_component)[field_index] == 1)
		{
			((size_t *)ecs->new_entity_archetype->c)[field_index] = 1;
		}
		field_index++;
	}
}

static bool	_c_identical(t_c *c, t_c *new_c, size_t t_c_size)
{
	size_t		index;

	index = 0;
	while (index < t_c_size)
	{
		if (((size_t *)c)[index] != ((size_t *)new_c)[index])
		{
			return false;
		}
		index++;
	}
	return true;
}

static bool	_g_identical(t_g *g, t_g *new_g, size_t t_g_size)
{
	size_t		index;

	index = 0;
	while (index < t_g_size)
	{
		if (((bool *)g)[index] != ((bool *)new_g)[index])
		{
			return false;
		}
		index++;
	}
	return true;
}

static t_archetype	*_find_archetype(t_archetype *new_entity_archetype, t_vector *archetypes, size_t t_c_size, size_t t_g_size)
{
	size_t		index;
	t_archetype	*archetype;

	index = 0;
	while (index < vector_size(archetypes))
	{
		archetype = vector_get(archetypes, index);
		if (_c_identical(archetype->c, new_entity_archetype->c, t_c_size)
		&& _g_identical(archetype->g, new_entity_archetype->g, t_g_size))
		{
			return vector_get(archetypes, index);
		}
		index++;
	}
	return NULL;
}

void	ecs_component(t_ecs *ecs, t_entity_id entity_id, t_c *added_component, void *value)
{
	t_archetype	**old_entity_archetype_ptr;
	t_archetype	*found_archetype;

	old_entity_archetype_ptr = vector_get(ecs->entity_id_archetype_pairs, entity_id);
	_update_new_entity_archetype(*old_entity_archetype_ptr, added_component, ecs);
	(void)value;

	// Checks whether new_entity_archetype.c and .g are already in ecs.archetypes
	found_archetype = _find_archetype(ecs->new_entity_archetype, ecs->archetypes, ecs->t_c_size, ecs->t_g_size);
	if (found_archetype == NULL)
	{
	// 	new_archetype = calloc();
	// 	ft_memcpy(new_archetype, ecs->new_entity_archetype, );
	// 	ecs->archetypes vector_push() new_archetype
	// 	ecs->entity_id_archetype_pairs[entity_id] = new_archetype
	//  use value
	}
	else
	{
		*old_entity_archetype_ptr = found_archetype;
	}
}

void	ecs_cleanup(t_ecs *ecs)
{
	t_archetype	*archetype;

	free(ecs->component_sizes);
	vector_free(ecs->entity_id_archetype_pairs);
	// TODO: Loop over all archetypes to free them all!
	archetype = vector_get(ecs->archetypes, 0);
	free(archetype->c);
	free(archetype->g);
	vector_free(ecs->archetypes);
	free(ecs->new_entity_archetype->c);
	free(ecs->new_entity_archetype->g);
	free(ecs->new_entity_archetype);
	free(ecs);
}

# endif // ECS_IMPLEMENTATION
