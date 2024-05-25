#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN 64

#pragma GCC diagnostic error "-Wpointer-arith"

typedef struct Vector {
	void *data;
	size_t element_size; // size of 1 element
	size_t size; // current size
	size_t capacity; // max size
} Vector;

typedef int(*cmp_ptr)(const void*, const void*);
typedef int(*predicate_ptr)(void*);
typedef void(*read_ptr)(void*);
typedef void(*print_ptr)(const void*);

// Allocate vector to initial capacity (block_size elements),
// Set element_size, size (to 0), capacity
void init_vector(Vector *vector, size_t block_size, size_t element_size) {
	vector->data = malloc(block_size * element_size);
	vector->element_size = element_size;
	vector->size = 0;
	vector->capacity = block_size;
}

// If new_capacity is greater than the current capacity,
// new data is allocated, otherwise the function does nothing.
void reserve(Vector *vector, size_t new_capacity) {
	if (new_capacity > vector->capacity)
	{
		vector->data = realloc((*vector).data, (*vector).element_size * new_capacity);
		vector->capacity = new_capacity;
	}
}

// Resizes the vector to contain new_size elements.
// If the current size is greater than new_size, the container is
// reduced to its first new_size elements.

// If the current size is less than new_size,
// additional zero-initialized elements are appended
void resize(Vector *vector, size_t new_size) {
	vector->data = realloc(vector->data, new_size * vector->element_size);

	if (new_size > (*vector).size)
	{
		void* new_data = (void*)((char*)vector->data + vector->size * vector->element_size);
		memset(new_data, 0, (new_size - vector->size) * vector->element_size);
	}

	vector->size = new_size;
	vector->capacity = new_size;
}

// Add element to the end of the vector
void push_back(Vector *vector, void *value) {
	if (vector->size == vector->capacity)
		reserve(vector, 2 * vector->capacity);

	void* new_data = (void*)((char*)vector->data + vector->size * vector->element_size);
	memcpy(new_data, value, (*vector).element_size);
	((*vector).size)++;
}

// Remove all elements from the vector
void clear(Vector *vector) {
	free((*vector).data);
	(*vector).size = 0;
}

// Insert new element at index (0 <= index <= size) position
void insert(Vector *vector, size_t index, void *value) {
	if (vector->size == vector->capacity)
		reserve(vector, 2 * vector->capacity);

	memmove(
		(void*)((char*)vector->data + (index + 1) * vector->element_size),
		(void*)((char*)vector->data + index * vector->element_size),
		(vector->size - index) * vector->element_size
	);

	memcpy((void*)((char*)vector->data + index * vector->element_size), value, vector->element_size);

	(vector->size)++;
}

// Erase element at position index
void erase(Vector *vector, size_t index) { // 0 <= index < size
	memmove(
		(void*)((char*)vector->data + index * vector->element_size), 
		(void*)((char*)vector->data + (index + 1) * vector->element_size), 
		(vector->size - index - 1) * vector->element_size
	);
	(vector->size)--;
}

// Erase all elements that compare equal to value from the container
void erase_value(Vector *vector, void *value, cmp_ptr cmp) {
	size_t i = 0;
	while (i < vector->size)
	{
		if (!cmp(value, (void*)((char*)vector->data + i * vector->element_size)))
		{
			memmove(
				(void*)((char*)vector->data + i * vector->element_size),
				(void*)((char*)vector->data + (i + 1) * vector->element_size),
				(vector->size - i - 1) * vector->element_size
			);
			(vector->size)--;
		}
		else
			i++;
	}
}

// Erase all elements that satisfy the predicate from the vector
void erase_if(Vector *vector, int (*predicate)(void *)) {
	size_t i = 0;
	while (i < vector->size)
	{
		if (predicate((void*)((char*)vector->data + i * vector->element_size)))
		{
			memmove(
				(void*)((char*)vector->data + i * vector->element_size),
				(void*)((char*)vector->data + (i + 1) * vector->element_size),
				(vector->size - i - 1) * vector->element_size
			);
			(vector->size)--;
		}
		else
			i++;
	}
	
}

