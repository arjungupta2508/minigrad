
from . import _engine


class Value:
    def __init__(self, data):
        self._ptr = _engine.lib.value_create(float(data))

        if self._ptr == _engine.ffi.NULL:
            raise MemoryError("Could not allocate Value")

    @property
    def data(self):
        return self._ptr.data

    @property
    def grad(self):
        return self._ptr.grad

    def __repr__(self):
        return f"Value(data={self.data}, grad={self.grad})"
    
    def backward(self):
        _engine.lib.value_backward(self._ptr)
        
    def __add__(self, other):
        if not isinstance(other, Value):
            other = Value(other)

        result = Value.__new__(Value)
        result._ptr = _engine.lib.value_add(
            self._ptr,
            other._ptr
        )

        if result._ptr == _engine.ffi.NULL:
            raise MemoryError("Could not create addition result")

        return result

    def __mul__(self, other):
        if not isinstance(other, Value):
            other = Value(other)

        result = Value.__new__(Value)
        result._ptr = _engine.lib.value_mul(
            self._ptr,
            other._ptr
        )

        if result._ptr == _engine.ffi.NULL:
            raise MemoryError("Could not create multiplication result")
        
        

        return result
    
    
