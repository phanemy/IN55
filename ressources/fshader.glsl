#version 150

const vec2 lightBias = vec2(0.7, 0.6);//just indicates the balance between diffuse and ambient lighting
const vec3 lightDirection = vec3(1, -1,1);
in vec2 pass_textureCoords;
in vec3 pass_normal;

out vec4 out_colour;

uniform sampler2D diffuseMap;

void main(void){

        vec4 diffuseColour = texture2D(diffuseMap, pass_textureCoords);
        vec3 unitNormal = normalize(pass_normal);
        float diffuseLight = max(dot(-lightDirection, unitNormal), 0.0) * lightBias.x + lightBias.y;
        out_colour = vec4((diffuseColour * diffuseLight).xyz,1.0);
}

