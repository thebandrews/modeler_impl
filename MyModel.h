#ifndef __MY_MODEL_HEADER__
#define __MY_MODEL_HEADER__

#pragma warning (disable : 4305)


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
    //ShaderProgram shader;

    //////////////////////////////// PROPERTIES ///////////////////////////////////
    // Switches for spheres

    // Some slider properties
    RangeProperty rotateX, rotateY;

    // Neck
    RangeProperty NeckRotateX, NeckRotateZ;

    // Left Shoulder
    RangeProperty LShoulderRotateX, LShoulderRotateZ;

    // Right Shoulder
    RangeProperty RShoulderRotateX, RShoulderRotateZ;

    // Left Elbow
    RangeProperty LElbowRotateX, LElbowRotateZ;

    // Right Elbow
    RangeProperty RElbowRotateX, RElbowRotateZ;

    // Left Hand
    RangeProperty LHandRotateX, LHandRotateZ;

    // Right Hand
    RangeProperty RHandRotateX, RHandRotateZ;

    //// Waist
    //RangeProperty WaistRotateX, WaistRotateY;

    //// Left Hip
    //RangeProperty LHipRotateX, LHipRotateZ;

    //// Right Hip
    //RangeProperty RHipRotateX, RHipRotateZ;

    //// Left Knee
    //RangeProperty LKneeRotateX, LKneeRotateZ;

    //// Right Knee
    //RangeProperty RKneeRotateX, RKneeRotateZ;

    //// Left Foot
    //RangeProperty LFootRotateX, LFootRotateZ;

    //// Right Foot
    //RangeProperty RFootRotateX, RFootRotateZ;



public:

    /** Construct the scene */
    MyModel() :
        // You have to call the parent class's constructor, to provide a
        // name for the model.
        Model("MyModel"),

        // Construct textures and shaders. 
        // They won't be loaded until the model is drawn for the first time.
        texture("Wood4.png"),

        rotateX("Rotate X", -180, 180, 0, 1),
        rotateY("Rotate Y", -180, 180, 0, 1),

        NeckRotateX("Rotate Neck X", -180, 180, 0, 1),
        NeckRotateZ("Rotate Neck Z", -180, 180, 0, 1),

        LShoulderRotateX("Rotate LShoulder X", -180, 180, 0, 1),
        LShoulderRotateZ("Rotate LShoulder Z", -180, 180, 0, 1),

        RShoulderRotateX("Rotate RShoulder X", -180, 180, 0, 1),
        RShoulderRotateZ("Rotate RShoulder Z", -180, 180, 0, 1),

        LElbowRotateX("Rotate LElbow X", -180, 180, 0, 1),
        LElbowRotateZ("Rotate LElbow Z", -180, 180, 0, 1),

        RElbowRotateX("Rotate RElbow X", -180, 180, 0, 1),
        RElbowRotateZ("Rotate RElbow Z", -180, 180, 0, 1),

        LHandRotateX("Rotate LHand X", -180, 180, 0, 1),
        LHandRotateZ("Rotate LHand Z", -180, 180, 0, 1),

        RHandRotateX("Rotate RHand X", -180, 180, 0, 1),
        RHandRotateZ("Rotate RHand Z", -180, 180, 0, 1)

    {
        // If you have child Models, like the MobileLight model from model.h,
        // you can add their property groups, and they will appear in the list
        // in the top left corner of Modeler, under this model's entry:

        // Finally, add all the properties to this model's PropertyGroup.
        properties.add(&rotateX)
                  .add(&rotateY)
                  .add(&NeckRotateX)
                  .add(&NeckRotateZ)
                  .add(&LShoulderRotateX)
                  .add(&LShoulderRotateZ)
                  .add(&RShoulderRotateX)
                  .add(&RShoulderRotateZ)
                  .add(&LElbowRotateX)
                  .add(&LElbowRotateZ)
                  .add(&RElbowRotateX)
                  .add(&RElbowRotateZ)
                  .add(&LHandRotateX)
                  .add(&LHandRotateZ)
                  .add(&RHandRotateX)
                  .add(&RHandRotateZ);

    }

    //
    // Public methods
    //
    void load();
    void tick();
    void drawModel();
    void draw();
};

#endif