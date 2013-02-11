varying vec3 normal, vVertex;

void main (void)
{
    vec4 final_color;
    vec4 diffuse;

    vec3 lightDir = vec3(gl_LightSource[1].position.xyz - vVertex);
    vec3 eyeVec = -vVertex;
    
    float d = length(lightDir);

    //
    // Compute Attenuation
    //
    float att = 1.0 / ( gl_LightSource[1].constantAttenuation + 
                        (gl_LightSource[1].linearAttenuation*d) + 
                        (gl_LightSource[1].quadraticAttenuation*d*d) );

    //
    // Compute Ambient
    //
    final_color = gl_LightModel.ambient * gl_FrontMaterial.ambient;
    final_color += (gl_FrontLightProduct[1].ambient)*att;


    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);
    
    float lambertTerm = dot(N,L);

    if(lambertTerm > 0.0)
    {
        //
        // Compute Diffuse
        //
        final_color += (gl_LightSource[1].diffuse*gl_FrontMaterial.diffuse*lambertTerm)*att;

        //
        // Compute Specular
        //
        vec3 Viewer = -normalize(vVertex);
        vec3 Light  = normalize(lightDir);

        // Compute halfway vector
        vec3 Half = normalize(Viewer+Light);

        float specular = pow(max(dot(Half, N), 0.0), gl_FrontMaterial.shininess);
        final_color += (specular*gl_FrontLightProduct[1].specular)*att;
    }

    final_color += gl_FrontMaterial.emission;

    gl_FragColor = final_color;
}