#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

struct List;
typedef void (*DataFp)(void*);
typedef void (*ConstDataFp)(const void*);
typedef  int (*CompareDataFp)(const void*, const void*);

typedef struct ListElement {
	struct ListElement *next;
	void *data;
} ListElement;

typedef struct {
	ListElement *head;
	ListElement *tail;
	ConstDataFp dump_data;
	DataFp free_data;
	CompareDataFp compare_data;
	DataFp modify_data;
} List;

void *safe_malloc(size_t size) {
	void *ptr = malloc(size);
	if(ptr) return ptr;
	printf("malloc error\n");
	exit(EXIT_FAILURE);
}

void *safe_strdup(const char *string) {
	void *ptr = strdup(string);
	if(ptr) return ptr;
	printf("strdup error\n");
	exit(EXIT_FAILURE);
}

// --- generic functions --- for any data type

void init_list(List *p_list, ConstDataFp dump_data, DataFp free_data,
		CompareDataFp compare_data, DataFp modify_data) {
	p_list->head = NULL;
	p_list->tail = NULL;
	p_list->modify_data = modify_data;
	p_list->compare_data = compare_data;
	p_list->dump_data = dump_data;
	p_list->free_data = free_data;
}

// Print elements of the list
void dump_list(const List* p_list) {
	ListElement* p = p_list->head;

	while (p != NULL)
	{
		p_list->dump_data(p->data);
		p = p->next;
	}
	printf("\n");
}

// Print elements of the list if comparable to data
void dump_list_if(List *p_list, void *data) {
	ListElement* p = p_list->head;

	while (p != NULL)
	{
		if (p_list->compare_data(p->data, data))
			p_list->dump_data(p->data);

		p = p->next;
	}
	printf("\n");
}

// Free element pointed by data using free_data() function
void free_element(DataFp free_data, ListElement *to_delete) {
	free_data(to_delete->data);
}

// Free all elements of the list
void free_list(List* p_list) {
	if (p_list->head == NULL)
		return;
	
	ListElement *first = p_list->head, *second = p_list->head->next;
	while (second != NULL)
	{
		p_list->free_data(first->data);
		first = second;
		second = second->next;
	}

	p_list->free_data(first);
	p_list->head = NULL;
	p_list->tail = NULL;
}

// Push element at the beginning of the list
void push_front(List *p_list, void *data) {
	ListElement* new_element = safe_malloc(sizeof(ListElement));
	new_element->data = data;
	new_element->next = p_list->head;

	p_list->head = new_element;
	if (p_list->tail == NULL)
		p_list->tail = new_element;
}

// Push element at the end of the list
void push_back(List *p_list, void *data) {
	ListElement* new_element = malloc(sizeof(ListElement));
	new_element->data = data;
	new_element->next = NULL;

	if (p_list->tail == NULL)
	{
		p_list->head = new_element;
		p_list->tail = new_element;
	}
	else
	{
		p_list->tail->next = new_element;
		p_list->tail = p_list->tail->next;
	}
}

// Remove the first element
void pop_front(List *p_list) {
	if (p_list != NULL)
	{
		ListElement* second = p_list->head->next;
		p_list->free_data(p_list->head);
		p_list->head = second;
	}
}

// Reverse the list
void reverse(List *p_list) {
	if (p_list->head == p_list->tail)
		return;
	
	ListElement* prev = NULL, *current = p_list->head, *next = p_list->head->next;
	ListElement* new_start = p_list->tail, *new_end = p_list->head;

	while (next != NULL)
	{
		current->next = prev;
		prev = current;
		current = next;
		next = next->next;
	}

	current->next = prev;

	p_list->head = new_start;
	p_list->tail = new_end;
}

// Insert element preserving order
void insert_in_order(List *p_list, void *p_data) {
	if (p_list->head == NULL || p_list->compare_data(p_list->head->data, p_data) > 0)
	{
		push_front(p_list, p_data);
		return;
	}

	ListElement* new_element = safe_malloc(sizeof(ListElement));
	new_element->data = p_data;
	new_element->next = NULL;

	ListElement* current = p_list->head;

	while (current->next != NULL && p_list->compare_data(current->next->data, p_data) <= 0)
		current = current->next;

	if (p_list->compare_data(current->data, p_data) == 0 && p_list->modify_data != NULL)
		p_list->modify_data(current->data);
	else if (p_list->compare_data(current->data, p_data))
	{
		new_element->next = current->next;
		current->next = new_element;
	}
}

