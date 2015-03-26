#include "glwidget.h"
#include <iostream>

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QTextStream>

using namespace std;
using glm::vec2;
using glm::ortho;
using glm::inverse;

float red = 0.0, green = 0.0, blue = 0.0;
int choice = 1;

GLWidget::GLWidget(char* imagepath, QWidget *parent) : QOpenGLWidget(parent), outline(false), drawMode(0), image(imagepath) {
    num_pts = 0;
    num_mode = 0;
    drawMode = GL_TRIANGLES;
    ptSize = 1.0f;
}

GLWidget::~GLWidget() {
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    glBindVertexArray(vao);
    glUseProgram(program1);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPointSize(1.0f);

    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    //GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a buffer on the GPU for position data
    glGenBuffers(1, &positionBuffer);
    // Create a buffer on the GPU for color data
    glGenBuffers(1, &colorBuffer);

    // Upload the position, and color data to the GPU, storing
    // it in the buffer we just allocated.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders();
    program1 = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "position");
    uniformLoc = glGetUniformLocation(program, "projection");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
}


void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_C:
            glBindVertexArray(vao);
            glUseProgram(program1);
            cout << "Cleared all the points. Make sure to "
                    "update this once you modify how the points "
                    "are stored." << endl;
            pts.clear();
            num_pts = 0;
            ptClr.clear();
            glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
            glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
            break;

        case Qt::Key_Up:
            ptSize = ptSize + 1.0f;
            cout << ptSize << endl;
            break;

        case Qt::Key_Down:
            if (ptSize > 1.0){
                ptSize = ptSize - 1.0f;
                cout << ptSize << endl;
            }
            break;

        case Qt::Key_T:
            choice = 1;
            break;

        case Qt::Key_B:
            choice = 2;
            break;

        case Qt::Key_S:
            choice = 3;
            break;

        case Qt::Key_P:
            choice = 4;
            break;

        case Qt::Key_N:
            choice = 5;
            break;

        case Qt::Key_H:
            choice = 6;
            break;

        case Qt::Key_Space:
                pts.clear();
                num_pts = 0;
                ptClr.clear();
                for(int i = 0; i <= 960; i = i + ptSize)
                {
                    for(int j = 0; j <= 540; j = j + ptSize)
                    {
                        QRgb tempColorRgb = image.pixel(i,j);
                        QColor tempColor(tempColorRgb);
                        red = tempColor.red() / 255.0;
                        green = tempColor.green() / 255.0;
                        blue = tempColor.blue() / 255.0;
                        fill(i, j, red, blue, green);
                    }
                }
    update();
}
    update();
}

