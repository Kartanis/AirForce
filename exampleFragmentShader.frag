/*----------------- "exampleVertexShader.vert" -----------------*/
 
#version 150 // Указываем версию GLSL, которую мы используем.
 
// in_Position была связана с атрибутом с индексом равным 0 ("shaderAttribute")
in  vec3 in_Position;
 
void main(void) 
{
    gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}
/*--------------------------------------------------------------*/