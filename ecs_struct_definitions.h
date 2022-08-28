#ifndef ECS_STRUCT_DEFINITIONS_H
# define ECS_STRUCT_DEFINITIONS_H

typedef	s_archetype
{
	t_c	*c;
	t_g	*g;
}	t_archetype;

typedef s_ecs
{
	t_c			*component_sizes;
	size_t		entity_count;
	t_archetype	*entity_id_archetypes; // vector that maps index entity_id 5 -> value archetype 3 for when components are added to/removed from an entity
	t_archetype	*archetypes; // Is a Set data type
	void		**archetypes_data; // A vector where each index corresponds with an index in the archetypes field, and the value is a pointer to archetype data
}	t_ecs;

// TODO: Typedef to t_iterator?
typedef s_query
{
	t_u8	*data;
	size_t	entity_index;
}	t_query;

#endif
