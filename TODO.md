# ecs.h
* Let ecs contain a vector of entity IDs that have been removed,
and let ecs_entity() use those before incrementing ecs.next_highest_entity_id
* Use a hash table in ecs_component() to check whether new_entity_archetype.c
and .g are already in ecs.archetypes, rather than iterating all archetypes.

# README.md
* Replace `x` with `a` and `b` in the explanation of "How the example works", since it's useful to show the memory layout of multiple components.
