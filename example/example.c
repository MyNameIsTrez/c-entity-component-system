#include "ecs.h"
#include "assert.h"

typedef struct	s_c
{
	size_t	x;
}	t_c; // Components

typedef struct	s_g
{
	bool	player;
}	t_g; // Tags (_t is reserved)

// void	foo(t_ecs *ecs);

int	main(void)
{
	t_ecs		*ecs;
	t_entity_id	monster_id;
	// t_entity_id	player_id;
	int			x;

	ecs = ecs_init(sizeof(t_c), sizeof(t_g));

	ecs_size(&(t_c){.x=sizeof(int)}, ecs);

	monster_id = ecs_entity(ecs);
	x = 21;
	ecs_component(monster_id, &(t_c){.x=1}, (int *)&x, ecs); // sizeof(int) bytes from x are copied

	// player_id = ecs_entity(ecs);
	// x = 42;
	// ecs_component(player_id, &(t_c){.x=1}, (int *)&x, ecs);
	// ecs_tag(player_id, &(t_g){.player=1}, ecs);

	// foo(ecs);

	return (EXIT_SUCCESS);
}

// void	foo(t_ecs *ecs)
// {
// 	t_query	*query; // Pointer to an array of components, and keeps an index for ecs_iterate()
// 	int		*x;

// 	query = ecs_query(&(t_c){.x=1}, &(t_g){.player=1}, ecs);
// 	while (ecs_iterate(query) != FINISHED) // Does i++
// 	{
// 		x = ecs_get(&(t_c){.x=1}, query); // Does query[i].x
// 		assert(*x == 42); // Note how monster_id has an x of 21, but doesn't have the player tag so won't be iterated
// 	}
// }

// This is the memory layout.
// The core idea is to duplicate component data for optimal iteration.
// The first line is the combination of components and tags.
// The second line is a contiguous array[] of combinations of components{}
// The third line is how it's stored as bytes.

// x
// [ {.x=21}, {.x=42} ]
// [21, 42] - x is 4 bytes, so 8 bytes in total

// x + player
// [ {.x=42} ]
// [42] - x is 4 bytes, so 4 bytes in total
