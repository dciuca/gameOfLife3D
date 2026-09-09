#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in mat4 instanceTransform;

uniform mat4 mvp;

out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main()
{
    vec4 worldPos = instanceTransform * vec4(vertexPosition, 1.0);
    fragPosition = worldPos.xyz;
    fragTexCoord = vertexTexCoord;
    
    mat3 normalMatrix = mat3(instanceTransform);
    fragNormal = normalize(normalMatrix * vertexNormal);
    
    gl_Position = mvp * worldPos;
}