void GLWidget::fill(int x, int y, float red, float blue, float green){
    vec3 rgb = vec3(red, green, blue);
    vec2 top;
    vec2 bottom;
    vec2 bottom_left;
    vec2 bottom_right;
    vec2 top_right;
    vec2 top_left;
    vec2 radius1;
    vec2 radius2;
    vec2 radius3;
    vec2 radius4;
    vec2 center;
    vec2 circ1;
    vec2 circ2;

    switch(choice)
    {
        case 2:
            top_right = vec2((x + (ptSize/2.0)),(y - (ptSize/2.0)));
            top_left = vec2((x - (ptSize/2.0)),(y - (ptSize/2.0)));
            bottom_right = vec2((x + (ptSize/2.0)),(y + (ptSize/2.0)));
            bottom_left = vec2((x - (ptSize/2.0)),(y + (ptSize/2.0)));
            pts.push_back(top_left);
            ptClr.push_back(rgb);
            pts.push_back(top_right);
            ptClr.push_back(rgb);
            pts.push_back(bottom_left);
            ptClr.push_back(rgb);
            pts.push_back(bottom_left);
            ptClr.push_back(rgb);
            pts.push_back(top_right);
            ptClr.push_back(rgb);
            pts.push_back(bottom_right);
            ptClr.push_back(rgb);
            num_pts = num_pts + 6;
            break;
        case 3:
            center = vec2(x,y);
            for(int i = 0; i <= 360; i=i+2)
            {
                radius1 = vec2((x+((ptSize / 2.0)*(sin(i)))),(y+((ptSize / 2.0)*(cos(i)))));
                radius2 = vec2((x+((ptSize / 2.0)*(sin(i+1)))),(y+((ptSize / 2.0)*(cos(i+1)))));
                pts.push_back(center);
                ptClr.push_back(rgb);
                pts.push_back(radius1);
                ptClr.push_back(rgb);
                pts.push_back(radius2);
                ptClr.push_back(rgb);
                num_pts = num_pts + 3;
            }
            break;
        case 4:
            center = vec2(x,y);
            for(int i = 0; i < 5; i++)
            {
                radius1 = vec2((x+((ptSize / 2.0)*(sin(i)))),(y+((ptSize / 2.0)*(cos(i)))));
                radius2 = vec2((x+((ptSize / 2.0)*(sin(i+1)))),(y+((ptSize / 2.0)*(cos(i+1)))));
                pts.push_back(center);
                ptClr.push_back(rgb);
                pts.push_back(radius1);
                ptClr.push_back(rgb);
                pts.push_back(radius2);
                ptClr.push_back(rgb);
                num_pts = num_pts + 3;
            }
            break;
        case 5:
            center = vec2(x,y);
            for(int i = 0; i < 6; i=i+2)
            {
                radius1 = vec2((x+((ptSize / 2.0)*(sin(i)))),(y+((ptSize / 2.0)*(cos(i)))));
                radius2 = vec2((x+((ptSize / 2.0)*(sin(i+1)))),(y+((ptSize / 2.0)*(cos(i+1)))));
                pts.push_back(center);
                ptClr.push_back(rgb);
                pts.push_back(radius1);
                ptClr.push_back(rgb);
                pts.push_back(radius2);
                ptClr.push_back(rgb);
                num_pts = num_pts + 3;
            }
            break;

        case 6:
            center = vec2(x,y);
            //top = vec2(x,(y - ((ptSize * 2.0) / 3.0)));
            bottom_left = vec2((x + ((ptSize * 1.723) / 3.0)),(y + ((ptSize * 2.0) / 3.0)));
            bottom_right = vec2((x - ((ptSize * 1.723) / 3.0)),(y + ((ptSize * 2.0) / 3.0)));
            top_left = vec2((x + ((ptSize * 1.723) / 3.0)),(y - ((ptSize * 2.0) / 3.0)));
            top_right = vec2((x - ((ptSize * 1.723) / 3.0)),(y - ((ptSize * 2.0) / 3.0)));
            pts.push_back(center);
            ptClr.push_back(rgb);
            pts.push_back(bottom_left);
            ptClr.push_back(rgb);
            pts.push_back(bottom_right);
            ptClr.push_back(rgb);
            pts.push_back(center);
            ptClr.push_back(rgb);
            pts.push_back(top_left);
            ptClr.push_back(rgb);
            pts.push_back(top_right);
            ptClr.push_back(rgb);
            num_pts = num_pts + 6;
            break;

        default:
            top = vec2(x,(y - ((ptSize * 2.0) / 3.0)));
            bottom_left = vec2((x + ((ptSize * 1.723) / 3.0)),(y + ((ptSize * 2.0) / 3.0)));
            bottom_right = vec2((x - ((ptSize * 1.723) / 3.0)),(y + ((ptSize * 2.0) / 3.0)));
            pts.push_back(top);
            ptClr.push_back(rgb);
            pts.push_back(bottom_left);
            ptClr.push_back(rgb);
            pts.push_back(bottom_right);
            ptClr.push_back(rgb);
            num_pts = num_pts + 3;
            break;
    }
    glBindVertexArray(vao);
    glUseProgram(program1);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, num_pts*sizeof(vec2), &pts[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, num_pts*sizeof(vec3), &ptClr[0], GL_DYNAMIC_DRAW);
    update();

}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    QRgb tempColorRgb = image.pixel(event->x(), event->y());
            QColor tempColor(tempColorRgb);
            red = tempColor.red()/255.0;
            green = tempColor.green()/255.0;
            blue = tempColor.blue()/255.0;
            int x = event->x();
            int y = event->y();
            fill(x, y, red, blue, green);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    QRgb tempColorRgb = image.pixel(event->x(), event->y());
            QColor tempColor(tempColorRgb);
            red = tempColor.red()/255.0;
            green = tempColor.green()/255.0;
            blue = tempColor.blue()/255.0;
            int x = event->x();
            int y = event->y();
            fill(x, y, red, blue, green);
}


