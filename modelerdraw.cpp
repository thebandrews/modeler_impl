#include "modelerdraw.h"
#include <FL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

// Helper functions from the red book so we can print text on the
// screen.
GLubyte space[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
GLubyte letters[][13] = {
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
    {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
    {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
    {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

GLuint fontOffset;

void makeRasterFont(void)
{
    GLuint i, j;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 8);

    fontOffset = glGenLists (128);
    for (i = 0,j = 'A'; i < 26; i++,j++) {
        glNewList(fontOffset + j, GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
        glEndList();
    }
    glNewList(fontOffset + ' ', GL_COMPILE);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
    glEndList();
}

void printString(char *s)
{
    static bool haveInitialized = false;
    if( !haveInitialized ) {
        makeRasterFont();
        haveInitialized = true;
    }
    glPushAttrib (GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
    glPopAttrib ();
}

// ********************************************************
// Support functions from previous version of modeler
// ********************************************************
static void _dump_current_modelview( void )
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    if (mds->m_rayFile == NULL)
    {
        fprintf(stderr, "No .ray file opened for writing, bailing out.\n");
        exit(-1);
    }

    GLdouble mv[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, mv );
    fprintf( mds->m_rayFile, 
        "transform(\n\t(%f, %f, %f, %f),\n\t(%f, %f, %f, %f),\n\t(%f, %f, %f, %f),\n\t(%f, %f, %f, %f),\n",
        mv[0], mv[4], mv[8], mv[12],
        mv[1], mv[5], mv[9], mv[13],
        mv[2], mv[6], mv[10], mv[14],
        mv[3], mv[7], mv[11], mv[15] );
}

static void _dump_current_material( void )
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    if (mds->m_rayFile == NULL)
    {
        fprintf(stderr, "No .ray file opened for writing, bailing out.\n");
        exit(-1);
    }

    fprintf( mds->m_rayFile, 
        "material={\n\tdiffuse = (%f, %f, %f);\n\tambient = (%f, %f, %f);\n\tspecular = (%f, %f, %f);\n\tshininess = %f; }\n",
        mds->m_diffuseColor[0], mds->m_diffuseColor[1], mds->m_diffuseColor[2], 
        mds->m_ambientColor[0], mds->m_ambientColor[1], mds->m_ambientColor[2],
        mds->m_specularColor[0], mds->m_specularColor[1], mds->m_specularColor[2],
        mds->m_shininess);
}

// ****************************************************************************

// Initially assign singleton instance to NULL
ModelerDrawState* ModelerDrawState::m_instance = NULL;

ModelerDrawState::ModelerDrawState() : m_drawMode(NORMAL), m_quality(MEDIUM),
    showMarkers(false)
{
    float grey[]  = {.5f, .5f, .5f, 1};
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};

    memcpy(m_ambientColor, black, 4 * sizeof(float));
    memcpy(m_diffuseColor, grey, 4 * sizeof(float));
    memcpy(m_specularColor, white, 4 * sizeof(float));

    m_shininess = 5.5;

    m_rayFile = NULL;
}

// CLASS ModelerDrawState METHODS
ModelerDrawState* ModelerDrawState::Instance()
{
    // Return the singleton if it exists, otherwise, create it
    return (m_instance) ? (m_instance) : m_instance = new ModelerDrawState();
}

// ****************************************************************************
// Modeler functions for your use
// ****************************************************************************
// Set the current material properties

void setAmbientColor(float r, float g, float b)
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    mds->m_ambientColor[0] = (GLfloat)r;
    mds->m_ambientColor[1] = (GLfloat)g;
    mds->m_ambientColor[2] = (GLfloat)b;
    mds->m_ambientColor[3] = (GLfloat)1.0;

    if (mds->m_drawMode == NORMAL)
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mds->m_ambientColor);
}

void setEmissiveColor(float r, float g, float b)
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    mds->m_emissiveColor[0] = (GLfloat)r;
    mds->m_emissiveColor[1] = (GLfloat)g;
    mds->m_emissiveColor[2] = (GLfloat)b;
    mds->m_emissiveColor[3] = (GLfloat)1.0;

    if (mds->m_drawMode == NORMAL)
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mds->m_emissiveColor);
}

