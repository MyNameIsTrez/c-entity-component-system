# c-entity-component-system

This is a simple and efficient C implementation of an Entity Component System.

## The example

Clone this repository and execute `make example` to run it.

Read example.c to get a feel for how ecs.h should be used.

### How the example works
This is the memory layout. The core idea is to duplicate component data for optimal iteration.

The first line has the component names.

The second line has the tag names.

The third line is a contiguous array[] of the components{}.

The fourth line is how it's stored as bytes.

```json
x

[ {.x=21}, {.x=42} ]
[ 21, 42 ] - x is 4 bytes, so 8 bytes in total
```

```json
x
player
[ {.x=42} ]
[ 42 ] - x is 4 bytes, so 4 bytes in total
```

## How the ECS works

See [Dylan Falconer's ECS YouTube video](https://www.youtube.com/watch?v=s6TMa33niJo) for an excellent explanation of roughly the same API. The main difference is that his implementation uses an Array of Structs, while mine uses a Struct of Arrays. This made my implementation slightly harder to implement, but also much more efficient.

## What makes the iteration so fast

The magic is in the `ecs_query()` function. Whenever it is called with a combination of components that it hasn't seen before, it'll create a new array where those components are alternated, like `ABABAB...`

Whenever that function is called a second time with the same combination of components, it won't have to recreate that array.

The function will then return an object that contains a pointer to the start of that array.

The point of alternating components like this is to make the cache happy. If during iteration you instead have an array like `AAA...` and an array like `BBB...`, it can happen that reading a single `A` will overwrite all cached `BBB...` data. It is bad if this happens often, since it takes a relatively long time to fetch that `BBB...` data back.
