#include "glwidget.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QTextStream>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

using glm::inverse;
using glm::vec2;
using glm::vec3;
using glm::mat4;
using glm::perspective;
using glm::normalize;
using glm::length;
using glm::cross;
using glm::dot;
using glm::rotate;
using glm::value_ptr;
using glm::lookAt;

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    sx = 1;
    sy = 1;
    sz = 1;
    rowSize = 1;
    colSize = 1;
    totRotation = mat4(1.0f);
    wallType = 1;
    xspace = .5;
    yspace = .5;
    zspace = .5;
}

GLWidget::~GLWidget() {
}

void GLWidget::initializeGrid() {
    glGenVertexArrays(1, &gridVao);
    glBindVertexArray(gridVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    vec3 pts[84];
    for(int i = -10; i <= 10; i++) {

        pts[2*(i+10)] = vec3(i, -.5f, 10);
        pts[2*(i+10)+1] = vec3(i, -.5f, -10);

        pts[2*(i+10)+42] = vec3(10,-.5f, i);
        pts[2*(i+10)+43] = vec3(-10,-.5f, i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/grid_vert.glsl", ":/grid_frag.glsl");
    glUseProgram(program);
    gridProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    gridProjMatrixLoc = glGetUniformLocation(program, "projection");
    gridViewMatrixLoc = glGetUniformLocation(program, "view");
    gridModelMatrixLoc = glGetUniformLocation(program, "modelGrid");
}

void GLWidget::initializeCube() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &cubeVao);
    glBindVertexArray(cubeVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);

    vec3 pts[] = {
        // top
        vec3(.5,.5,.5),    // 0
        vec3(.5,.5,-.5),   // 1
        vec3(-.5,.5,-.5),  // 2
        vec3(-.5,.5,.5),   // 3

        // bottom
        vec3(.5,-.5,.5),   // 4
        vec3(-.5,-.5,.5),  // 5
        vec3(-.5,-.5,-.5), // 6
        vec3(.5,-.5,-.5),  // 7

        // front
        vec3(.5,.5,.5),    // 8
        vec3(-.5,.5,.5),   // 9
        vec3(-.5,-.5,.5),  // 10
        vec3(.5,-.5,.5),   // 11

        // back
        vec3(-.5,-.5,-.5), // 12
        vec3(-.5,.5,-.5),  // 13
        vec3(.5,.5,-.5),   // 14
        vec3(.5,-.5,-.5),  // 15

        // right
        vec3(.5,-.5,.5),   // 16
        vec3(.5,-.5,-.5),  // 17
        vec3(.5,.5,-.5),   // 18
        vec3(.5,.5,.5),     // 19

        // left
        vec3(-.5,-.5,.5),  // 20
        vec3(-.5,.5,.5),   // 21
        vec3(-.5,.5,-.5),  // 22
        vec3(-.5,-.5,-.5) // 23

    };

    for(int i = 0; i < 24; i++) {
        pts[i] *= .5;
    }

    vec3 colors[] = {
        // top
        vec3(0,1,0),
        vec3(0,1,0),
        vec3(0,1,0),
        vec3(0,1,0),

        // bottom
        vec3(0,.5f,0),
        vec3(0,.5f,0),
        vec3(0,.5f,0),
        vec3(0,.5f,0),

        // front
        vec3(0,0,.75f),
        vec3(0,0,.75f),
        vec3(0,0,.75f),
        vec3(0,0,.75f),

        // back
        vec3(0,0,.75f),
        vec3(0,0,.75f),
        vec3(0,0,.75f),
        vec3(0,0,.75f),

        // right
        vec3(.75f,0,0),
        vec3(.75f,0,0),
        vec3(.75f,0,0),
        vec3(.75f,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec3 normal[] = {
        // top
        vec3(0,1,0),
        vec3(0,1,0),
        vec3(0,1,0),
        vec3(0,1,0),

        // bottom
        vec3(0,-1,0),
        vec3(0,-1,0),
        vec3(0,-1,0),
        vec3(0,-1,0),

        // front
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,-1),
        vec3(0,0,-1),
        vec3(0,0,-1),
        vec3(0,0,-1),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(-1,0,0),
        vec3(-1,0,0),
        vec3(-1,0,0),
        vec3(-1,0,0)
    };

    //vec3 lightPos = vec3(0, 10, 0);

    GLuint restart = 0xFFFFFFFF;
    GLuint indices[] = {
        0,1,2,3, restart,
        4,5,6,7, restart,
        8,9,10,11, restart,
        12,13,14,15, restart,
        16,17,18,19, restart,
        20,21,22,23
    };

    // Upload the position data to the GPU, storing
    // it in the buffer we just allocated.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/vert.glsl", ":/frag.glsl");
    glUseProgram(program);
    cubeProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    GLint normalIndex = glGetAttribLocation(program, "normal");
    glEnableVertexAttribArray(normalIndex);
    glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    cubeProjMatrixLoc = glGetUniformLocation(program, "projection");
    cubeViewMatrixLoc = glGetUniformLocation(program, "view");
    cubeModelMatrixLoc = glGetUniformLocation(program, "model");
    lightPosition = glGetUniformLocation(program, "lightPos");
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPointSize(4.0f);

    glEnable(GL_DEPTH_TEST);
    GLuint restart = 0xFFFFFFFF;
    glPrimitiveRestartIndex(restart);
    glEnable(GL_PRIMITIVE_RESTART);

    initializeCube();
    initializeGrid();
}

void GLWidget::resizeGL(int w, int h) {
    width = w;
    height = h;

    float aspect = (float)w/h;

    projMatrix = perspective(45.0f, aspect, 1.0f, 100.0f);
    viewMatrix = lookAt(vec3(0,0,-10),vec3(0,0,0),vec3(0,1,0));
    modelMatrix = mat4(1.0f);

    glUseProgram(cubeProg);
    glUniformMatrix4fv(cubeProjMatrixLoc, 1, false, value_ptr(projMatrix));
    glUniformMatrix4fv(cubeViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(cubeModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(gridProg);
    glUniformMatrix4fv(gridProjMatrixLoc, 1, false, value_ptr(projMatrix));
    glUniformMatrix4fv(gridViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(gridModelMatrixLoc, 1, false, value_ptr(modelMatrix));
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (wallType){

        case 1:
            renderCube(modelMatrix);
            break;

        case 2:
            for (int i = 0; i < rowSize; i++){
                float l = i * yspace;
                for (int j = 0; j < colSize; j++){
                    float k = j * xspace;
                    transform = glm::translate(modelMatrix, vec3(k,l,0));
                    renderCube(transform);
                }
            }
            break;
        case 3:
            for (int i = 0; i < rowSize; i++){
                float l = i * yspace;
                if(i == (rowSize - 1)){
                    for (int j = 0; j < colSize; j+=2){
                        float k = j * xspace;
                        transform = glm::translate(modelMatrix, vec3(k,l,0));
                        renderCube(transform);
                    }
                    /*float k = 0 * xspace;
                    transform = glm::translate(modelMatrix, vec3(k,l,0));
                    renderCube(transform);
                    k = 2 * xspace;
                    transform = glm::translate(modelMatrix, vec3(k,l,0));
                    renderCube(transform);
                    k = 4 * xspace;
                    transform = glm::translate(modelMatrix, vec3(k,l,0));
                    renderCube(transform);*/
                }
                else{
                    for (int j = 0; j < colSize; j++){
                        float k = j * xspace;
                        transform = glm::translate(modelMatrix, vec3(k,l,0));
                        renderCube(transform);
                    }
                }
            }
            break;

        case 4:
            for (int z = 0; z < 5; z++){
                float x = z * zspace;
                if(z == 0 || z == 4){
                    for (int i = 0; i < rowSize; i++){
                        float l = i * yspace;
                        if(i == (rowSize - 1)){
                            for (int j = 0; j < 5; j+=2){
                                float k = j * xspace;
                                transform = glm::translate(modelMatrix, vec3(k,l,x));
                                renderCube(transform);
                            }
                        }
                        else{
                            for (int j = 0; j < 5; j++){
                                float k = j * xspace;
                                transform = glm::translate(modelMatrix, vec3(k,l,x));
                                renderCube(transform);
                            }
                        }
                    }
                }
                else{
                    for (int i = 0; i < rowSize; i++){
                        float l = i * yspace;
                        if (i == (rowSize - 1)){
                            if (z == 2){
                                if (i == (rowSize - 1)){
                                    for (int j = 0; j < 5; j++){
                                        if (j == 0 || j == 4){
                                            float k = j * xspace;
                                            transform = glm::translate(modelMatrix, vec3(k,l,x));
                                            renderCube(transform);
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            for (int j = 0; j < 5; j++){
                                float k = j * xspace;
                                if (j == 0 || j == 4){
                                    transform = glm::translate(modelMatrix, vec3(k,l,x));
                                    renderCube(transform);

                                }
                            }
                        }
                    }
                }
            }
            break;

        case 5:
            float width = colSize;
            float height = rowSize;
            transform = glm::scale(modelMatrix, vec3(width, height, 1));
            renderCube(transform);
            break;


    }
    renderGrid();
}

void GLWidget::renderCube(mat4 transform) {
    glUseProgram(cubeProg);
    glBindVertexArray(cubeVao);
    glUniformMatrix4fv(cubeModelMatrixLoc, 1, false, value_ptr(transform));
    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}

void GLWidget::renderGrid() {
    glUseProgram(gridProg);
    glBindVertexArray(gridVao);
    glDrawArrays(GL_LINES, 0, 84);
}

GLuint GLWidget::loadShaders(const char* vertf, const char* fragf) {
    GLuint program = glCreateProgram();

    // read vertex shader from Qt resource file
    QFile vertFile(vertf);
    vertFile.open(QFile::ReadOnly | QFile::Text);
    QString vertString;
    QTextStream vertStream(&vertFile);
    vertString.append(vertStream.readAll());
    std::string vertSTLString = vertString.toStdString();

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
    QFile fragFile(fragf);
    fragFile.open(QFile::ReadOnly | QFile::Text);
    QString fragString;
    QTextStream fragStream(&fragFile);
    fragString.append(fragStream.readAll());
    std::string fragSTLString = fragString.toStdString();

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

    return program;
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    vec2 pt(event->x(), event->y());
    lastVPt = normalize(pointOnVirtualTrackball(pt));
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    vec2 pt(event->x(), event->y());
    vec3 vPt = normalize(pointOnVirtualTrackball(pt));

    vec3 axis = cross(lastVPt, vPt);
//    vec3 axis = cross(vPt, lastVPt);
    if(length(axis) >= .00001) {
        axis = normalize(axis);
        float angle = acos(dot(vPt,lastVPt));
        mat4 r = rotate(mat4(1.0f), angle, axis);

        totRotation = r*totRotation;
        modelMatrix = r*modelMatrix;
        modelGridMatrix = r*modelGridMatrix;

        glUseProgram(cubeProg);
        glUniformMatrix4fv(cubeModelMatrixLoc, 1, false, value_ptr(modelMatrix));

        glUseProgram(gridProg);
        glUniformMatrix4fv(gridModelMatrixLoc, 1, false, value_ptr(modelGridMatrix));
    }
    lastVPt = vPt;
    update();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        //A and Q deal with scaling on the x-axis
        case Qt::Key_A:
            sx = sx + 1;
            break;

        case Qt::Key_Q:
            if(sx <= 1){
                sx = 1;
            }
            else {
                sx = sx - 1;
            }
            break;

        //S and W deal with scaling on the y-axis
        case Qt::Key_S:
            sy = sy + 1;
            break;

        case Qt::Key_W:
            if(sy <= 1){
                sy = 1;
            }
            else {
                sy = sy - 1;
            }
            break;

        //D and E deal with scaling on the z-axis
        case Qt::Key_D:
            sz = sz + 1;
            break;

        case Qt::Key_E:
            if(sz <= 1){
                sz = 1;
            }
            else {
                sz = sz - 1;
            }
            break;

        case Qt::Key_X:
            if(xspace <= .5){
                xspace = .5;
            }
            else{
                xspace = xspace -.25;
            }
            break;

        case Qt::Key_Z:
            xspace = xspace + .25;
            break;

        case Qt::Key_V:
            if(yspace <= .5){
                yspace = .5;
            }
            else{
                yspace = yspace - .25;
            }
            break;

        case Qt::Key_C:
            yspace = yspace + .25;
            break;

        case Qt::Key_G:
            if(zspace <= .5){
                zspace = .5;
            }
            else{
                zspace = zspace - .25;
            }
            break;

        case Qt::Key_H:
            zspace = zspace + .25;
            break;

        case Qt::Key_N:
            rowSize = rowSize + 1;
            break;

        case Qt::Key_M:
            if(rowSize <= 1){
                rowSize = 1;
            }
            else{
                rowSize = rowSize - 1;
            }
            break;

        case Qt::Key_Plus:
            colSize = colSize + 1;
            break;

        case Qt::Key_Minus:
            if(colSize <= 1){
                colSize = 1;
            }
            else{
                colSize = colSize - 1;
            }
            break;

        //The next four options change what kind of wall will be generated
        case Qt::Key_J:
            wallType = 1;
            break;

        case Qt::Key_Space:
            wallType = 2;
            break;

        case Qt::Key_L:
            wallType = 3;
            break;

        case Qt::Key_K:
            wallType = 4;
            break;

        case Qt::Key_Semicolon:
            wallType = 5;
            break;

    }
    modelMatrix = mat4(1.0f);
    modelGridMatrix = mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(sx, sy, sz));
    modelMatrix = totRotation*modelMatrix;
    modelGridMatrix = totRotation*modelGridMatrix;
    glUseProgram(cubeProg);
    glUniformMatrix4fv(cubeModelMatrixLoc, 1, false, value_ptr(modelMatrix));
    glUseProgram(gridProg);
    glUniformMatrix4fv(gridModelMatrixLoc, 1, false, value_ptr(modelGridMatrix));
    update();
}

vec3 GLWidget::pointOnVirtualTrackball(const vec2 &pt) {
    float r = .5f;
    float rr = r*r;
    p.x = -1 + pt.x*(2.0f/width);
    p.y = -(float)height/width*(1-pt.y*(2.0f/height));

    float xx = p.x*p.x;
    float yy = p.y*p.y;

    if(xx+yy <= rr*.5) {
        p.z = sqrt(rr-(xx+yy));
    } else {
        p.z = rr*.5/sqrt(xx+yy);
    }

//    std::cout << p.x << ", " << p.y << ", " << p.z << std::endl;

    return p;
}
