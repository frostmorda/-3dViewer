attribute  vec3 vertexPos;
varying vec4 fragColor;
uniform vec4 color;
uniform mat4 mvpMatrix;
uniform mat4 projectionMatrix;
uniform float koef;
uniform mat4 transMatrix;
void main(void)
{
    vec4 mypos;
    mypos = projectionMatrix * transMatrix * mvpMatrix * vec4(vertexPos, 1.0);
    gl_Position = vec4(mypos.x * koef, mypos.y, 0, mypos.w);
    fragColor = color;
}
