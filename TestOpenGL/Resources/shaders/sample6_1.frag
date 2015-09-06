precision mediump float;

varying vec4 v_position;
uniform float u_radius;

void main()
{
	vec3 color;
	float n = 8.0;
	float span = 2.0*u_radius/n;

	int i = int((v_position.x + u_radius)/span);
	int j = int((v_position.y + u_radius)/span);
	int k = int((v_position.z + u_radius)/span);
	int whichColor = int(mod(float(i+j+k),2.0));

	if(whichColor == 1){
		color = vec3(0.678,0.231,0.129);
	}else{
		color = vec3(1.0,1.0,1.0);
	}

    gl_FragColor = vec4(color,0);
}
