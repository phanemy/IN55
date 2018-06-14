#version 330

const int MAX_JOINTS = 50;//max joints allowed in a skeleton
const int MAX_WEIGHTS = 3;//max number of joints that can affect a vertex

in vec3 in_position;
in vec3 in_color;
in vec3 in_jointIndices;
in vec3 in_weights;
in vec3 in_normal;
in vec2 in_textureCoords;

const vec3 weights = vec3(1,0,0);
const vec3 test = vec3(0,0,0);
const vec3 test1 = vec3(1,0,0);
const vec3 testx = vec3(1,-1,-1);
const vec3 testy = vec3(-1,1,-1);
const vec3 testz = vec3(-1,-1,1);

out vec3 fColor;
out vec2 pass_textureCoords;
out vec3 pass_normal;

uniform mat4 jointTransforms[MAX_JOINTS];
uniform mat4 mvp;

void main(void){

        vec4 totalLocalPos = vec4(0.0);
        vec4 totalNormal = vec4(0.0);
        gl_PointSize = 10.0;
        for(int i=0;i<MAX_WEIGHTS;i++){
            mat4 jointTransform = jointTransforms[int(in_jointIndices[i])];
//            mat4 jointTransform = jointTransforms[0];
                vec4 posePosition = jointTransform * vec4(in_position, 1.0);
                totalLocalPos += posePosition * in_weights[i];

                vec4 worldNormal = jointTransform * vec4(in_normal.xyz, 1.0);
                totalNormal += worldNormal * in_weights[i];
        }

        gl_Position = mvp * vec4(totalLocalPos.xyz,1);
//        gl_Position = mvp * totalLocalPos;

//        gl_Position = mvp * vec4(in_position,1.0);
        pass_normal = totalNormal.xyz;
//        fColor = vec3(1,1,1);

        pass_textureCoords = in_textureCoords;

//        fColor = vec3(1,1,1);



//        if(in_position.x < -0.9 && in_position.y > 0.9 && in_position.z <-0.9)
//            fColor = vec3(0,1,0);

//        if(in_position.x < -0.9 && in_position.y < -0.9 && in_position.z >0.9)
//            fColor = vec3(0,0,1);

//        if(in_position.x < -0.9 && in_position.y < -0.9 && in_position.z < -0.9)
//            fColor = vec3(0,1,1);

        if(in_jointIndices == test)
            fColor = vec3(0,1,1);
        else if(in_jointIndices == test1)
            fColor = vec3(1,0,1);
        else
            fColor = in_jointIndices.xyz;

//        if(in_position.x > 0.9 && in_position.y > 0.9 && in_position.z >0.9)
//            fColor = vec3(1,1,1);
}