// -----------------------------------------------------------
// --- type-specific definitions

// int element

void dump_int(const void *d) {
	printf("%d ", *(int*)d);
}

void free_int(void *d) {
	free(d);
}

int cmp_int(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int *create_data_int(int v) {
	int* value = safe_malloc(sizeof(v));
	memcpy(value, &v, sizeof(int));
	return value;
}

// Word element

typedef struct DataWord {
	char *word;
	int counter;
} DataWord;

void dump_word (const void *d) {
	printf("%s ", ((DataWord*)d)->word);
}

void free_word(void *d) {
	free(d);
}

int cmp_word_alphabet(const void *a, const void *b) {
	char *x = safe_strdup(((DataWord*)a)->word), *y = safe_strdup(((DataWord*)b)->word);
	
	for (int i = 0; x[i] != '\0'; i++)
		x[i] = tolower(x[i]);
	
	for (int i = 0; y[i] != '\0'; i++)
		y[i] = tolower(y[i]);

	return strcmp(x, y);
}

int cmp_word_counter(const void *a, const void *b) {
	DataWord *x = (DataWord*)a, *y = (DataWord*)b;
	return x->counter - y->counter;
}

void dump_word_lowercase(const void *a)
{
	char *word = safe_strdup(((DataWord*)a)->word);
	for (int i = 0; word[i] != '\0'; i++)
		word[i] = tolower(word[i]);

	printf("%s ", word);
}

void modify_word(void *p) {
	DataWord *x = (DataWord*)p;
	(x->counter)++;
}

void *create_data_word(const char *string, int counter) {
	DataWord* result = safe_malloc(sizeof(DataWord));
	result->word = safe_strdup(string);
	result->counter = counter;
	return (void*)result;
}

// read text, parse it to words, and insert those words to the list.
// Order of insertions is given by the last parameter of type CompareDataFp.
// (comparator function address). If this address is not NULL the element is
// inserted according to the comparator. Otherwise, read order is preserved.
void stream_to_list(List *p_list, FILE *stream, CompareDataFp cmp) {
	const char delimits[] = " \r\t\n.,?!:;-";
	char buffer[BUFFER_SIZE];

	while (!feof(stream))
	{
		buffer[0] = '\0';
		fgets(buffer, BUFFER_SIZE, stream);

		for (
			char* word = strtok(buffer, delimits);
			word != NULL;
			word = strtok(NULL, delimits)
		)
		{
			if (p_list->compare_data)
				insert_in_order(p_list, create_data_word(word, 0));
			else
				push_back(p_list, create_data_word(word, 0));
		}
	}
}

// test integer list
void list_test(List *p_list, int n) {
	char op;
	int v;
	for (int i = 0; i < n; ++i) {
		scanf(" %c", &op);
		switch (op) {
			case 'f':
				scanf("%d", &v);
				push_front(p_list, create_data_int(v));
				break;
			case 'b':
				scanf("%d", &v);
				push_back(p_list, create_data_int(v));
				break;
			case 'd':
				pop_front(p_list);
				break;
			case 'r':
				reverse(p_list);
				break;
			case 'i':
				scanf("%d", &v);
				insert_in_order(p_list, create_data_int(v));
				break;
			default:
				printf("No such operation: %c\n", op);
				break;
		}
	}
}

int main(void) {
	int to_do, n;
	List list;

	scanf ("%d", &to_do);
	switch (to_do) {
		case 1: // test integer list
			scanf("%d",&n);
			init_list(&list, dump_int, free_int, cmp_int, NULL);
			list_test(&list, n);
			dump_list(&list);
			free_list(&list);
			break;
		case 2: // read words from text, insert into list, and print
			init_list(&list, dump_word, free_word, NULL, NULL);
			stream_to_list(&list, stdin, NULL);
			dump_list(&list);
			free_list(&list);
			break;
		case 3: // read words, insert into list alphabetically, print words encountered n times
			scanf("%d",&n);

			init_list(&list, dump_word_lowercase, free_word, cmp_word_alphabet, modify_word);
			stream_to_list(&list, stdin, cmp_word_alphabet);

			DataWord data = { NULL, n };
			list.compare_data = cmp_word_counter;
			dump_list_if(&list, &data);
			free_list(&list);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

