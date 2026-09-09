#version 330

// Attributi standard di Raylib per le mesh
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;

// Matrice di trasformazione per l'istanza (passata da DrawMeshInstanced)
layout(location = 3) in mat4 instanceTransform;

// Uniform: la matrice MVP (Proiezione * Vista * Modello)
uniform mat4 mvp;

// Output per il fragment shader
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main()
{
    // Calcola la posizione nel mondo
    vec4 worldPos = instanceTransform * vec4(vertexPosition, 1.0);
    fragPosition = worldPos.xyz;
    
    // Passa le coordinate UV
    fragTexCoord = vertexTexCoord;
    
    // Calcola la normale nel mondo (solo rotazione, senza traslazione)
    // Assumiamo che instanceTransform contenga solo traslazione + scala + rotazione
    mat3 normalMatrix = mat3(instanceTransform);
    fragNormal = normalize(normalMatrix * vertexNormal);
    
    // Calcola la posizione finale
    gl_Position = mvp * worldPos;
}