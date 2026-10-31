
#include "engine.h"
#include <stdlib.h>

#define MAX_NODES 1000

Value *value_create(double data)
{
    Value *v = malloc(sizeof(Value));

    if (v == NULL) {
        return NULL;
    }

    v->data = data;
    v->grad = 0.0;
    v->a = NULL;
    v->b = NULL;
    v->op = '\0';

    return v;
}

Value *value_add(Value *a, Value *b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }

    Value *result = value_create(a->data + b->data);

    if (result == NULL) {
        return NULL;
    }

    result->a = a;
    result->b = b;
    result->op = '+';

    return result;
}

Value *value_mul(Value *a, Value *b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }

    Value *result = value_create(a->data * b->data);

    if (result == NULL) {
        return NULL;
    }

    result->a = a;
    result->b = b;
    result->op = '*';

    return result;
}

static int visited(Value *v, Value *nodes[], int count)
{
    for (int i = 0; i < count; i++) {
        if (nodes[i] == v) {
            return 1;
        }
    }

    return 0;
}

static void build_topology(
    Value *v,
    Value *seen[],
    int *seen_count,
    Value *topo[],
    int *topo_count
)
{
    if (v == NULL || visited(v, seen, *seen_count)) {
        return;
    }

    if (*seen_count >= MAX_NODES ||
        *topo_count >= MAX_NODES) {
        return;
    }

    seen[(*seen_count)++] = v;

    build_topology(v->a, seen, seen_count, topo, topo_count);
    build_topology(v->b, seen, seen_count, topo, topo_count);

    topo[(*topo_count)++] = v;
}

void value_backward(Value *output)
{
    if (output == NULL) {
        return;
    }

    Value *seen[MAX_NODES];
    Value *topo[MAX_NODES];

    int seen_count = 0;
    int topo_count = 0;

    build_topology(
        output,
        seen,
        &seen_count,
        topo,
        &topo_count
    );

    for (int i = 0; i < topo_count; i++) {
        topo[i]->grad = 0.0;
    }

    output->grad = 1.0;

    for (int i = topo_count - 1; i >= 0; i--) {
        Value *v = topo[i];

        if (v->op == '+') {
            v->a->grad += v->grad;
            v->b->grad += v->grad;
        }

        else if (v->op == '*') {
            v->a->grad += v->b->data * v->grad;
            v->b->grad += v->a->data * v->grad;
        }
    }
}

void value_free(Value *v)
{
    free(v);
}
