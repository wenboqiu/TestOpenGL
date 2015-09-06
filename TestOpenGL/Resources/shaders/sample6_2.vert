attribute vec4 a_position;
varying vec4 v_position;
varying vec4 v_ambient;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_position = a_position;
    v_ambient = vec4(0.15,0.15,0.15,1.0);
}