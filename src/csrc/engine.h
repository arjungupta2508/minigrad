
#ifndef ENGINE_H
#define ENGINE_H

typedef struct Value {
    double data;
    double grad;

    struct Value *a;
    struct Value *b;

    char op;
} Value;

Value *value_create(double data);

Value *value_add(Value *a, Value *b);
Value *value_mul(Value *a, Value *b);

void value_backward(Value *output);

void value_free(Value *v);

#endif
