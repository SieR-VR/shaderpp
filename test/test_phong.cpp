#include <iostream>
#include <fstream>

#include "variable.h"
#include "struct.h"

#include "internal_functions.h"
#include "program.h"
#include "uniform.h"

class Phong : public GLSL::Shader
{
    GLSL::Output<GLSL::Vec4> FragColor;

    GLSL::Input<GLSL::Vec3> Normal;
    GLSL::Input<GLSL::Vec3> FragPos;

public:
    GLSL::Uniform<GLSL::Vec3> lightPos;
    GLSL::Uniform<GLSL::Vec3> viewPos;
    GLSL::Uniform<GLSL::Vec3> lightColor;
    GLSL::Uniform<GLSL::Vec3> objectColor;

    Phong()
        : GLSL::Shader("300", "es"),
          FragColor("FragColor", this),
          Normal("Normal", this),
          FragPos("FragPos", this),
          lightPos("lightPos", this),
          viewPos("viewPos", this),
          lightColor("lightColor", this),
          objectColor("objectColor", this)
    {
    }

    void main() {
        using namespace GLSL;

        Float ambientStrength = 0.1;
        Vec3 ambient = lightColor * ambientStrength;

        Vec3 norm = normalize(Normal);
        Vec3 lightDir = normalize(lightPos - FragPos);
        Float diff = max(dot(norm, lightDir), 0);
        Vec3 diffuse = lightColor * diff;

        Float specularStrength = 0.5;
        Vec3 viewDir = normalize(viewPos - FragPos);
        Vec3 reflectDir = reflect(-lightDir, norm);
        Float spec = pow(max(dot(viewDir, reflectDir), 0), 32);

        Vec3 specular = lightColor * specularStrength * spec;

        Vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = Vec4(result.x, result.y, result.z, 1);
    }
};

int main(int argc, char *argv[])
{
    Phong shader;
    shader.compile();
    
    std::cout << shader.source;
    return 0;
}