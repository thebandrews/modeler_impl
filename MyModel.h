#ifndef __MY_MODEL_HEADER__
#define __MY_MODEL_HEADER__

//#pragma warning (disable : 4305)
//#pragma warning (disable : 4244)
//#pragma warning (disable : 4786)
//#pragma warning (disable : 4312)

#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include <cmath>

class MyModel : public Model {
protected:
    ///////////////////////////////// TEXTURES ////////////////////////////////////
    Texture2D texture;

    ///////////////////////////////// SHADERS /////////////////////////////////////
    ShaderProgram shader;

    //////////////////////////////// PROPERTIES ///////////////////////////////////
    // Switches for spheres
    BooleanProperty useTexture;
    //  for showing/hiding reference unit sphere
    //BooleanProperty showReferenceUnitSphere;

    // Lets you pick what shapes to use for the default model!
    //ChoiceProperty shapeChoice;

    BooleanProperty useShader;

    // Some slider properties
    RangeProperty rotateX, rotateY;

    // Diffuse color picker
    RGBProperty diffuse;


    // Scene lights
    //PointLight pointLight;
    //DirectionalLight directionalLight;


public:

    /** Construct the scene */
    MyModel() :
        // You have to call the parent class's constructor, to provide a
        // name for the model.
        Model("MyModel"),

        // Construct textures and shaders. 
        // They won't be loaded until the model is drawn for the first time.
        texture("checkers.png"),
        shader("shader.vert", "shader.frag", NULL),

        // Call the constructors for the lights
        //pointLight("Point Light", GL_LIGHT1, /**direction part**/ -5, 5, 5, /**diffuse part**/ 1.0, 0.5, 0.5, 
        ///**specular part**/ 1.0, 0.5, 0.5, /**ambient part**/ .2f, 0.1, 0.1 /**attenuation part**/, 0.4, 0.7, 0),
        //directionalLight("Directional Light", GL_LIGHT0, /**direction part**/ 5, 5, 5, /**diffuse part**/ 0.0f, 0.5, 0.5f, 
        ///**specular part**/ 0.0f, 0.5f, 0.5f ),

        // Now, call the constructors for each Property:
        useTexture("Use Checkered Texture", true),
        //showReferenceUnitSphere("Show Reference Unit Sphere", false),
        //shapeChoice("Model Shape:", "Sphere|Cube|Cylinder|Torus|Icosahedron|Teapot|Revolution|My Model", 0),
        useShader("Use My Shader", false),
        rotateX("Rotate X", -180, 180, 0, 1),
        rotateY("Rotate Y", -180, 180, 0, 1),
        diffuse("Diffuse Color", 1.0, 0.7, .4)
    {
        // If you have child Models, like the MobileLight model from model.h,
        // you can add their property groups, and they will appear in the list
        // in the top left corner of Modeler, under this model's entry:
        //properties.add(pointLight.getProperties())
        //    .add(directionalLight.getProperties());

        // Finally, add all the properties to this model's PropertyGroup.
        properties.add(&useTexture)
            .add(&useShader)
            .add(&rotateX)
            .add(&rotateY)
            .add(&diffuse)
            ;

    }

    //
    // Public methods
    //
    void load();
    void tick();
    void drawModel();
    void draw();

    //
    // Draw the various body parts
    //
    void UpperTorso();
    void LowerTorso();
    void Head();
    void UpperLeftArm();
    void UpperRightArm();
    void UpperLeftLeg();
    void UpperRightLeg();
    void LowerLeftArm();
    void LowerRightArm();



};

#endif