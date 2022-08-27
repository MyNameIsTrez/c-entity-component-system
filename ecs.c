#include "ecs.h"
#include "ecs_internal.h"

void	ecs_init(t_ecs *ecs)
{
	bzero(ecs, sizeof(t_ecs));
}

void    ecs_declare(t_c c)
{
    size_t  field_index;
    size_t  field_count;

    field_index = 0;
    field_count = sizeof(c) / sizeof(size_t);
    while (field_index < field_count)
    {
        printf("%ld\n", ((size_t *)&c)[field_index]);
        field_index++;
    }
}
