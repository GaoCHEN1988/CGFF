#version 440

layout (location = 0) out vec4 color;

in DATA
{
	vec4 fragPosition;
	vec4 color;
	vec3 normal;
} fs_in;

struct Light {

    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 sys_CameraPosition;
uniform vec3 u_color;

void main()
{
	Light light;
	light.direction = vec3(0.2f, -1.0f, 0.3f);
	light.ambient = vec3(0.4f, 0.4f, 0.4f);
	light.diffuse = vec3(0.6f, 0.6f, 0.6f);
	light.specular = vec3(1.0f, 1.0f, 1.0f);
	

	// ambient
    //vec3 ambient = light.ambient * fs_in.color.rgb;
    vec3 ambient = light.ambient * u_color;
  	
    // diffuse 
    vec3 norm = normalize(fs_in.normal);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * fs_in.color.rgb;  
    
    // specular
    vec3 viewDir = normalize(sys_CameraPosition - fs_in.fragPosition.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0f);
    vec3 specular = light.specular * spec * fs_in.color.rgb;  
        
    vec3 result = ambient + diffuse;
    color = vec4(result, fs_in.color.a);
};
