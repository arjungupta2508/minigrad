from pathlib import Path
from cffi import FFI

ROOT = Path(__file__).resolve().parent
C_SOURCE = ROOT / "src" / "csrc"

ffibuilder = FFI()

ffibuilder.cdef("""
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
""")

ffibuilder.set_source(
    "minigrad._engine",
    '#include "engine.h"',
    sources=[str("src/csrc/engine.c")],
    include_dirs=[str(C_SOURCE)],
)

if __name__ == "__main__":
    ffibuilder.compile(
        tmpdir=str(ROOT),
        verbose=True,
    )