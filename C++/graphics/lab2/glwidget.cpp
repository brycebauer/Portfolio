#include "glwidget.h"
#include <iostream>
#include <sstream>
#include <string>
#include <QtGui/QImage>
#include <cmath>


using namespace std;

GLWidget::GLWidget(const QGLFormat &format, QWidget *parent) : QGLWidget(format, parent) {
    setAutoBufferSwap(false);
}

GLWidget::~GLWidget() {
}

void GLWidget::initializeGL() {
    string delim1 = ",";
    string delim2 = ":";
    string input;
    size_t pos = 0;
    float x1,x2,x3, y1,y2,y3;
    float r1,r2,r3, g1,g2,g3, b1,b2,b3;

    cout << "Plese enter in 3 points\n";
    cout << "All points must be in the format x,y:r,g,b\n";

    // input for the first point
    cout << "Point 1: \n";
    cin >> input;
    pos = input.find(delim1);
    x1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim2);
    y1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    r1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    g1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    b1 = atoi(input.c_str());
    x1 = (-1 + ((x1 * 2) / 640));
    y1 = (1 - ((y1 * 2) /480));

    //input for the second point
    cout << "Point 2: \n";
    cin >> input;
    pos = input.find(delim1);
    x2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim2);
    y2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    r2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    g2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    b2 = atoi(input.c_str());
    x2 = (-1 + ((x2 * 2) / 640));
    y2 = (1 - ((y2 * 2) /480));

    // input for the third point
    cout << "Point 3: \n";
    cin >> input;
    pos = input.find(delim1);
    x3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim2);
    y3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    r3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    g3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    b3 = atoi(input.c_str());
    x3 = (-1 + ((x3 * 2) / 640));
    y3 = (1 - ((y3 * 2) /480));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // position data for a single triangle
    Point pts[3] = {
        Point(x1,y1),
        Point(x2,y2),
        Point(x3,y3)
    };

    // color data for a single triangle
    Color clr[3] = {
        Color(r1,g1,b1),
        Color(r2,g2,b2),
        Color(r3,g3,b3)
    };

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    // Upload the position data to the GPU, storing
    // it in the buffer we just created.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(clr), clr, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders();

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint GLWidget::loadShaders() {
    GLuint program = glCreateProgram();

    const GLchar* vertSource =
        "#version 330\n"
        "in vec2 position;\n"
        "in vec3 color;\n"
        "out vec3 Color;\n"
        "void main() {\n"
        " Color = color;\n"
        " gl_Position = vec4(position.x, position.y, 0, 1);\n"
        "}\n";

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

    const GLchar* fragSource =
        "#version 330\n"
        "in vec3 Color;\n"
        "out vec4 color_out;\n"
        "void main() {\n"
        " color_out = vec4(Color, 1.0);\n"
        "}\n";
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

Point GLWidget::w2nd(Point pt_w) {
    /* convert pt_w to normalized device coordinates */
    /* use this method to convert your input coordinates to
       normalized device coordinates */
}
