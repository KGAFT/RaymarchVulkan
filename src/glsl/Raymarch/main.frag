#version 450 core

#define FOV 1.0
#define MAX_STEPS 256
#define MAX_DIST 500
#define EPSILON 0.001


layout(location = 0) in vec2 tr;
layout(location = 0) out vec4 FragColor;

layout(push_constant) uniform CodeInput{
    vec2 resolution;
} host_input;

vec2 map(vec3 p){

    p = mod(p, 4.0)-4.0*0.5;
    float sphereDistance = length(p) - 1;
    float sphereId = 1;
    vec2 sphere = vec2(sphereDistance, sphereId);
    return sphere;
}

vec2 marchRay(vec3 origin, vec3 direction){
    vec2 hit, object;
    for(int i = 0; i<MAX_STEPS; i++){
        vec3 p = origin+object.x*direction;
        hit = map(p);
        object.x+=hit.x;
        object.y = hit.y;
        if(abs(hit.x)<EPSILON || object.x>MAX_DIST) break;
    }
    return object;
}

vec3 render(vec2 uv){
    vec3 res = vec3(0);
    vec3 rayOrigin = vec3(0.0f,0.0f,-3.0f);
    vec3 rayDirection = normalize(vec3(uv, FOV));
    vec2 object = marchRay(rayOrigin, rayDirection);

    if(object.x < MAX_DIST){
        res+=3.0/object.x;
    }

    return res;
}

void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    
    vec2 uv = (2.0*fragCoord-host_input.resolution)/host_input.resolution.y;
    uv.y*=-1;
    FragColor = vec4(render(uv),  1.0f);
}