void setDiffuseColor(float r, float g, float b)
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    mds->m_diffuseColor[0] = (GLfloat)r;
    mds->m_diffuseColor[1] = (GLfloat)g;
    mds->m_diffuseColor[2] = (GLfloat)b;
    mds->m_diffuseColor[3] = (GLfloat)1.0;

    if (mds->m_drawMode == NORMAL)
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mds->m_diffuseColor);
    else
        glColor3f(r,g,b);
}

void setSpecularColor(float r, float g, float b)
{	
    ModelerDrawState *mds = ModelerDrawState::Instance();

    mds->m_specularColor[0] = (GLfloat)r;
    mds->m_specularColor[1] = (GLfloat)g;
    mds->m_specularColor[2] = (GLfloat)b;
    mds->m_specularColor[3] = (GLfloat)1.0;

    if (mds->m_drawMode == NORMAL)
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mds->m_specularColor);
}

void setShininess(float s)
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    mds->m_shininess = (GLfloat)s;

    if (mds->m_drawMode == NORMAL)
        glMaterialf( GL_FRONT, GL_SHININESS, mds->m_shininess);
}

void setDrawMode(DrawModeSetting_t drawMode)
{
    ModelerDrawState::Instance()->m_drawMode = drawMode;
}

void setQuality(QualitySetting_t quality)
{
    ModelerDrawState::Instance()->m_quality = quality;
}

bool openRayFile(const char rayFileName[])
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    fprintf(stderr, "Warning: Ray file may render differently.\n");

    if (!rayFileName)
        return false;

    if (mds->m_rayFile) 
        closeRayFile();

    //mds->m_rayFile = fopen(rayFileName, "w");
    mds->m_rayFile = NULL;
    fopen_s(&(mds->m_rayFile), rayFileName, "w");

    if (mds->m_rayFile != NULL) 
    {
        /*
        fprintf( mds->m_rayFile, "SBT-raytracer 1.0\n\n" );
        fprintf( mds->m_rayFile, "camera { fov=30; position=(0,0.8,5); direction=(0,-0.8,-5); }\n\n" );
        fprintf( mds->m_rayFile, 
        "directional_light { direction=(-1,-2,-1); color=(0.7,0.7,0.7); }\n\n" );
        */

        fprintf( mds->m_rayFile, "SBT-raytracer 1.0\n\n" );

        return true;
    }
    else
        return false;
}

static void _setupOpenGl()
{
    ModelerDrawState *mds = ModelerDrawState::Instance();
    switch (mds->m_drawMode)
    {
    case NORMAL:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glShadeModel(GL_SMOOTH);
        break;
    case FLATSHADE:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glShadeModel(GL_FLAT);
        break;
    case WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glShadeModel(GL_FLAT);
    default:
        break;
    }

}

void closeRayFile()
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    if (mds->m_rayFile) 
        fclose(mds->m_rayFile);

    mds->m_rayFile = NULL;
}

void drawAxes()
{
    // Draw the origin
    glPushMatrix();
    glScalef(5,5,5);

    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    // x axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3d( 0.0, 0.0, 0.0 );
    glVertex3d( 1.0, 0.0, 0.0 );

    // y axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3d( 0.0, 0.0, 0.0 );
    glVertex3d( 0.0, 1.0, 0.0 );

    // z axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3d( 0.0, 0.0, 0.0 );
    glVertex3d( 0.0, 0.0, 1.0 );
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f(1.2f, 0.0f, 0.0f);
    printString("X");

    glColor3f(0.0, 1, 0.0);
    glRasterPos3f(0.0f, 1.2f, 0.0f);
    printString("Y");

    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos3f(0.0f, 0.0f, 1.2f);
    printString("Z");

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void drawSphere(double r)
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    _setupOpenGl();

    if (mds->m_rayFile)
    {
        _dump_current_modelview();
        fprintf(mds->m_rayFile, "scale(%f,%f,%f,sphere {\n", r, r, r );
        _dump_current_material();
        fprintf(mds->m_rayFile, "}))\n\n" );
    }
    else
    {
        int divisions; 
        switch(mds->m_quality)
        {
        case HIGH: 
            divisions = 128; break;
        case MEDIUM: 
            divisions = 32; break;
        case LOW:
            divisions = 16; break;
        case POOR:
            divisions = 8; break;
        }

        GLUquadricObj* gluq = gluNewQuadric();
        gluQuadricDrawStyle( gluq, GLU_FILL );
        gluQuadricNormals( gluq, GLU_SMOOTH );
        glShadeModel(GL_SMOOTH);
        gluQuadricTexture( gluq, GL_TRUE );

        gluSphere(gluq, r, divisions, divisions);

        glShadeModel(GL_SMOOTH);
        gluDeleteQuadric( gluq );
    }
}

