uniform vec3 u_lightLocation;
uniform vec3 u_camera;
attribute vec4 a_position;
//attribute vec4 a_normal;
varying vec4 v_position;
//varying vec4 v_diffuse;
varying vec4 v_specular;

void pointLight(in vec3 normal, inout vec4 specular, in vec3 lightLocation, in vec4 lightSpecular)
{
    vec3 normalTarget = a_position.xyz+normal;
    vec3 newNormal = (CC_MVMatrix*vec4(normalTarget,1)).xyz - (CC_MVMatrix*a_position).xyz;
    newNormal = normalize(newNormal);
    
    vec3 eye = normalize(u_camera-(CC_MVMatrix*a_position).xyz);
    
    vec3 vp = normalize(lightLocation-(CC_MVMatrix*a_position).xyz);
    vp = normalize(vp);
    
    vec3 halfVector = normalize(vp+eye);
    
    float shininess = 50.0;
    
    float nDotViewHalfVector = dot(newNormal,halfVector);
    
    float powerFactor = max(0.0,pow(nDotViewHalfVector,shininess));
    
    specular = lightSpecular*powerFactor;
}

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_position = a_position;
    
    vec4 specularTemp = vec4(0.0,0.0,0.0,0.0);
    pointLight(normalize(a_position.xyz),specularTemp,u_lightLocation,vec4(0.7,0.7,0.7,1.0));
    v_specular = specularTemp;
}