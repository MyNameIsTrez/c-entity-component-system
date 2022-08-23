void foo(t_ecs *ecs)
{
	t_query				query;
	t_component_player	*player;
	t_component_entity	*entity;

	query = ecs_query((t_component_id []){COMPONENT_PLAYER, COMPONENT_ENTITY}, 2, ecs);
	while (ecs_iterate(&query) != FINISHED)
	{
		player = ecs_get(&query, COMPONENT_PLAYER);
		entity = ecs_get(&query, COMPONENT_ENTITY);
		printf("%i, %i\n", player->dead, entity->tile.index);
	}
}

int	main(void)
{
	t_ecs		ecs;
	t_entity_id	player_id_1;
	t_entity_id	player_id_2;

	ecs_init(2, &(sizeof []){
		sizeof(t_component_entity),
		sizeof(t_component_player),
	}, ecs);

	player_id_1 = ecs_create();
	ecs_add(player_id_1, COMPONENT_PLAYER, &(t_component_player){.dead=false}, ecs);

	player_id_2 = ecs_create();
	ecs_add(player_id_2, COMPONENT_PLAYER, &(t_component_player){.dead=true}, ecs);
	ecs_add(player_id_2, COMPONENT_ENTITY, &(t_component_entity){.enabled=true}, ecs);

	foo(&ecs);
	return (EXIT_SUCCESS);
}
