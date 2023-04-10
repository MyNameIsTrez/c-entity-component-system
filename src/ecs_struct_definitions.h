#ifndef ECS_STRUCT_DEFINITIONS_H
# define ECS_STRUCT_DEFINITIONS_H

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

#endif