int load_2dcurve_txt(const char* filename,std::vector<Point2d>* pts) {
    std::ifstream infile( filename );
    if ( infile.is_open() ) {

        pts->clear();

        float x,y;
        while ( (infile >> x) && (infile >> y) ) {
            Point2d p;
            p.x = x;
            p.y = y;
            pts->push_back( p );
        }
        infile.close();
    } else {
        return -1;
    }

    return 0;
}


std::vector<Point2d> revolution_pts;

int reload_curve_file(const char* filename) {
    int load_ret = load_2dcurve_txt( filename, &revolution_pts );
    if ( load_ret < 0 ) {
        printf( "Cannot open curve file: %s.\n", filename );
    }

    return load_ret;
}

void init_load_curve_file() {
    int load_ret = load_2dcurve_txt( "curves/sample1_curve.apts", &revolution_pts );
    if ( load_ret < 0 ) {
        printf( "Cannot open curve file.\n" );
        return;
    }
}

void drawRevolution(double scale)
{
    if ( revolution_pts.empty() ) {
        return;
    }
    ModelerDrawState *mds = ModelerDrawState::Instance();

    _setupOpenGl();

    if (mds->m_rayFile)
    {
        // write into rayfile
    }
    else
    {
        //
        // Number of bands in the rotation
        //
        int divisions; 
        switch(mds->m_quality)
        {
        case HIGH: 
            divisions = 128; break;
        case MEDIUM: 
            divisions = 32; break;
        case LOW:
            divisions = 16; break;
        case POOR:
            divisions = 8; break;
        }

        const float PI = 3.14159265f;

        float origin_y = 1.0;
        float origin_z = -3.0f;

        int num_pts = revolution_pts.size();

        float * vertices = new float[12*num_pts*360];
        float * normals = new float[12*num_pts*360];
        int * indices = new int[6*num_pts*360];
        float * texture_uv = new float[8*num_pts*360];

        int v_idx = 0;
        int n_idx = 0;
        int i_idx = 0;
        int t_idx = 0;

        int idx_offset = 0;

        int step_size = 360 / divisions;

        //
        // Rotate around the y-axis in chunks of step_size. For each step compute triangle matrix
        // consisting of 4 points. Also, at each vertex compute normals and texture coordinates.
        //
        // This implementation uses glDrawElements
        //
        for(int i = 0; i < 360; i += step_size)
        {
            float radian = i * (PI / 180);

            for ( int j=1; j<num_pts; ++ j ) {

                //
                // Compute Pt #1
                //
                float size1 = (float)(revolution_pts[j-1].x * scale);
                vertices[v_idx++] = cos(radian)*(size1);
                vertices[v_idx++] = (float)(revolution_pts[j-1].y * scale + origin_y);
                vertices[v_idx++] = sin(radian)*(size1);
                normals[n_idx++] = 0;
                normals[n_idx++] = 1;
                normals[n_idx++] = 0;
                texture_uv[t_idx++] = 1.0;
                texture_uv[t_idx++] = 1.0;

                //
                // Compute Pt #2
                //
                float size2 = (float)(revolution_pts[j].x * scale);
                vertices[v_idx++] = cos(radian)*(size2);
                vertices[v_idx++] = (float)(revolution_pts[j].y * scale + origin_y);
                vertices[v_idx++] = sin(radian)*(size2);
                normals[n_idx++] = 0;
                normals[n_idx++] = 1;
                normals[n_idx++] = 0;
                texture_uv[t_idx++] = 1.0;
                texture_uv[t_idx++] = 1.0;

                //
                // Ensure that surface of revolution does not overlap.
                //
                float temp_radian;
                if(i + step_size > 360)
                {
                    temp_radian = 0;
                }
                else
                {
                    temp_radian = (i + step_size) * (PI / 180);
                }

                //
                // Compute Pt #3
                //
                vertices[v_idx++] = cos(temp_radian)*(size1);
                vertices[v_idx++] = vertices[v_idx - 6];
                vertices[v_idx++] = sin(temp_radian)*(size1);

                normals[n_idx++] = 0;
                normals[n_idx++] = 1;
                normals[n_idx++] = 0;

                texture_uv[t_idx++] = 1.0;
                texture_uv[t_idx++] = 1.0;


                //
                // Compute Pt #4
                //
                vertices[v_idx++] = cos(temp_radian)*(size2);
                vertices[v_idx++] = vertices[v_idx - 6];
                vertices[v_idx++] = sin(temp_radian)*(size2);

                normals[n_idx++] = 0;
                normals[n_idx++] = 1;
                normals[n_idx++] = 0;

                texture_uv[t_idx++] = 1.0;
                texture_uv[t_idx++] = 1.0;


                //
                // Setup indices matrix
                //
                indices[i_idx++] = 0 + idx_offset;
                indices[i_idx++] = 1 + idx_offset;
                indices[i_idx++] = 3 + idx_offset;

                indices[i_idx++] = 0 + idx_offset;
                indices[i_idx++] = 3 + idx_offset;
                indices[i_idx++] = 2 + idx_offset;

                //
                // We add 4 points to the vertices array each pass
                // so increment the offset by 4.
                //
                idx_offset += 4;
            }
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        //glEnableClientState(GL_NORMAL_ARRAY);
        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        //glNormalPointer(GL_FLOAT,0,normals);
        //glTexCoordPointer(2,GL_FLOAT,0,texture_uv);
        glDrawElements(GL_TRIANGLES, i_idx, GL_UNSIGNED_INT, indices);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);


        //
        // Clean up
        //
        delete [] vertices;
        delete [] normals;
        delete [] indices;
        delete [] texture_uv;
    }
}


