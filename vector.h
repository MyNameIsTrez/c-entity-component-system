#ifndef VECTOR_H
# define VECTOR_H

#include <stddef.h>
#include <string.h>

typedef struct s_vector	t_vector;

t_vector	*vector_new(size_t element_size);
void		*vector_grow(t_vector *vector);
void		*vector_get(t_vector *vector, size_t index);
size_t		vector_size(t_vector *vector);
void		vector_free(t_vector *vector);

#endif // VECTOR_H

# ifdef VECTOR_IMPLEMENTATION
# define VECTOR_IMPLEMENTATION

struct s_vector
{
	size_t	element_size;
	size_t	size;
	size_t	capacity;
	uint8_t	*address;
};

t_vector	*vector_new(size_t element_size)
{
	t_vector	*vector;

	vector = calloc(1, sizeof(t_vector));
	vector->element_size = element_size;
	return vector;
}

void	*vector_grow(t_vector *vector)
{
	size_t	new_element_capacity;
	uint8_t	*new_address;

	if (vector->size + 1 > vector->capacity)
	{
		if (vector->capacity == 0)
		{
			new_element_capacity = 1;
		}
		else
		{
			new_element_capacity = vector->capacity * 2;
		}
		new_address = calloc(new_element_capacity, vector->element_size);
		if (vector->size > 0)
		{
			memcpy(new_address, vector->address, vector->size * vector->element_size);
		}
		free(vector->address);
		vector->address = new_address;
		vector->capacity = new_element_capacity;
	}
	vector->size++;
	return &vector->address[(vector->size - 1) * vector->element_size];
}

void	*vector_get(t_vector *vector, size_t index)
{
	return &vector->address[index * vector->element_size];
}

size_t	vector_size(t_vector *vector)
{
	return vector->size;
}

void	vector_free(t_vector *vector)
{
	free(vector->address);
	free(vector);
}

# endif // VECTOR_IMPLEMENTATION
