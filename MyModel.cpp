// The sample box model.  You should build a file
// very similar to this for when you make your model in
// order to plug in to the animator project.

#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning (disable : 4786)
#pragma warning (disable : 4312)

#include "MyModel.h"





/**
* Modeler calls this method once an OpenGL context becomes available,
* (which happens before the first time draw() is called), and whenever
* you click the "Reload Textures and Shaders" menu option.
*
* Make sure you call the load() methods of each of your textures and
* shaders here.
*/
void MyModel::load() {
    texture.load();
    shader.load();
}

/**
* Modeler calls this method many times a second when the Animate
* checkbox is checked.
*/
void MyModel::tick() {
    // You can put code here to increment animation counters for
    // extra credit.
}

/** Draw the model. */
void MyModel::drawModel() {

    int divisions=16;
    switch(ModelerDrawState::Instance()->m_quality)
    {
    case HIGH: 
        divisions = 64; break;
    case MEDIUM: 
        divisions = 20; break;
    case LOW:
        divisions = 12; break;
    case POOR:
        divisions = 8; break;
    }

    // Remember our current modelview matrix, which is in world space.
    glPushMatrix();

    // Rotate around the X-axis
    glRotatef(rotateX.getValue(), 1, 0, 0);

    // Rotate around the Y-axis
    glRotatef(rotateY.getValue(), 0, 1, 0);

    // Waist
    drawSphere(0.5);

    // Lower Torso
    glPushMatrix();
    glTranslatef(0.0,-1.95,0.0);
    drawRevolution("LowerTorso.apts",1);

    // Upper Left Leg Joint
    glPushMatrix();
    glTranslatef(-0.3,0.85,0);
    drawSphere(0.22);
    glPopMatrix(); // Upper Left Leg Joint

    // Upper Right Leg Joint
    glPushMatrix();
    glTranslatef(0.3,0.85,0);
    drawSphere(0.22);
    glPopMatrix(); // Upper Right Leg Joint

    glPopMatrix(); // Lower Torso

    // Upper Torso
    glPushMatrix();
    glTranslatef(0.0,-1.55,0.0);
    drawRevolution("torso2.apts",1);

    // Neck
    glPushMatrix();
    glTranslatef(0,3.4,0);
    drawSphere(0.25);

    // Head
    glPushMatrix();
    glTranslatef(0,-0.9,0);
    drawRevolution("head.apts",1);
    glPopMatrix(); // Head
    glPopMatrix(); // Neck

    // Upper Left Arm Joint
    glPushMatrix();
    glTranslatef(-0.92,2.9,0);
    drawSphere(0.2);

    // Upper Left Arm
    glPushMatrix();
    glTranslatef(0,-3.3,0);
    drawRevolution("UpperArm.apts",1);

    // Lower Left Arm Joint
    glPushMatrix();
    glTranslatef(0,1.9,0);
    drawSphere(0.15);

    // Lower Left Arm
    glPushMatrix();
    glTranslatef(0,-3.3,0);
    drawRevolution("LowerArm.apts",1);
    glPopMatrix(); // Lower Left Arm

    glPopMatrix(); // Lower Left Arm Joint
    glPopMatrix(); // Upper Left Arm
    glPopMatrix(); // Upper Left Arm Joint

    // Upper Right Arm Joint
    glPushMatrix();
    glTranslatef(0.92,2.9,0);
    drawSphere(0.2);

    // Upper Right Arm
    glPushMatrix();
    glTranslatef(0,-3.3,0);
    drawRevolution("UpperArm.apts",1);

    // Lower Right Arm Joint
    glPushMatrix();
    glTranslatef(0,1.9,0);
    drawSphere(0.15);

    // Lower Right Arm
    glPushMatrix();
    glTranslatef(0,-3.3,0);
    drawRevolution("LowerArm.apts",1);
    glPopMatrix(); // Lower Right Arm

    glPopMatrix(); // Lower Right Arm Joint
    glPopMatrix(); // Upper Right Arm
    glPopMatrix(); // Upper Right Arm Joint

    glPopMatrix(); // Upper Torso

    // Go back to "world space"
    glPopMatrix();

    

}

/** Draw the scene. */
void MyModel::draw() {

    // Use the texture if desired.
    //if (useTexture.getValue()) {
        texture.use();
    /*} else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }*/

    // Use the shader if desired.
    if (useShader.getValue()) {
        shader.use();
    }

    // Call a class method that draws our model.
    drawModel();
    // Stop applying shaders to objects.
    // This if-statement makes sure that glUseProgram is not a null
    // function pointer (which it will be if GLEW couldn't initialize).
    if (glUseProgram) {
        glUseProgram(0);
    }

    // Stop applying textures to objects
    glBindTexture(GL_TEXTURE_2D, 0);
}

//
// Draw Upper torso
//
void MyModel::UpperTorso()
{

}
