uniform vec3 u_lightLocation;
attribute vec4 a_position;
//attribute vec4 a_normal;
varying vec4 v_position;
varying vec4 v_diffuse;

void pointLight(in vec3 normal, inout vec4 diffuse, in vec3 lightLocation, in vec4 lightDiffuse)
{
    vec3 normalTarget = a_position.xyz+normal;
    vec3 newNormal = (CC_MVMatrix*vec4(normalTarget,1)).xyz - (CC_MVMatrix*a_position).xyz;
    newNormal = normalize(newNormal);
    
    vec3 vp = normalize(lightLocation-(CC_MVMatrix*a_position).xyz);
    vp = normalize(vp);
    
    float nDotViewPosition = max(0.0,dot(newNormal,vp));
    diffuse = lightDiffuse*nDotViewPosition;
}

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_position = a_position;
    
    vec4 diffuseTemp = vec4(0.0,0.0,0.0,0.0);
    pointLight(normalize(a_position.xyz),diffuseTemp,u_lightLocation,vec4(0.8,0.8,0.8,1.0));
    v_diffuse = diffuseTemp;
}