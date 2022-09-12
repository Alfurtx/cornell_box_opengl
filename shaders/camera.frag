#version 330 core

out vec4 frag_color;

in VS_OUT {
    vec3 position;
    vec3 normal;
    vec3 color;
    vec4 frag_pos_light_space;
} fs_in;

vec3 light_color = vec3(1.0);

float light_constant  = 1.0f;
float light_linear    = 0.004f;
float light_quadratic = 0.00007f;

uniform vec3 light_position;
uniform vec3 view_position;

uniform bool is_lamp;
uniform bool is_ceiling;

uniform sampler2D depth_map;
uniform float near_plane;
uniform float far_plane;

float
linearize_depth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}

float
shadow_calculations(vec4 frag_pos_light_space)
{
    // float closest_depth = texture(depth_map, proj_coords.xy).r;
    // float current_depth = proj_coords.z;

    // vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
    // proj_coords = proj_coords * 0.5 + 0.5;
    // float closest_depth = linearize_depth(texture(depth_map, proj_coords.xy).r);
    // float current_depth = linearize_depth(proj_coords.z);
    // vec3 normal = normalize(fs_in.normal);
    // vec3 light_direction = normalize(light_position - fs_in.position);
    // float bias = max(30 * (1.0 - dot(normal, light_direction)), 0.005);  
    // float shadow = current_depth - bias > closest_depth ? 1.0 : 0.0;
    // if(proj_coords.z > 1.0) 
    //     shadow = 0.0;
    // return shadow;

    vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
    vec2 UVCoords;
    UVCoords.x = 0.5 * proj_coords.x + 0.5;
    UVCoords.y = 0.5 * proj_coords.y + 0.5;
    float z = 0.5 * proj_coords.z + 0.5;
    float Depth = texture(depth_map, UVCoords).x;
    if (Depth < (z + 0.001))
        return 0.5;
    else
        return 1.0;
}

void
main()
{
    if(is_lamp) {
        frag_color = vec4(1.0);
        return;
    }

    vec3 ambient = 0.01 * light_color;

    vec3 normal = normalize(fs_in.normal);
    vec3 light_direction = normalize(light_position - fs_in.position);
    float diff = max(dot(light_direction, normal), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 view_direction = normalize(view_position - fs_in.position);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec = pow(max(dot(normal, halfway_direction), 0.0), 32.0);
    vec3 specular = spec * light_color;

    float distance = length(light_position - fs_in.position);
    float attenuation = 1.0 / (light_constant + light_linear * distance + light_quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    float shadow = shadow_calculations(fs_in.frag_pos_light_space);
    vec3 result = (ambient + (shadow) * (diffuse + specular)) * fs_in.color;

    if(is_ceiling) {
        result = ambient * fs_in.color;
    }

    frag_color = vec4(result, 1.0);

    // float depth_value = texture(depth_map, fs_in.color.rg).r;
    // frag_color = vec4(vec3(linearize_depth(depth_value) / far_plane), 1.0); // perspective
}







