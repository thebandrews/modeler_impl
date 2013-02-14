varying vec3 normal, vVertex;

void main (void)
{
    // The scene's ambient light.
    vec4 final_color = gl_LightModel.ambient * gl_FrontMaterial.ambient;;

    // Since the vertex is in eye space, the direction to the
    // viewer is simply the normalized vector from v to the
    // origin.
    vec3 Viewer = -normalize(vVertex);

    // The normal vectors is generally not normalized after being
    // interpolated across a triangle.  Here we normalize it.
    vec3 N = normalize(normal);


    ///////////////////////////////////////////////////////////////////////////
    //
    // Directional Light Computations
    //
    ///////////////////////////////////////////////////////////////////////////

    // Get the lighting direction and normalize it.
    vec3 DirectionalLight  = normalize(gl_LightSource[0].position.xyz);

    // Compute halfway vector
    vec3 Half = normalize(Viewer+DirectionalLight);

    // Compute factor to prevent light leakage from below the
    // surface
    float lambertTerm1 = dot(N, DirectionalLight);

    //
    // Compute Ambient
    //
    final_color += gl_FrontLightProduct[0].ambient;

    //
    // Compute Diffuse
    //
    float diffuseShade = max(lambertTerm1, 0.0);
    final_color += diffuseShade * gl_FrontLightProduct[0].diffuse;

    //
    // Compute Specular
    //
    if(lambertTerm1 > 0.0)
    {
        float specularShade = pow(max(dot(Half, N), 0.0), gl_FrontMaterial.shininess);
        final_color += specularShade * gl_FrontLightProduct[0].specular;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    // Point Light Computations
    //
    ///////////////////////////////////////////////////////////////////////////
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
    final_color += (gl_FrontLightProduct[1].ambient)*att;

    // Normalize the lighting direction.
    vec3 L = normalize(lightDir);

    // Compute factor to prevent light leakage from below the
    // surface
    float lambertTerm2 = dot(N,L);

    if(lambertTerm2 > 0.0)
    {
        //
        // Compute Diffuse
        //
        final_color += (gl_LightSource[1].diffuse*gl_FrontMaterial.diffuse*lambertTerm2)*att;

        //
        // Compute Specular
        //
        vec3 Light  = normalize(lightDir);

        // Compute halfway vector
        vec3 Half = normalize(Viewer+Light);

        float specular = pow(max(dot(Half, N), 0.0), gl_FrontMaterial.shininess);
        final_color += (specular*gl_FrontLightProduct[1].specular)*att;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    // Spot Light Computations
    //
    ///////////////////////////////////////////////////////////////////////////
    float spotEffect;

    vec3 spotLightDir = vec3(gl_LightSource[2].position.xyz - vVertex);

    // Compute distance to the light source
    float spotDist = length(spotLightDir);

    // Normalize the lighting direction.
    vec3 L2 = normalize(spotLightDir);

    // Compute factor to prevent light leakage from below the
    // surface
    float lambertTerm3 = max(dot(N,L2), 0.0);

    if (lambertTerm3 > 0.0) {
        spotEffect = dot(normalize(gl_LightSource[2].spotDirection), normalize(-spotLightDir));

        if (spotEffect > gl_LightSource[2].spotCosCutoff) 
        {
            spotEffect = pow(spotEffect, gl_LightSource[2].spotExponent);
            float att = spotEffect / ( gl_LightSource[2].constantAttenuation + 
                (gl_LightSource[2].linearAttenuation*spotDist) + 
                (gl_LightSource[2].quadraticAttenuation*spotDist*spotDist) );

            //
            // Compute Diffuse
            //
            final_color += (gl_LightSource[2].diffuse*gl_FrontMaterial.diffuse*lambertTerm3)*att;

            //
            // Compute Specular
            //
            vec3 spotLight  = normalize(spotLightDir);

            // Compute halfway vector
            vec3 spotHalf = normalize(Viewer+spotLight);

            float spotSpecular = pow(max(dot(spotHalf, N), 0.0), gl_FrontMaterial.shininess);
            final_color += (spotSpecular*gl_FrontLightProduct[2].specular)*att;
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    final_color += gl_FrontMaterial.emission;

    gl_FragColor = final_color;
}