void drawBox( double x, double y, double z )
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    _setupOpenGl();

    if (mds->m_rayFile)
    {
        _dump_current_modelview();
        fprintf(mds->m_rayFile,  
            "scale(%f,%f,%f,translate(0.5,0.5,0.5,box {\n", x, y, z );
        _dump_current_material();
        fprintf(mds->m_rayFile,  "})))\n\n" );
    }
    else
    {
        /* remember which matrix mode OpenGL was in. */
        int savemode;
        glGetIntegerv( GL_MATRIX_MODE, &savemode );

        /* switch to the model matrix and scale by x,y,z. */
        glMatrixMode( GL_MODELVIEW );

        glPushMatrix();
        glScaled( x, y, z );

        glBegin( GL_QUADS );

        glNormal3d( 0.0, 0.0, -1.0 );
        glVertex3d( 0.0, 0.0, 0.0 );
        glVertex3d( 0.0, 1.0, 0.0 );
        glVertex3d( 1.0, 1.0, 0.0 );
        glVertex3d( 1.0, 0.0, 0.0 );

        glNormal3d( 0.0, -1.0, 0.0 );
        glVertex3d( 0.0, 0.0, 0.0 );
        glVertex3d( 1.0, 0.0, 0.0 );
        glVertex3d( 1.0, 0.0, 1.0 );
        glVertex3d( 0.0, 0.0, 1.0 );

        glNormal3d( -1.0, 0.0, 0.0 );
        glVertex3d( 0.0, 0.0, 0.0 );
        glVertex3d( 0.0, 0.0, 1.0 );
        glVertex3d( 0.0, 1.0, 1.0 );
        glVertex3d( 0.0, 1.0, 0.0 );

        glNormal3d( 0.0, 0.0, 1.0 );
        glVertex3d( 0.0, 0.0, 1.0 );
        glVertex3d( 1.0, 0.0, 1.0 );
        glVertex3d( 1.0, 1.0, 1.0 );
        glVertex3d( 0.0, 1.0, 1.0 );

        glNormal3d( 0.0, 1.0, 0.0 );
        glVertex3d( 0.0, 1.0, 0.0 );
        glVertex3d( 0.0, 1.0, 1.0 );
        glVertex3d( 1.0, 1.0, 1.0 );
        glVertex3d( 1.0, 1.0, 0.0 );

        glNormal3d( 1.0, 0.0, 0.0 );
        glVertex3d( 1.0, 0.0, 0.0 );
        glVertex3d( 1.0, 1.0, 0.0 );
        glVertex3d( 1.0, 1.0, 1.0 );
        glVertex3d( 1.0, 0.0, 1.0 );

        glEnd();

        /* restore the model matrix stack, and switch back to the matrix
        mode we were in. */
        glPopMatrix();
        glMatrixMode( savemode );
    }
}

