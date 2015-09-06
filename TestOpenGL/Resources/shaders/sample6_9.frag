precision mediump float;

uniform float u_radius;
uniform vec3 u_lightLocation;
uniform vec3 u_camera;
varying vec4 v_position;
varying vec3 v_normal;

void pointLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular, in vec3 lightLocation,
                in vec4 lightAmbient, in vec4 lightDiffuse, in vec4 lightSpecular)
{
    ambient = lightAmbient;
    
    vec3 normalTarget = v_position.xyz+normal;
    vec3 newNormal = (CC_MVMatrix*vec4(normalTarget,1)).xyz - (CC_MVMatrix*v_position).xyz;
    newNormal = normalize(newNormal);
    
    vec3 eye = normalize(u_camera-(CC_MVMatrix*v_position).xyz);
    
    vec3 vp = normalize(lightLocation-(CC_MVMatrix*v_position).xyz);
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
    
    vec4 finalColor = vec4(color, 0);
    
    vec4 ambientTemp, diffuseTemp, specularTemp;
    pointLight(normalize(v_position.xyz),ambientTemp,diffuseTemp,specularTemp,u_lightLocation,vec4(0.15,0.15,0.15,1.0),vec4(0.8,0.8,0.8,1.0),vec4(0.7,0.7,0.7,1.0));
    
    gl_FragColor = finalColor * ambientTemp + finalColor * diffuseTemp + finalColor * specularTemp;
}