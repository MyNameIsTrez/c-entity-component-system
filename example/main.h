typedef enum e_component_id
{
	COMPONENT_POSITION = 0b01,
	TAG_PLAYER = 0b10,
}	t_component_id;

typedef s_tile
{
	t_i32	x;
	t_i32	y;
}	t_tile;

typedef struct s_component_position
{
	t_tile	tile; // !Note that this should be moved into its own component if you have tiles that aren't in entities!
	t_u32	ticks_since_last_frame_change;
	t_u32	ticks_between_frame_changes;
	t_u32	ticks_since_last_update;
	t_u32	ticks_between_updates;
	t_u32	age;
	bool	enabled;
}	t_component_position;

typedef s_controls
{
	t_i32	placeholder;
}	t_controls;

typedef s_tag_player
{
}	t_tag_player;
