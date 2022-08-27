#ifndef ECS_STRUCT_DEFINITIONS_H
# define ECS_STRUCT_DEFINITIONS_H

typedef s_ecs
{
	t_c	*c;
	size_t	entity_count;
}	t_ecs;

// TODO: Typedef to t_iterator?
typedef s_query
{
	t_u8	*data;
	size_t	entity_index;
}	t_query;

#endif