void GLWidget::resizeGL(int w, int h) {
//    float AspectRatio = h / w;
    glViewport(0, 0,w,h);
    //glUseProgram(program1);
    width = w;
    heigth = h;

    glBindVertexArray(vao);
    glUseProgram(program1);
/*
    glm::mat4 projection = glm::ortho(-1.f, 1.f, -(AspectRatio),AspectRatio);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(projection));
*/
    glm::mat4 matrix = glm::mat4(
        glm::vec4(2.f/width, 0, 0, 0),
        glm::vec4(0, -2.f/heigth, 0, 0),
        glm::vec4(0, 0, 1.f, 0),
        glm::vec4(-1.0f, 1.0f, 0, 1.f));
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(matrix));

    // When our OpenGL context is resized, we need to change
    // our projection matrix to match. Create an orthographic
    // projection matrix that converts window coordinates to normalized
    // device coordinates.  This is similar to our previous lab,
    // except the conversion will happen in our vertex shader.
    // This way we won't need to do any conversions on our mouse
    // event coordinates and when we resize the window the geometry
    // won't be scaled unevenly.
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program1);
    // draw primitives based on the current draw mode
    glDrawArrays(drawMode, 0, num_pts);

    // draw points so we can always see them
    // glPointSize adjusts the size of point
    // primitives
    glDrawArrays(GL_POINTS, 0, num_pts);
}

// Copied from LoadShaders.cpp in the the oglpg-8th-edition.zip
// file provided by the OpenGL Programming Guide, 8th edition.
const GLchar* GLWidget::readShader(const char* filename) {
#ifdef WIN32
        FILE* infile;
        fopen_s( &infile, filename, "rb" );
#else
    FILE* infile = fopen( filename, "rb" );
#endif // WIN32

    if ( !infile ) {
#ifdef _DEBUG
        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
#endif /* DEBUG */
        return NULL;
    }

    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET );

    GLchar* source = new GLchar[len+1];

    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    return const_cast<const GLchar*>(source);
}

GLuint GLWidget::loadShaders() {
    GLuint program = glCreateProgram();

    // read vertex shader from Qt resource file
    QFile vertFile(":/vert.glsl");
    vertFile.open(QFile::ReadOnly | QFile::Text);
    QString vertString;
    QTextStream vertStream(&vertFile);
    vertString.append(vertStream.readAll());
    string vertSTLString = vertString.toStdString();

    cout << "Vertex Shader:" << endl;
    cout << vertSTLString << endl;

    const GLchar* vertSource = vertSTLString.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    {
        GLint compiled;
        glGetShaderiv( vertShader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            GLsizei len;
            glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( vertShader, len, &len, log );
            std::cout << "Shader compilation failed: " << log << std::endl;
            delete [] log;
        }
    }
    glAttachShader(program, vertShader);

    // read fragment shader from Qt resource file
    QFile fragFile(":/frag.glsl");
    fragFile.open(QFile::ReadOnly | QFile::Text);
    QString fragString;
    QTextStream fragStream(&fragFile);
    fragString.append(fragStream.readAll());
    string fragSTLString = fragString.toStdString();

    cout << "Fragment Shader:" << endl;
    cout << fragSTLString << endl;

    const GLchar* fragSource = fragSTLString.c_str();

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    {
        GLint compiled;
        glGetShaderiv( fragShader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            GLsizei len;
            glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( fragShader, len, &len, log );
            std::cerr << "Shader compilation failed: " << log << std::endl;
            delete [] log;
        }
    }
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glUseProgram(program);

    return program;
}