// Request the removal of unused capacity
void shrink_to_fit(Vector *vector) {
	vector->data = realloc(vector->data, vector->size * vector->element_size);
	vector->capacity = vector->size;
}

// ---------------------------------------------------

typedef struct {
	int age;
	char first_name[MAX_STR_LEN];
	char last_name[MAX_STR_LEN];
} Person;

void print_int(const void *v) {
	printf("%d ", *((int*)v));
}

void print_char(const void *v) {
	printf("%c ", *((char*)v));
}

void print_person(const void *v) {
	Person* p = (Person*) v;
	printf("%d %s %s\n", p->age, p->first_name, p->last_name);
}

void print_vector(Vector *vector, print_ptr print) {
	printf("%ld\n", vector->capacity);

	for (int i = 0; i < vector->size; i++)
		print((void*)((char*)vector->data + i * vector->element_size));
	printf("\n");
}

int int_cmp(const void *v1, const void *v2) {
	return *(int *)v1 - *(int *)v2;
}

int char_cmp(const void *v1, const void *v2) {
	return *(char *)v1 - *(char *)v2;
}

int person_cmp(const void *p1, const void *p2) {
	Person *x = (Person *)p1, *y = (Person *)p2;

	if (x->age == y->age) {
		if (strcmp(x->first_name, y->first_name)) {
			return strcmp(x->last_name, y->last_name);
		}

		return strcmp(x->first_name, y->first_name);
	}

	return y->age - x->age;
}

int is_even(void *value) {
	return *((int*)value) % 2 == 0;
}

int is_vowel(void *value) {
	char c = *(char *)value;
	if ('A' <= c && c <= 'Z') c -= 'A' - 'a';
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int is_older_than_25(void *person) {
	Person* p = (Person*)person;
	return p->age > 25;
}

void read_int(void* value) {
	scanf("%d", (int*)value);
}

void read_char(void* value) {
	scanf(" %c", (char*)value);
}

void read_person(void* value) {
	Person* p = (Person*) value;
	scanf("%d %s %s", &p->age, p->first_name, p->last_name);
}

void vector_test(Vector *vector, size_t block_size, size_t elem_size, int n, read_ptr read,
		 cmp_ptr cmp, predicate_ptr predicate, print_ptr print) {
	init_vector(vector, block_size, elem_size);
	void *v = malloc(vector->element_size);
	size_t index, size;
	for (int i = 0; i < n; ++i) {
		char op;
		scanf(" %c", &op);
		switch (op) {
			case 'p': // push_back
				read(v);
				push_back(vector, v);
				break;
			case 'i': // insert
				scanf("%zu", &index);
				read(v);
				insert(vector, index, v);
				break;
			case 'e': // erase
				scanf("%zu", &index);
				erase(vector, index);
				break;
			case 'v': // erase
				read(v);
				erase_value(vector, v, cmp);
				break;
			case 'd': // erase (predicate)
				erase_if(vector, predicate);
				break;
			case 'r': // resize
				scanf("%zu", &size);
				resize(vector, size);
				break;
			case 'c': // clear
				clear(vector);
				break;
			case 'f': // shrink
				shrink_to_fit(vector);
				break;
			case 's': // sort
				qsort(vector->data, vector->size,
				      vector->element_size, cmp);
				break;
			default:
				printf("No such operation: %c\n", op);
				break;
		}
	}
	print_vector(vector, print);
	free(vector->data);
	free(v);
}

int main(void) {
	int to_do, n;
	Vector vector_int, vector_char, vector_person;

	scanf("%d%d", &to_do, &n);

	switch (to_do) {
		case 1:
			vector_test(&vector_int, 4, sizeof(int), n, read_int, int_cmp,
				is_even, print_int);
			break;
		case 2:
			vector_test(&vector_char, 2, sizeof(char), n, read_char, char_cmp,
				is_vowel, print_char);
			break;
		case 3:
			vector_test(&vector_person, 2, sizeof(Person), n, read_person,
				person_cmp, is_older_than_25, print_person);
			break;
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}

	return 0;
}

