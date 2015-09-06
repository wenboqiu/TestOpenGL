attribute vec4 a_position;
varying vec4 v_position;
varying vec3 v_normal;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_position = a_position;
    v_normal = a_position.xyz;
}


