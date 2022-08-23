typedef enum e_component_id
{
	COMPONENT_ENTITY,
	COMPONENT_PLAYER,
}	t_component_id;

typedef struct s_component_entity
{
	t_tile	tile; // !Note that this should be moved into its own component if you have tiles that aren't in entities!
	t_u32	ticks_since_last_frame_change;
	t_u32	ticks_between_frame_changes;
	t_u32	ticks_since_last_update;
	t_u32	ticks_between_updates;
	bool	enabled;
}	t_component_entity;

// Note how unlike in so_long, the player doesn't store "t_entity *entity"
typedef s_component_player
{
	t_controls	controls;
	bool		dead;
}   t_component_player;
