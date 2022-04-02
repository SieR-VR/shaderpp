# shaderpp

# Table of Contents
1. [Requirements](#requirements)
2. [Example](#example)

## Requirements

* C++ 17 or newer

## Example

C++ Code:
```c++
std::function<Float(Float&, Float&)> func = [](Float& a0, Float& a1) {
    return a0 * a1;
}

auto func_parsed = Parse(func, "func");
```

Auto Generated GLSL Code:
```glsl
func(float a0, float a1);

func(float a0, float a1) {
    return a0 * a1;
}
```