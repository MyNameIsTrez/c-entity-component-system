#ifndef VECTOR_H
# define VECTOR_H

#include <stddef.h>
#include <string.h>

typedef struct s_vector	t_vector;

t_vector	*vector_new(size_t type_size);
void		vector_push(t_vector *vector);
void		*vector_get(t_vector *vector, size_t index);
void		vector_free(t_vector *vector);

# ifdef VECTOR_IMPLEMENTATION

struct s_vector
{
	size_t	type_size;
	size_t	element_count;
	uint8_t	*address;
};

t_vector	*vector_new(size_t type_size)
{
	t_vector	*vector;

	vector = calloc(1, sizeof(t_vector));
	vector->type_size = type_size;
	return (vector);
}

void	vector_push(t_vector *vector)
{
	uint8_t	*new_address;

	vector->element_count++;
	new_address = calloc(vector->element_count, vector->type_size);
	if (vector->element_count > 1)
	{
		memcpy(new_address, vector->address, (vector->element_count - 1) * vector->type_size);
	}
	free(vector->address);
	vector->address = new_address;
}

void	*vector_get(t_vector *vector, size_t index)
{
	return (&vector->address[index * vector->type_size]);
}

void	vector_free(t_vector *vector)
{
	free(vector->address);
	free(vector);
}

# endif // VECTOR_IMPLEMENTATION

#endif // VECTOR_H
