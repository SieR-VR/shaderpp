#include <iostream>
#include <fstream>

#include "core/variable.h"
#include "core/struct.h"

#include "core/internal_functions.h"
#include "core/builder.h"

int main(int argc, char *argv[])
{
    using namespace GLSL;
    Vec4 FragColor("FragColor");

    Vec3 Normal("Normal");
    Vec3 FragPos("FragPos");

    Vec3 lightPos("lightPos");
    Vec3 viewPos("viewPos");
    Vec3 lightColor("lightColor");
    Vec3 objectColor("objectColor");

    std::function<void()> main_func = [&]() {
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
    };

    auto result = GLSL::Builder("460")
        .add_outputs({ FragColor })
        .add_inputs({ Normal, FragPos })
        .add_uniforms({ lightPos, viewPos, lightColor, objectColor })
        .build(main_func);

    std::ofstream out("../sample.frag");
    out << result;

    return 0;
}