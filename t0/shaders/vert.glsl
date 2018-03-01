#version 330 core

layout (location=0) in vec3 pos;
layout (location=2) in vec2 texCoord;

out vec2 pTexCoord;

uniform mat4 uCam;
uniform mat4 uModel;

void main(){
    gl_Position = uCam*uModel*vec4(pos, 1.0f);
    pTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}
