# MiniGrad

**A lightweight automatic differentiation library powered by C and Python.**

MiniGrad is an experimental automatic differentiation engine that combines a C-based computation engine with a Python interface.

## Features

- C-powered computation graph
- Automatic differentiation using reverse-mode backpropagation
- Python interface through CFFI
- Basic arithmetic operations: addition and multiplication
- Gradient computation with `backward()`

## Installation

Clone the repository:

```bash
git clone (https://github.com/arjungupta2508/minigrad.git)
cd minigrad
```

Install MiniGrad:

```bash
pip install .
```

## Quick Start

```python
import minigrad

x = minigrad.Value(2.0)
y = minigrad.Value(3.0)

z = x * y + x

z.backward()

print(z.data)  # 8.0
print(x.grad)  # 4.0
print(y.grad)  # 2.0
```

## How It Works

MiniGrad uses a C-based computation graph to store mathematical operations. Its Python interface provides a simple way to construct expressions and calculate gradients through reverse-mode automatic differentiation.

## Project Structure

```text
minigrad/
├── src/
│   ├── csrc/
│   │   ├── engine.c
│   │   └── engine.h
│   └── minigrad/
│       ├── __init__.py
│       └── core.py
├── build.py
├── setup.py
└── pyproject.toml
```

## Current Limitations

MiniGrad is an early experimental project.

- Supports addition and multiplication only.
- Uses a fixed computation graph capacity.
- Memory ownership and cleanup are not yet fully implemented.
- Has not been extensively tested across platforms.

Do not use it for production workloads yet.

## License

MIT License.
