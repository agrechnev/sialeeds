#version 330 core

in vec2 pTexCoord;

out vec4 color;

uniform sampler2D uTex1;
uniform sampler2D uTex2;
uniform float uMix;

void main(){
    color = mix(texture(uTex1, pTexCoord), texture(uTex2, pTexCoord), uMix);
}
