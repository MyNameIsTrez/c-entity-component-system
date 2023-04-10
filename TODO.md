# ecs.h
* Let ecs contain a vector of entity IDs that have been removed and let ecs_entity() use those before incrementing ecs.next_highest_entity_id

# vector.h
* Write vector_push() and replace all uses of vector_grow() with it.
