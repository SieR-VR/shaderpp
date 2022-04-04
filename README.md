Shaderpp is a GLSL(shader) code generator library for C++.

It enables integrated development experiment for C++ and GLSL.

# Table of Contents
1. [Requirements](#requirements)
2. [Example](#example)

## Requirements

* C++ 17 or newer

## Coverage

|GLSL Feature|Progress|
|---|---|
|Preprocessor|50% (using preprocessor in C++)|
|Operator priority|100% (as same as C++)|
|Comments|Unavailable|
|Tokens|15%|
|Keywords|10%|
|Types|3% (float, vec2, int)|
|Booleans|0% (Well I don't know how to control if statement)|
|Literals|0%|
|Structures|60%|
|Functions|50%|
|Arrays|0%|
|Implicit Conversions|0%|
|Storage Qualifiers|0%|
|Built-In functions|0%|
|Input/Output Variables|0%|
|Uniform Variables|0%|
|Buffer Variables|0%|


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