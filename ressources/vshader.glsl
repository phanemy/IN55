#version 330

const int MAX_BONES = 50;//max bones allowed in a skeleton
const int MAX_WEIGHTS = 3;//max number of bones that can affect a vertex

in vec3 in_position;
in vec3 in_color;
in vec3 in_boneIndices;
in vec3 in_weights;
in vec3 in_normal;
in vec2 in_textureCoords;

const vec3 weights = vec3(1,0,0);
const vec3 test = vec3(0,0,0);
const vec3 test1 = vec3(1,0,0);
const vec3 testx = vec3(1,-1,-1);
const vec3 testy = vec3(-1,1,-1);
const vec3 testz = vec3(-1,-1,1);

out vec2 pass_textureCoords;
out vec3 pass_normal;

uniform mat4 bonesTransforms[MAX_BONES];
uniform mat4 mvp;

void main(void){

        vec4 totalLocalPos = vec4(0.0);
        vec4 totalNormal = vec4(0.0);
        gl_PointSize = 10.0;
        for(int i=0;i<MAX_WEIGHTS;i++){
            mat4 bonesTransform = bonesTransforms[int(in_boneIndices[i])];
                vec4 posePosition = bonesTransform * vec4(in_position, 1.0);
                totalLocalPos += posePosition * in_weights[i];

                vec4 worldNormal = bonesTransform * vec4(in_normal.xyz, 1.0);
                totalNormal += worldNormal * in_weights[i];
        }

        gl_Position = mvp * vec4(totalLocalPos.xyz,1);
        pass_normal = totalNormal.xyz;
        pass_textureCoords = in_textureCoords;
}
