#ifndef VECTOR_H
# define VECTOR_H

#include <stddef.h>
#include <string.h>

typedef struct s_vector	t_vector;

t_vector	*vector_new(size_t type_size);
void		vector_grow(t_vector *vector);
void		*vector_get(t_vector *vector, size_t index);
void		vector_free(t_vector *vector);

#endif // VECTOR_H

# ifdef VECTOR_IMPLEMENTATION
# define VECTOR_IMPLEMENTATION

struct s_vector
{
	size_t	type_size;
	size_t	element_count;
	size_t	element_capacity;
	uint8_t	*address;
};

t_vector	*vector_new(size_t type_size)
{
	t_vector	*vector;

	vector = calloc(1, sizeof(t_vector));
	vector->type_size = type_size;
	return (vector);
}

void	vector_grow(t_vector *vector)
{
	size_t	new_element_capacity;
	uint8_t	*new_address;

	if (vector->element_count + 1 > vector->element_capacity)
	{
		if (vector->element_capacity == 0)
		{
			new_element_capacity = 1;
		}
		else
		{
			new_element_capacity = vector->element_capacity * 2;
		}
		new_address = calloc(new_element_capacity, vector->type_size);
		if (vector->element_count > 0)
		{
			memcpy(new_address, vector->address, vector->element_count * vector->type_size);
		}
		free(vector->address);
		vector->address = new_address;
		vector->element_capacity = new_element_capacity;
	}
	vector->element_count++;
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
