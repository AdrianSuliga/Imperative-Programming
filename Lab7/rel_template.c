#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

int is_connected(pair *tab, int n);
void array_sort(int *domain, int n);

void print_relation(pair *relation, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d %d\n", relation[i].first, relation[i].second);
}

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
	int iterator = 0;
	while (iterator < n)
	{
		if (tab[iterator].first == new_pair.first && tab[iterator].second == new_pair.second)
			return 0;
		iterator++;
	}
	tab[iterator] = new_pair;
	return 1;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) { 
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		pair new_pair;
		scanf("%d %d", &new_pair.first, &new_pair.second);
		if (add_relation(relation, i, new_pair) == 0)
			n--;
	}
	return n;
}

void print_int_array(int *array, int n) {
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

//------------------------------------------------

int relation_contains(pair* relation, int n, pair p)
{
	for (int i = 0; i < n; i++)
	{
		if (relation[i].first == p.first && relation[i].second == p.second)
			return 1;
	}
	return 0;
}

// Case 1:
int is_in_array(int* result, int size, int value)
{
	for (int i = 0; i < size; i++)
	{
		if (result[i] == value)
			return 1;
	}
	return 0;
} 
void extract_values(pair* tab, int n, int *diff_values, int *values)
{
	int iterator = 0;
	for (int i = 0; i < n; i++)
	{
		if (!is_in_array(values, iterator, tab[i].first))
		{
			values[iterator] = tab[i].first;
			iterator++;
		}
		if (!is_in_array(values, iterator, tab[i].second))
		{
			values[iterator] = tab[i].second;
			iterator++;
		}
	}
	(*diff_values) = iterator;
}

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair *tab, int n) {
	int diff_values = 0;
	int values[2*n];
	pair p;
	extract_values(tab, n, &diff_values, values);

	for (int i = 0; i < diff_values; i++)
	{
		p.first = values[i];
		p.second = values[i];
		if (!relation_contains(tab, n, p))
			return 0;
	}
	return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair *tab, int n) { 
	int diff_values = 0;
	int values[2*n];
	pair p;
	extract_values(tab, n, &diff_values, values);

	for (int i = 0; i < diff_values; i++)
	{
		p.first = values[i];
		p.second = values[i];
		if (relation_contains(tab, n, p))
			return 0;
	}
	return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair *tab, int n) {
	pair p;
	for (int i = 0; i < n; i++)
	{
		p.first = tab[i].second;
		p.second = tab[i].first;
		if (!relation_contains(tab, n, p))
			return 0;
	}
	return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair *tab, int n) {
	pair p;
	for (int i = 0; i < n; i++)
	{
		p.first = tab[i].second;
		p.second = tab[i].first;
		if (relation_contains(tab, n, p))
		{
			if (tab[i].first != tab[i].second)
				return 0;
		}
	}
	return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair *tab, int n) {
	pair p;
	for (int i = 0; i < n; i++)
	{
		p.first = tab[i].second;
		p.second = tab[i].first;
		if (relation_contains(tab, n, p))
			return 0;
	}
	return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair *tab, int n) {
	pair p;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tab[i].second == tab[j].first)
			{
				p.first = tab[i].first;
				p.second = tab[j].second;
				if (!relation_contains(tab, n, p))
					return 0;
			}
		}
	}
	return 1;
}

//------------------------------------------------

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair *tab, int n) { 
	return is_reflexive(tab, n) && is_transitive(tab, n) && is_antisymmetric(tab, n);
}

// A total order relation is a partial order relation that is connected
int is_total_order(pair *tab, int n) { 
	return is_partial_order(tab, n) && is_connected(tab, n);
}

int find_max_elements(pair *tab, int n, int *max_elements) { // tab - partial order
	int values[2 * n];
	int size = 0, iterator = 0;
	pair p;
	extract_values(tab, n, &size, values);
	for (int i = 0; i < size; i++)
	{
		int should_be_added = 1;
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				continue;
			p.first = values[i];
			p.second = values[j];
			if (relation_contains(tab, n, p))
			{
				should_be_added = 0;
				break;
			}
		}
		if (should_be_added && !is_in_array(max_elements, iterator, values[i]))
		{
			max_elements[iterator] = values[i];
			iterator++;
		}
	}
	array_sort(max_elements, iterator);
	return iterator;
}

int find_min_elements(pair *tab, int n, int *min_elements) { // tab - strong partial order
	int values[2 * n];
	int size = 0, iterator = 0;
	pair p;
	extract_values(tab, n, &size, values);
	for (int i = 0; i < size; i++)
	{
		int should_be_added = 1;
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				continue;
			p.first = values[j];
			p.second = values[i];
			if (relation_contains(tab, n, p))
			{
				should_be_added = 0;
				break;
			}
		}
		if (should_be_added && !is_in_array(min_elements, iterator, values[i]))
		{
			min_elements[iterator] = values[i];
			iterator++;
		}
	}
	array_sort(min_elements, iterator);
	return iterator;
}
int parent(int i)
{
	return (i - 1) / 2;
}
int left(int i)
{
	return 2 * i + 1;
}
int right(int i)
{
	return 2 * i + 2;
}
void swap(int* domain, int i, int j)
{
	int buffor = domain[i];
	domain[i] = domain[j];
	domain[j] = buffor;
}
void heapify(int *domain, int n, int i)
{
	int l = left(i), r = right(i), mi = i;
	if (l < n && domain[l] > domain[mi])
		mi = l;
	if (r < n && domain[r] > domain[mi])
		mi = r;
	if (mi != i)
	{
		swap(domain, mi, i);
		heapify(domain, n, mi);
	}
}
void build_heap(int *domain, int n)
{
	for (int i = parent(n - 1); i > -1; i--)
		heapify(domain, n, i);	
}
void array_sort(int *domain, int n)
{
	build_heap(domain, n);
	for (int i = n - 1; i > 0; i--)
	{
		swap(domain, 0, i);
		heapify(domain, i, 0);
	}
}
int get_domain(pair *tab, int n, int *domain) {
	int values[2*n];
	int size = 0;
	extract_values(tab, n, &size, values);
	for (int i = 0; i < size; i++)
		domain[i] = values[i];
	array_sort(domain, size);
	return size;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair *tab, int n) { 
	int values[2*n];
	int size = 0;
	pair p1, p2;
	extract_values(tab, n, &size, values);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (values[i] == values[j])
				continue;
			p1.first = values[i];
			p1.second = values[j];
			p2.first = values[j];
			p2.second = values[i];
			if (!(relation_contains(tab, n, p1) || relation_contains(tab, n, p2)))
				return 0;
		}
	}
	return 1;
}

//------------------------------------------------

// Case 3:

// x(S o R)z iff exists y: xRy and ySz
int composition (pair *rel_1, int n1, pair *rel_2, int n2, pair *rel_3) { 
	int n3 = 0;
	pair p;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (rel_1[i].second == rel_2[j].first)
			{
				p.first = rel_1[i].first;
				p.second = rel_2[j].second;
				if (add_relation(rel_3, n3, p) != 0)
					n3++;
			}
		}
	}
	return n3;
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	
	return 0;
}

