uniform vec3 u_lightLocation;
uniform vec3 u_camera;
attribute vec4 a_position;
//attribute vec4 a_normal;
varying vec4 v_position;
varying vec4 v_ambient;
varying vec4 v_diffuse;
varying vec4 v_specular;

void pointLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular, in vec3 lightLocation,
                                in vec4 lightAmbient, in vec4 lightDiffuse, in vec4 lightSpecular)
{
    ambient = lightAmbient;
    
    vec3 normalTarget = a_position.xyz+normal;
    vec3 newNormal = (CC_MVMatrix*vec4(normalTarget,1)).xyz - (CC_MVMatrix*a_position).xyz;
    newNormal = normalize(newNormal);
    
    vec3 eye = normalize(u_camera-(CC_MVMatrix*a_position).xyz);
    
    vec3 vp = normalize(lightLocation-(CC_MVMatrix*a_position).xyz);
    vp = normalize(vp);
    
    float nDotViewPosition = max(0.0,dot(newNormal,vp));
    diffuse = lightDiffuse*nDotViewPosition;
    
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
    
    vec4 ambientTemp, diffuseTemp, specularTemp;
    pointLight(normalize(a_position.xyz),ambientTemp,diffuseTemp,specularTemp,u_lightLocation,vec4(0.15,0.15,0.15,1.0),vec4(0.8,0.8,0.8,1.0),vec4(0.7,0.7,0.7,1.0));
    
    v_ambient = ambientTemp;
    v_diffuse = diffuseTemp;
    v_specular = specularTemp;
}