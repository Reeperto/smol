# Smol

Smol is a template library for C++ intended to achieve a couple goals

- Be small and self contained whenever possible
- Be understandable and readable (with comments for documentation and explanations)
- Provide a partial alternative to the STL
- Provide new data structures or classes the STL doesn't offer

# Building

To build Smol, you will need

- C++20 capable compiler
- `premake`
- `gtest` for testing

Generating the compilation files is as simple as running premake with the action you want. For example to make `make` files run

```bash
premake5 gmake
```