void drawCylinder( double h, double r1, double r2 )
{
    ModelerDrawState *mds = ModelerDrawState::Instance();
    int divisions;

    _setupOpenGl();

    switch(mds->m_quality)
    {
    case HIGH: 
        divisions = 32; break;
    case MEDIUM: 
        divisions = 20; break;
    case LOW:
        divisions = 12; break;
    case POOR:
        divisions = 8; break;
    }

    if (mds->m_rayFile)
    {
        _dump_current_modelview();
        fprintf(mds->m_rayFile, 
            "cone { height=%f; bottom_radius=%f; top_radius=%f; capped = true; \n", h, r1, r2 );
        _dump_current_material();
        fprintf(mds->m_rayFile, "})\n\n" );
    }
    else
    {
        //////// BEGIN YOUR CYLINDER CODE /////////
        // ... if you are replacing the cylinder.
        GLUquadricObj* gluq;

        /* GLU will again do the work.  draw the sides of the cylinder. */
        gluq = gluNewQuadric();
        gluQuadricDrawStyle( gluq, GLU_FILL );
        gluQuadricTexture( gluq, GL_TRUE );
        gluCylinder( gluq, r1, r2, h, divisions, divisions);
        gluDeleteQuadric( gluq );

        if ( r1 > 0.0 )
        {
            /* if the r1 end does not come to a point, draw a flat disk to
            cover it up. */

            gluq = gluNewQuadric();
            gluQuadricDrawStyle( gluq, GLU_FILL );
            gluQuadricTexture( gluq, GL_TRUE );
            gluQuadricOrientation( gluq, GLU_INSIDE );
            gluDisk( gluq, 0.0, r1, divisions, divisions);
            gluDeleteQuadric( gluq );
        }

        if ( r2 > 0.0 )
        {
            /* if the r2 end does not come to a point, draw a flat disk to
            cover it up. */

            /* save the current matrix mode. */	
            int savemode;
            glGetIntegerv( GL_MATRIX_MODE, &savemode );

            /* translate the origin to the other end of the cylinder. */
            glMatrixMode( GL_MODELVIEW );
            glPushMatrix();
            glTranslated( 0.0, 0.0, h );

            /* draw a disk centered at the new origin. */
            gluq = gluNewQuadric();
            gluQuadricDrawStyle( gluq, GLU_FILL );
            gluQuadricTexture( gluq, GL_TRUE );
            gluQuadricOrientation( gluq, GLU_OUTSIDE );
            gluDisk( gluq, 0.0, r2, divisions, divisions);
            gluDeleteQuadric( gluq );

            /* restore the matrix stack and mode. */
            glPopMatrix();
            glMatrixMode( savemode );
        }
        //////// END YOUR CYLINDER CODE /////////
    }
}

// In opengl, triangles have a "front" and "back".  This is for
// efficiency purposes.  You will want to make sure that you
// specify the vertices (x1,y1,z1), (x2,y2,z2), (x3,y3,z3) in
// *counterclockwise* order.
void drawTriangle( double x1, double y1, double z1,
                  double x2, double y2, double z2,
                  double x3, double y3, double z3 )
{
    ModelerDrawState *mds = ModelerDrawState::Instance();

    _setupOpenGl();

    if (mds->m_rayFile)
    {
        _dump_current_modelview();
        fprintf(mds->m_rayFile, 
            "polymesh { points=((%f,%f,%f),(%f,%f,%f),(%f,%f,%f)); faces=((0,1,2));\n", x1, y1, z1, x2, y2, z2, x3, y3, z3 );
        _dump_current_material();
        fprintf(mds->m_rayFile, "})\n\n" );
    }
    else
    {
        double a, b, c, d, e, f;

        /* the normal to the triangle is the cross product of two of its edges. */
        a = x2-x1;
        b = y2-y1;
        c = z2-z1;

        d = x3-x1;
        e = y3-y1;
        f = z3-z1;

        glBegin( GL_TRIANGLES );
        glNormal3d( b*f - c*e, c*d - a*f, a*e - b*d );
        glVertex3d( x1, y1, z1 );
        glVertex3d( x2, y2, z2 );
        glVertex3d( x3, y3, z3 );
        glEnd();
    }
}

