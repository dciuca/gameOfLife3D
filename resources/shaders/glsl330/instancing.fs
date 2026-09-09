#version 330

// Input dal vertex shader
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;

// Uniform: colore del cubo
uniform vec4 cubeColor = vec4(0.2, 0.5, 0.8, 1.0);

// Output: colore finale
out vec4 finalColor;

void main()
{
    // Luce fissa dall'alto a destra
    vec3 lightPos = vec3(10.0, 15.0, 10.0);
    vec3 lightDir = normalize(lightPos - fragPosition);
    
    // Calcola la normale (già normalizzata nel vertex shader)
    vec3 normal = normalize(fragNormal);
    
    // Illuminazione diffusa (Lambert)
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Luce ambiente
    float ambient = 0.3;
    float brightness = ambient + diff * 0.7;
    
    // Colore finale
    finalColor = vec4(cubeColor.rgb * brightness, cubeColor.a);
}