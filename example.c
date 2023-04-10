// #include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// Components
// The sizes of components in bytes are stored here.
// x is an int and sizeof(int) == 32, so this s_c.x size_t will hold 32.
struct	s_c
{
	size_t	x;
};

// Tags (_t is reserved, so can't be s_t)
// Tags are effectively components without a value.
// Useful when you just want to differentiate say a player from a monster.
struct	s_g
{
	bool	player;
};

#define ECS_IMPLEMENTATION
#include "ecs.h"

// void	foo(t_ecs *ecs);

int	main(void)
{
	t_ecs		*ecs;
	t_entity_id	monster_id;
	// t_entity_id	player_id;
	int			x;

	ecs = ecs_init(sizeof(t_c), sizeof(t_g));

	ecs_size(ecs, &(t_c){.x=sizeof(int)});

	monster_id = ecs_entity(ecs);
	x = 21;
	// sizeof(int) bytes from x are copied
	ecs_component(ecs, monster_id, &(t_c){.x=1}, (int *)&x);

	// // player_id = ecs_entity(ecs);
	// // x = 42;
	// // ecs_component(ecs, player_id, &(t_c){.x=1}, (int *)&x);
	// // ecs_tag(ecs, player_id, &(t_g){.player=1});

	// // foo(ecs);

	ecs_cleanup(ecs);

	return (EXIT_SUCCESS);
}

// void	foo(t_ecs *ecs)
// {
	// iterator contains a pointer to an array of components, and has an iteration index for ecs_iterate()
// 	t_iterator	*iterator;
// 	int		*x;

// 	iterator = ecs_query(ecs, &(t_c){.x=1}, &(t_g){.player=1});
	// Does i++
// 	while (ecs_iterate(iterator))
// 	{
		// Does iterator[i].x
// 		x = ecs_get(&(t_c){.x=1}, iterator);
		// monster_id has an x that is 21, but doesn't have the player tag so won't be iterated
// 		assert(*x == 42);
// 	}
// }
