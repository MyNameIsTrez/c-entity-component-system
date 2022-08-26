int	main(void)
{
	t_ecs		ecs;
	t_entity_id	monster_id;
	t_entity_id	player_id;

	ecs_init(&ecs);

	ecs_declare(COMPONENT_POSITION, sizeof(t_component_position), &ecs);
	ecs_declare(TAG_PLAYER, sizeof(t_tag_player), &ecs);

	monster_id = ecs_entity();
	ecs_add(monster_id, COMPONENT_POSITION, &(t_component_position){.age=21}, &ecs);

	player_id = ecs_entity();
	ecs_add(player_id, COMPONENT_POSITION, &(t_component_position){.age=42}, &ecs);
	ecs_add(player_id, TAG_PLAYER, &(t_tag_player){}, &ecs);

	foo(&ecs);

	return (EXIT_SUCCESS);
}

void foo(t_ecs *ecs)
{
	t_query					query; // A pointer to a simple array
	t_component_position	*position;
	t_tag_player			*player;

	query = ecs_query(COMPONENT_POSITION | TAG_PLAYER, ecs);
	while (ecs_iterate(&query) != FINISHED) // Does i++
	{
		position = ecs_get(&query, COMPONENT_POSITION); // Does query[i].position
		assert(position->age, 42); // Note how monster_id has .age=21, but isn't a player so won't be iterated
	}
}

// This is the memory layout. The core idea is to duplicate component data for optimal iteration.
// The first line is the combination of components, where | is the bitwise OR operator.
// The second line is a contiguous array[], consisting of combinations of components{}
// The third line is what it'd look like as raw bytes.

// TAG_PLAYER
// [ {.dead=true} ]
// [1] - 1 bit in total

// COMPONENT_POSITION
// [ {.age=21}, {.age=42} ]
// [21, 42] - if age is 4 bytes, 8 bytes in total

// COMPONENT_POSITION | TAG_PLAYER
// [ {.age=42} ]
// [42] - if age is 4 bytes, 4 bytes in total
