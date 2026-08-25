#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rbtree.h>

typedef enum
{
    RED,
    BLACK
} Color;

struct Node
{
    char *key;
    void *value;
    Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

struct rbtree
{
    struct Node *root;
    size_t size;
    rb_value_free_fn value_free;
};

rbtree_t *rb_create(rb_value_free_fn value_free)
{
    struct rbtree *t = malloc(sizeof(*t));
    if (t == NULL)
    {
        return NULL;
    }
    t->root = NULL;
    t->size = 0;
    t->value_free = value_free;

    return t;
}

int rb_insert(rbtree_t *t, const char *key, void *value)
{
    struct Node *node = malloc(sizeof(*node));
    node->key = key;
    node->value = value;
    return 0;
}

/* Returns the value, or NULL if absent. Tree retains ownership. */
void *rb_find(const rbtree_t *t, const char *key)
{
    struct Node *current = t->root;
    while (current != NULL)
    {
        int cmp = strcmp(key, current->key);
        if (cmp == 0)
        {

            return current->value;
        }
        else if (cmp < 0)
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }
    return NULL;
}

int rb_delete(rbtree_t *t, const char *key);
size_t rb_size(const rbtree_t *t)
{
    return t->size;
}

/* In-order. Mutation 3: O(1) auxiliary space, no recursion. */
void rb_foreach(const rbtree_t *t,
                void (*fn)(const char *key, void *value, void *ctx),
                void *ctx);

/* Returns 0 iff all red-black invariants hold
 * (see the baseline section). */
int rb_validate(const rbtree_t *t);

/* Frees all nodes, key copies, and (if owned) values.
 * Mutation 3: O(1) auxiliary space, no recursion. NULL-safe. */
void rb_destroy(rbtree_t *t);