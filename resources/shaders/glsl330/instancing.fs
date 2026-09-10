#version 330

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;

uniform vec4 cubeColor = vec4(0.2, 0.6, 1.0, 1.0);
uniform vec3 lightPos;

out vec4 finalColor;

void main()
{
    // Calcoli luce
    vec3 lightDir = normalize(lightPos - fragPosition);
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(vec3(0.0) - fragPosition);
    
    // Diffusa
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Speculare - REGOLA LA LUCENTEZZA QUI!
    vec3 halfDir = normalize(lightDir + viewDir);
    
    // 🔆 Più basso = più lucido (riflesso più ampio)
    // 🔆 Più alto = meno lucido (riflesso più concentrato)
    float shininess = 64.0;  // Prova: 8, 16, 32, 64
    
    float spec = pow(max(dot(normal, halfDir), 0.0), shininess);
    
    // 🔆 Intensità della luce speculare (0.0 = opaco, 1.0 = molto lucido)
    float specIntensity = 1.0;  // Prova: 0.0, 0.5, 1.0, 1.5
    
    // Illuminazione
    float ambient = 0.25;
    float brightness = ambient + diff * 0.65 + spec * specIntensity * 0.8;
    
    // Colore con tinta calda
    vec3 lightColor = vec3(1.0, 0.95, 0.9);
    vec3 finalColorRGB = cubeColor.rgb * brightness * lightColor;
    
    // Gamma correction
    finalColorRGB = pow(finalColorRGB, vec3(1.0 / 2.2));

    // EXPERIMENTAL: aggiungi bordo
    // 🟢 Aggiungi il bordo usando le coordinate UV
    // Più vicino al bordo della faccia, più scuro
    // vec2 uv = fragTexCoord;
    // float borderWidth = 0.01;
    // float border = 0.5;
    // // Controlla se siamo vicino al bordo della texture
    // if (uv.x < borderWidth || uv.x > 1.0 - borderWidth ||
    //     uv.y < borderWidth || uv.y > 1.0 - borderWidth)
    // {
    //     border = 0.1;  // Scuro per il bordo
    // }
    // finalColorRGB *= border;
    
    finalColor = vec4(finalColorRGB, cubeColor.a);
}