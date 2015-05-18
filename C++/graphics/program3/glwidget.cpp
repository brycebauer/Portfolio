#include "glwidget.h"
#include <iostream>
#include <QOpenGLTexture>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QTextStream>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

using glm::inverse;
using glm::vec2;
using glm::vec3;
using glm::mat3;
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
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(16);

    forward = false;
    back = false;
    left = false;
    right = false;
    up = false;
    down = false;
    fly = false;
    run = false;
    quick = false;
    turtle = false;
    speed = 1;
    xspace = .5;
    yspace = .5;
    zspace = .5;
    xscale = 1;
    yscale = 1;
    zscale = 1;
    rowNum = 1;

}

GLWidget::~GLWidget() {
}

void GLWidget::animate(){
    float dt = .016;
    if (fly){
        velocity = vec3(0,0,0);
        forwardVec = -vec3(orientation[2]);
        rightVec = vec3(yawMatrix[0]);
        upVec = vec3(0,1,0);
    }
    else {
        velocity = vec3(0,0,0);
        //position += velocity*speed*dt;
        forwardVec = -vec3(yawMatrix[2]);
        rightVec = vec3(yawMatrix[0]);
        upVec = vec3(0,1,0);
    }

    if (length(velocity)>0){
        velocity += normalize(velocity);
    }

    if (forward){
        velocity += forwardVec;
    }

    if (back){
        velocity += -forwardVec;
    }

    if (right){
        velocity += rightVec;
    }

    if (left){
        velocity += -rightVec;
    }

    if (up){
        velocity += upVec;
    }

    if (down){
        velocity += -upVec;
    }

    if (run){
        speed = 2;
    } else if(quick){
        speed = 50;
    } else if (turtle){
        speed = .15;
    }
    else {
        speed = 1;
    }

    currentPosition += velocity*speed*dt;

    if (currentPosition.x < -4.45){
        currentPosition.x = -4.45;
    }

    if (currentPosition.x > 4.45){
        currentPosition.x = 4.45;
    }

    if (currentPosition.y < -.45){
        currentPosition.y = -.45;
    }

    if (currentPosition.y > 8.45){
        currentPosition.y = 8.45;
    }

    if (currentPosition.z > .45){
        currentPosition.z = .45;
    }

    if (currentPosition.z < -12.45){
        currentPosition.z = -12.45;
    }

    if (currentPosition.y < 5.55 && currentPosition.y > 5.45){
        if (currentPosition.x < -.45){
            currentPosition.y = 5.55;
        }
        if (currentPosition.x > .45){
            currentPosition.y = 5.55;
        }
        if (currentPosition.z < -.45){
            currentPosition.y = 5.55;
        }
    }

    if (currentPosition.y < 3.55  && currentPosition.y > 3.45){
        if (currentPosition.x < -.45){
            currentPosition.y = 3.45;
        }
        if (currentPosition.x > .45){
            currentPosition.y = 3.45;
        }
        if (currentPosition.z < -.45){
            currentPosition.y = 3.45;
        }
    }

    if (currentPosition.y > 1.45 && currentPosition.y < 4.45){
        if (currentPosition.x < -1.45 && currentPosition.x > -1.55){
            currentPosition.x = -1.45;
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 1.55){
            currentPosition.x = 1.45;
        }
        if (currentPosition.x < -2.45 && currentPosition.x > -2.55){
            currentPosition.x = -2.55;
        }
        if (currentPosition.x > 2.45 && currentPosition.x < 2.55){
            currentPosition.x = 2.55;
        }
    }

    if (currentPosition.y < 1.45){
        if (currentPosition.x < -1.45 && currentPosition.x > -1.55){
            if (currentPosition.z > -.55){
                currentPosition.x = -1.45;
            }
            if (currentPosition.z < -1.45 && currentPosition.z > -5.55){
                currentPosition.x = -1.45;
            }
            if (currentPosition.z < -6.45 && currentPosition.z > -10.55){
                currentPosition.x = -1.45;
            }
            if (currentPosition.z < -11.45){
                currentPosition.x = -1.45;
            }
        }

        if (currentPosition.x < -2.45 && currentPosition.x > -2.55){
            if (currentPosition.z > -.55){
                currentPosition.x = -2.55;
            }
            if (currentPosition.z < -1.45 && currentPosition.z > -5.55){
                currentPosition.x = -2.55;
            }
            if (currentPosition.z < -6.45 && currentPosition.z > -10.55){
                currentPosition.x = -2.55;
            }
            if (currentPosition.z < -11.45){
                currentPosition.x = -2.55;
            }
        }

        if  (currentPosition.x > 1.45 && currentPosition.x < 1.55){
            if (currentPosition.z > -.55){
                currentPosition.x = 1.45;
            }
            if (currentPosition.z < -1.45 && currentPosition.z > -5.55){
                currentPosition.x = 1.45;
            }
            if (currentPosition.z < -6.45 && currentPosition.z > -10.55){
                currentPosition.x = 1.45;
            }
            if (currentPosition.z < -11.45){
                currentPosition.x = 1.45;
            }
        }

        if (currentPosition.x > 2.45 && currentPosition.x < 2.55){
            if (currentPosition.z > -.55){
                currentPosition.x = 2.55;
            }
            if (currentPosition.z < -1.45 && currentPosition.z > -5.55){
                currentPosition.x = 2.55;
            }
            if (currentPosition.z < -6.45 && currentPosition.z > -10.55){
                currentPosition.x = 2.55;
            }
            if (currentPosition.z < -11.45){
                currentPosition.x = 2.55;
            }
        }
    }

    if (currentPosition.z < -.45 &&  currentPosition.z > -1.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y > 1.45 && currentPosition.y < 1.55){
                currentPosition.y = 1.45;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y > 1.45 && currentPosition.y < 1.55)
                currentPosition.y = 1.45;
        }
    }

    if (currentPosition.z < -5.45 && currentPosition.z > -6.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y > 1.45 && currentPosition.y < 1.55){
                currentPosition.y = 1.45;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y > 1.45 && currentPosition.y < 1.55)
                currentPosition.y = 1.45;
        }
    }

    if (currentPosition.z < -10.45 && currentPosition.z > -11.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y > 1.45 && currentPosition.y < 1.55){
                currentPosition.y = 1.45;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y > 1.45 && currentPosition.y < 1.55)
                currentPosition.y = 1.45;
        }
    }

    if (currentPosition.z < -.45 && currentPosition.z > -.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -.55;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -.55;
            }
        }
    }

    if (currentPosition.z < -1.45 && currentPosition.z > -1.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -1.45;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -1.45;
            }
        }
    }

    if (currentPosition.z < -5.45 && currentPosition.z > -5.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -5.55;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -5.55;
            }
        }
    }

    if (currentPosition.z < -6.45 && currentPosition.z > -6.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -6.45;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -6.45;
            }
        }
    }

    if (currentPosition.z < -10.45 && currentPosition.z > -10.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -10.55;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -10.55;
            }
        }
    }

    if (currentPosition.z < -11.45 && currentPosition.z > -11.55){
        if (currentPosition.x < -1.45 && currentPosition.x > -2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -11.45;
            }
        }
        if (currentPosition.x > 1.45 && currentPosition.x < 2.55){
            if (currentPosition.y < 2){
                currentPosition.z = -11.45;
            }
        }
    }

    if (currentPosition.z < -2.45 && currentPosition.z > -2.55){
        if (currentPosition.x < -2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -2.45;
            }
        }
        if (currentPosition.x > 2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -2.45;
            }
        }
    }

    if (currentPosition.z < -4.45 && currentPosition.z > -4.55){
        if (currentPosition.x < -2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -4.55;
            }
        }
        if (currentPosition.x > 2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -4.55;
            }
        }
    }

    if (currentPosition.z < -7.45 && currentPosition.z > -7.55){
        if (currentPosition.x < -2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -7.45;
            }
        }
        if (currentPosition.x > 2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -7.45;
            }
        }
    }

    if (currentPosition.z < -9.45 && currentPosition.z > -9.55){
        if (currentPosition.x < -2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -9.55;
            }
        }
        if (currentPosition.x > 2.45){
            if (currentPosition.y < 5){
                currentPosition.z = -9.55;
            }
        }
    }

    if (currentPosition.x < -.45 && currentPosition.x > -.55){
        if (currentPosition.y > 3.45 && currentPosition.y < 5.55){
            if (currentPosition.z > -.5){
                currentPosition.x = -.45;
            }
        }
    }

    if (currentPosition.x > .45 && currentPosition.x < .55){
        if (currentPosition.y > 3.45 && currentPosition.y < 5.55){
            if (currentPosition.z > -.5){
                currentPosition.x = .45;
            }
        }
    }

    if (currentPosition.z < -.45 && currentPosition.z > -.55){
        if (currentPosition.y > 3.45 && currentPosition.y < 5.55){
            currentPosition.z = -.45;
        }
    }

    updateView();
    update();
}

void GLWidget::initializeGrid() {
    glGenVertexArrays(1, &gridVao);
    glBindVertexArray(gridVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    vec3 pts[84];
    for(int i = -10; i <= 10; i++) {

        pts[2*(i+10)] = vec3(i, -1, 10);
        pts[2*(i+10)+1] = vec3(i, -1, -10);

        pts[2*(i+10)+42] = vec3(10,-1, i);
        pts[2*(i+10)+43] = vec3(-10,-1, i);
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
    gridModelMatrixLoc = glGetUniformLocation(program, "model");
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

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(1,1,1),    // 0
        vec3(1,1,-1),   // 1
        vec3(-1,1,-1),  // 2
        vec3(-1,1,1),   // 3

        // bottom
        vec3(1,-1,1),   // 4
        vec3(-1,-1,1),  // 5
        vec3(-1,-1,-1), // 6
        vec3(1,-1,-1),  // 7

        // front
        vec3(1,1,1),    // 8
        vec3(-1,1,1),   // 9
        vec3(-1,-1,1),  // 10
        vec3(1,-1,1),   // 11

        // back
        vec3(-1,-1,-1), // 12
        vec3(-1,1,-1),  // 13
        vec3(1,1,-1),   // 14
        vec3(1,-1,-1),  // 15

        // right
        vec3(1,-1,1),   // 16
        vec3(1,-1,-1),  // 17
        vec3(1,1,-1),   // 18
        vec3(1,1,1),     // 19

        // left
        vec3(-1,-1,1),  // 20
        vec3(-1,1,1),   // 21
        vec3(-1,1,-1),  // 22
        vec3(-1,-1,-1) // 23

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
        vec3(0,0,1),    
        vec3(0,0,1),    
        vec3(0,0,1),    
        vec3(0,0,1),    

        // back
        vec3(0,0,.5f),  
        vec3(0,0,.5f),  
        vec3(0,0,.5f),  
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),    
        vec3(1,0,0),    
        vec3(1,0,0),    
        vec3(1,0,0),    


        // left
        vec3(.5f,0,0),  
        vec3(.5f,0,0),  
        vec3(.5f,0,0),  
        vec3(.5f,0,0)  
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
    
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // The following is an 8x8 checkerboard pattern using
    // GL_RED, GL_UNSIGNED_BYTE data.
    static const GLubyte tex_checkerboard_data[] =
    {
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };

    glGenTextures(1, &textureObject);
    glBindTexture(GL_TEXTURE_2D, textureObject);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RED,8,8,0,GL_RED,GL_UNSIGNED_BYTE,tex_checkerboard_data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    cubeProjMatrixLoc = glGetUniformLocation(program, "projection");
    cubeViewMatrixLoc = glGetUniformLocation(program, "view");
    cubeModelMatrixLoc = glGetUniformLocation(program, "model");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeWall() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &wallVao);
    glBindVertexArray(wallVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(1,1,1),    // 0
        vec3(1,1,-1),   // 1
        vec3(-1,1,-1),  // 2
        vec3(-1,1,1),   // 3

        // bottom
        vec3(1,-1,1),   // 4
        vec3(-1,-1,1),  // 5
        vec3(-1,-1,-1), // 6
        vec3(1,-1,-1),  // 7

        // front
        vec3(1,1,1),    // 8
        vec3(-1,1,1),   // 9
        vec3(-1,-1,1),  // 10
        vec3(1,-1,1),   // 11

        // back
        vec3(-1,-1,-1), // 12
        vec3(-1,1,-1),  // 13
        vec3(1,1,-1),   // 14
        vec3(1,-1,-1),  // 15

        // right
        vec3(1,-1,1),   // 16
        vec3(1,-1,-1),  // 17
        vec3(1,1,-1),   // 18
        vec3(1,1,1),     // 19

        // left
        vec3(-1,-1,1),  // 20
        vec3(-1,1,1),   // 21
        vec3(-1,1,-1),  // 22
        vec3(-1,-1,-1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/vert.glsl", ":/frag.glsl");
    glUseProgram(program);
    wallProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &walltexObject);
    glBindTexture(GL_TEXTURE_2D, walltexObject);


    QImage img("walltex.jpg");
  //  img.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,img.width(),img.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    wallProjMatrixLoc = glGetUniformLocation(program, "projection");
    wallViewMatrixLoc = glGetUniformLocation(program, "view");
    wallModelMatrixLoc = glGetUniformLocation(program, "model");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeDoor() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &doorVao);
    glBindVertexArray(doorVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(1,2,1),    // 0
        vec3(1,2,-1),   // 1
        vec3(-1,2,-1),  // 2
        vec3(-1,2,1),   // 3

        // bottom
        vec3(1,-2,1),   // 4
        vec3(-1,-2,1),  // 5
        vec3(-1,-2,-1), // 6
        vec3(1,-2,-1),  // 7

        // front
        vec3(1,2,1),    // 8
        vec3(-1,2,1),   // 9
        vec3(-1,-2,1),  // 10
        vec3(1,-2,1),   // 11

        // back
        vec3(-1,-2,-1), // 12
        vec3(-1,2,-1),  // 13
        vec3(1,2,-1),   // 14
        vec3(1,-2,-1),  // 15

        // right
        vec3(1,-2,1),   // 16
        vec3(1,-2,-1),  // 17
        vec3(1,2,-1),   // 18
        vec3(1,2,1),     // 19

        // left
        vec3(-1,-2,1),  // 20
        vec3(-1,2,1),   // 21
        vec3(-1,2,-1),  // 22
        vec3(-1,-2,-1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(1,0),
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/door_vert.glsl", ":/door_frag.glsl");
    glUseProgram(program);
    doorProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &doortexObject);
    glBindTexture(GL_TEXTURE_2D, doortexObject);


    QImage dimg("doortex.jpg");
    dimg.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,dimg.width(),dimg.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,dimg.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    doorProjMatrixLoc = glGetUniformLocation(program, "projection");
    doorViewMatrixLoc = glGetUniformLocation(program, "view");
    doorModelMatrixLoc = glGetUniformLocation(program, "model");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeEnder() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &enderVao);
    glBindVertexArray(enderVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),

        // bottom
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),

        // front
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(1,0),
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

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

   // vec3 lightPos = vec3(-3, 2, -1);

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/head_vert.glsl", ":/head_frag.glsl");
    glUseProgram(program);
    enderProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "eposition");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "ecolor");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "euv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    GLint normalIndex = glGetAttribLocation(program, "enormal");
    glEnableVertexAttribArray(normalIndex);
    glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &enderObject);
    glBindTexture(GL_TEXTURE_2D, enderObject);


    QImage dimg("head.jpg");
    dimg.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,dimg.width(),dimg.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,dimg.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    enderProjMatrixLoc = glGetUniformLocation(program, "eprojection");
    enderViewMatrixLoc = glGetUniformLocation(program, "eview");
    enderModelMatrixLoc = glGetUniformLocation(program, "emodel");
    lightPosition = glGetUniformLocation(program, "elightPos");

    GLint texLoc = glGetUniformLocation(program, "etex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeZombie() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &zombieVao);
    glBindVertexArray(zombieVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),

        // bottom
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),

        // front
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        vec2(0,1),

        // back
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),
        vec2(0,1),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1)

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/zom_vert.glsl", ":/zom_frag.glsl");
    glUseProgram(program);
    zombieProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    GLint normalIndex = glGetAttribLocation(program, "normal");
    glEnableVertexAttribArray(normalIndex);
    glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &zombieObject);
    glBindTexture(GL_TEXTURE_2D, zombieObject);


    QImage dimg("zhead.jpg");
    dimg.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,dimg.width(),dimg.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,dimg.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    zombieProjMatrixLoc = glGetUniformLocation(program, "projection");
    zombieViewMatrixLoc = glGetUniformLocation(program, "view");
    zombieModelMatrixLoc = glGetUniformLocation(program, "model");
    lightPosition = glGetUniformLocation(program, "lightPos");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeCreep() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &creepVao);
    glBindVertexArray(creepVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),

        // bottom
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),
        vec2(0,0),

        // front
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        vec2(0,1),

        // back
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),
        vec2(0,1),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1)

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/creep_vert.glsl", ":/creep_frag.glsl");
    glUseProgram(program);
    creepProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    GLint normalIndex = glGetAttribLocation(program, "normal");
    glEnableVertexAttribArray(normalIndex);
    glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &creepObject);
    glBindTexture(GL_TEXTURE_2D, creepObject);


    QImage dimg("chead.jpg");
    dimg.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,dimg.width(),dimg.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,dimg.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    creepProjMatrixLoc = glGetUniformLocation(program, "projection");
    creepViewMatrixLoc = glGetUniformLocation(program, "view");
    creepModelMatrixLoc = glGetUniformLocation(program, "model");
    lightPosition = glGetUniformLocation(program, "lightPos");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeCeiling() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &ceilingVao);
    glBindVertexArray(ceilingVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(1,1,1),    // 0
        vec3(1,1,-1),   // 1
        vec3(-1,1,-1),  // 2
        vec3(-1,1,1),   // 3

        // bottom
        vec3(1,-1,1),   // 4
        vec3(-1,-1,1),  // 5
        vec3(-1,-1,-1), // 6
        vec3(1,-1,-1),  // 7

        // front
        vec3(1,1,1),    // 8
        vec3(-1,1,1),   // 9
        vec3(-1,-1,1),  // 10
        vec3(1,-1,1),   // 11

        // back
        vec3(-1,-1,-1), // 12
        vec3(-1,1,-1),  // 13
        vec3(1,1,-1),   // 14
        vec3(1,-1,-1),  // 15

        // right
        vec3(1,-1,1),   // 16
        vec3(1,-1,-1),  // 17
        vec3(1,1,-1),   // 18
        vec3(1,1,1),     // 19

        // left
        vec3(-1,-1,1),  // 20
        vec3(-1,1,1),   // 21
        vec3(-1,1,-1),  // 22
        vec3(-1,-1,-1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/ceiling_vert.glsl", ":/ceiling_frag.glsl");
    glUseProgram(program);
    ceilingProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &ceilingtexObject);
    glBindTexture(GL_TEXTURE_2D, ceilingtexObject);


    QImage img("ceilingtex.jpg");
    img.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,img.width(),img.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    ceilingProjMatrixLoc = glGetUniformLocation(program, "projection");
    ceilingViewMatrixLoc = glGetUniformLocation(program, "view");
    ceilingModelMatrixLoc = glGetUniformLocation(program, "model");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeFloor() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &floorVao);
    glBindVertexArray(floorVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(1,1,1),    // 0
        vec3(1,1,-1),   // 1
        vec3(-1,1,-1),  // 2
        vec3(-1,1,1),   // 3

        // bottom
        vec3(1,-1,1),   // 4
        vec3(-1,-1,1),  // 5
        vec3(-1,-1,-1), // 6
        vec3(1,-1,-1),  // 7

        // front
        vec3(1,1,1),    // 8
        vec3(-1,1,1),   // 9
        vec3(-1,-1,1),  // 10
        vec3(1,-1,1),   // 11

        // back
        vec3(-1,-1,-1), // 12
        vec3(-1,1,-1),  // 13
        vec3(1,1,-1),   // 14
        vec3(1,-1,-1),  // 15

        // right
        vec3(1,-1,1),   // 16
        vec3(1,-1,-1),  // 17
        vec3(1,1,-1),   // 18
        vec3(1,1,1),     // 19

        // left
        vec3(-1,-1,1),  // 20
        vec3(-1,1,1),   // 21
        vec3(-1,1,-1),  // 22
        vec3(-1,-1,-1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/floor_vert.glsl", ":/floor_frag.glsl");
    glUseProgram(program);
    floorProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &floortexObject);
    glBindTexture(GL_TEXTURE_2D, floortexObject);


    QImage fimg("floortex.jpg");
    fimg.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,fimg.width(),fimg.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,fimg.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    floorProjMatrixLoc = glGetUniformLocation(program, "projection");
    floorViewMatrixLoc = glGetUniformLocation(program, "view");
    floorModelMatrixLoc = glGetUniformLocation(program, "model");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeCastle() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &castleVao);
    glBindVertexArray(castleVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/castle_vert.glsl", ":/castle_frag.glsl");
    glUseProgram(program);
    castleProg = program;

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &castleObject);
    glBindTexture(GL_TEXTURE_2D, castleObject);


    QImage fimg("circuit.jpg");
    fimg.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,fimg.width(),fimg.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,fimg.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    castleProjMatrixLoc = glGetUniformLocation(program, "projection");
    castleViewMatrixLoc = glGetUniformLocation(program, "view");
    castleModelMatrixLoc = glGetUniformLocation(program, "model");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeIron() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &ironVao);
    glBindVertexArray(ironVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(0,0,0),    // 0
        vec3(0,0,-.1),   // 1
        vec3(-.1,0,-.1),  // 2
        vec3(-.1,0,0),   // 3

        // bottom
        vec3(0,-.1,0),   // 4
        vec3(-.1,-.1,0),  // 5
        vec3(-.1,-.1,-.1), // 6
        vec3(0,-.1,-.1),  // 7

        // front
        vec3(0,0,0),    // 8
        vec3(-.1,0,0),   // 9
        vec3(-.1,-.1,0),  // 10
        vec3(0,-.1,0),   // 11

        // back
        vec3(-.1,-.1,-.1), // 12
        vec3(-.1,0,-.1),  // 13
        vec3(0,0,-.1),   // 14
        vec3(0,-.1,-.1),  // 15

        // right
        vec3(0,-.1,0),   // 16
        vec3(0,-.1,-.1),  // 17
        vec3(0,0,-.1),   // 18
        vec3(0,0,0),     // 19

        // left
        vec3(-.1,-.1,0),  // 20
        vec3(-.1,0,0),   // 21
        vec3(-.1,0,-.1),  // 22
        vec3(-.1,-.1,-.1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/sword_vert.glsl", ":/sword_frag.glsl");
    glUseProgram(program);
    ironProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "swposition");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "swcolor");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "swuv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // The following is an 8x8 checkerboard pattern using
    // GL_RED, GL_UNSIGNED_BYTE data.
    static const GLubyte tex_checkerboard_data[] =
    {
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB
    };

    glGenTextures(1, &ironObject);
    glBindTexture(GL_TEXTURE_2D, ironObject);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RED,8,8,0,GL_RED,GL_UNSIGNED_BYTE,tex_checkerboard_data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    ironProjMatrixLoc = glGetUniformLocation(program, "swprojection");
    ironViewMatrixLoc = glGetUniformLocation(program, "swview");
    ironModelMatrixLoc = glGetUniformLocation(program, "swmodel");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeDark() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &darkVao);
    glBindVertexArray(darkVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(0,0,0),    // 0
        vec3(0,0,-.1),   // 1
        vec3(-.1,0,-.1),  // 2
        vec3(-.1,0,0),   // 3

        // bottom
        vec3(0,-.1,0),   // 4
        vec3(-.1,-.1,0),  // 5
        vec3(-.1,-.1,-.1), // 6
        vec3(0,-.1,-.1),  // 7

        // front
        vec3(0,0,0),    // 8
        vec3(-.1,0,0),   // 9
        vec3(-.1,-.1,0),  // 10
        vec3(0,-.1,0),   // 11

        // back
        vec3(-.1,-.1,-.1), // 12
        vec3(-.1,0,-.1),  // 13
        vec3(0,0,-.1),   // 14
        vec3(0,-.1,-.1),  // 15

        // right
        vec3(0,-.1,0),   // 16
        vec3(0,-.1,-.1),  // 17
        vec3(0,0,-.1),   // 18
        vec3(0,0,0),     // 19

        // left
        vec3(-.1,-.1,0),  // 20
        vec3(-.1,0,0),   // 21
        vec3(-.1,0,-.1),  // 22
        vec3(-.1,-.1,-.1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/sword_vert.glsl", ":/sword_frag.glsl");
    glUseProgram(program);
    darkProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "swposition");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "swcolor");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "swuv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // The following is an 8x8 checkerboard pattern using
    // GL_RED, GL_UNSIGNED_BYTE data.
    static const GLubyte tex_checkerboard_data[] =
    {
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66
    };

    glGenTextures(1, &darkObject);
    glBindTexture(GL_TEXTURE_2D, darkObject);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RED,8,8,0,GL_RED,GL_UNSIGNED_BYTE,tex_checkerboard_data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    darkProjMatrixLoc = glGetUniformLocation(program, "swprojection");
    darkViewMatrixLoc = glGetUniformLocation(program, "swview");
    darkModelMatrixLoc = glGetUniformLocation(program, "swmodel");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeWood() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &woodVao);
    glBindVertexArray(woodVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(0,0,0),    // 0
        vec3(0,0,-.1),   // 1
        vec3(-.1,0,-.1),  // 2
        vec3(-.1,0,0),   // 3

        // bottom
        vec3(0,-.1,0),   // 4
        vec3(-.1,-.1,0),  // 5
        vec3(-.1,-.1,-.1), // 6
        vec3(0,-.1,-.1),  // 7

        // front
        vec3(0,0,0),    // 8
        vec3(-.1,0,0),   // 9
        vec3(-.1,-.1,0),  // 10
        vec3(0,-.1,0),   // 11

        // back
        vec3(-.1,-.1,-.1), // 12
        vec3(-.1,0,-.1),  // 13
        vec3(0,0,-.1),   // 14
        vec3(0,-.1,-.1),  // 15

        // right
        vec3(0,-.1,0),   // 16
        vec3(0,-.1,-.1),  // 17
        vec3(0,0,-.1),   // 18
        vec3(0,0,0),     // 19

        // left
        vec3(-.1,-.1,0),  // 20
        vec3(-.1,0,0),   // 21
        vec3(-.1,0,-.1),  // 22
        vec3(-.1,-.1,-.1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/wood_vert.glsl", ":/wood_frag.glsl");
    glUseProgram(program);
    woodProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "swposition");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "swcolor");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "swuv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &woodObject);
    glBindTexture(GL_TEXTURE_2D, woodObject);

    QImage img("oak.jpg");
    img.bits();

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,img.width(),img.height(),0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img.bits());

    //glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,8,8,0,GL_RGBA,GL_UNSIGNED_BYTE,tex_checkerboard_data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    woodProjMatrixLoc = glGetUniformLocation(program, "swprojection");
    woodViewMatrixLoc = glGetUniformLocation(program, "swview");
    woodModelMatrixLoc = glGetUniformLocation(program, "swmodel");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
}

void GLWidget::initializeSword() {
    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    glGenVertexArrays(1, &swordVao);
    glBindVertexArray(swordVao);

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    vec3 pts[] = {
        // top
        vec3(0,0,0),    // 0
        vec3(0,0,-.1),   // 1
        vec3(-.1,0,-.1),  // 2
        vec3(-.1,0,0),   // 3

        // bottom
        vec3(0,-.1,0),   // 4
        vec3(-.1,-.1,0),  // 5
        vec3(-.1,-.1,-.1), // 6
        vec3(0,-.1,-.1),  // 7

        // front
        vec3(0,0,0),    // 8
        vec3(-.1,0,0),   // 9
        vec3(-.1,-.1,0),  // 10
        vec3(0,-.1,0),   // 11

        // back
        vec3(-.1,-.1,-.1), // 12
        vec3(-.1,0,-.1),  // 13
        vec3(0,0,-.1),   // 14
        vec3(0,-.1,-.1),  // 15

        // right
        vec3(0,-.1,0),   // 16
        vec3(0,-.1,-.1),  // 17
        vec3(0,0,-.1),   // 18
        vec3(0,0,0),     // 19

        // left
        vec3(-.1,-.1,0),  // 20
        vec3(-.1,0,0),   // 21
        vec3(-.1,0,-.1),  // 22
        vec3(-.1,-.1,-.1) // 23

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
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),
        vec3(0,0,1),

        // back
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),
        vec3(0,0,.5f),

        // right
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),
        vec3(1,0,0),


        // left
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0),
        vec3(.5f,0,0)
    };

    vec2 uvs[] = {
        // top
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // bottom
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // front
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // back
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // right
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),

        // left
        vec2(0,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0)

    };

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

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders(":/sword_vert.glsl", ":/sword_frag.glsl");
    glUseProgram(program);
    swordProg = program;

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "swposition");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GLint colorIndex = glGetAttribLocation(program, "swcolor");
    glEnableVertexAttribArray(colorIndex);
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    GLint uvIndex = glGetAttribLocation(program, "swuv");
    glEnableVertexAttribArray(uvIndex);
    glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // The following is an 8x8 checkerboard pattern using
    // GL_RED, GL_UNSIGNED_BYTE data.
    static const GLubyte tex_checkerboard_data[] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    glGenTextures(1, &swordtexObject);
    glBindTexture(GL_TEXTURE_2D, swordtexObject);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RED,8,8,0,GL_RED,GL_UNSIGNED_BYTE,tex_checkerboard_data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    swordProjMatrixLoc = glGetUniformLocation(program, "swprojection");
    swordViewMatrixLoc = glGetUniformLocation(program, "swview");
    swordModelMatrixLoc = glGetUniformLocation(program, "swmodel");

    GLint texLoc = glGetUniformLocation(program, "tex");
    glUniform1i(texLoc, 0);
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
    initializeCastle();
    initializeWall();
    initializeDoor();
    initializeFloor();
    initializeCeiling();
    initializeSword();
    initializeDark();
    initializeWood();
    initializeEnder();
    initializeZombie();
    initializeCreep();
    initializeIron();
    initializeGrid();

    viewMatrix = mat4(1.0f);
    modelMatrix = mat4(1.0f);
    enderMatrix = mat4(1.0f);
    swordMatrix = mat4(.5f);
    swordViewMat = mat4(.5f);

    glUseProgram(cubeProg);
    glUniformMatrix4fv(cubeViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(cubeModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(wallProg);
    glUniformMatrix4fv(wallViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(wallModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(doorProg);
    glUniformMatrix4fv(doorViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(doorModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(floorProg);
    glUniformMatrix4fv(floorViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(floorModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(castleProg);
    glUniformMatrix4fv(castleViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(castleModelMatrixLoc, 1, false, value_ptr(castleMatrix));

    glUseProgram(enderProg);
    glUniformMatrix4fv(enderViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(enderModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(zombieProg);
    glUniformMatrix4fv(zombieViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(zombieModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(creepProg);
    glUniformMatrix4fv(creepViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(creepModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(swordProg);
    glUniformMatrix4fv(swordViewMatrixLoc, 1, false, value_ptr(swordViewMat));
    glUniformMatrix4fv(swordModelMatrixLoc, 1, false, value_ptr(swordMatrix));

    glUseProgram(ironProg);
    glUniformMatrix4fv(ironViewMatrixLoc, 1, false, value_ptr(swordViewMat));
    glUniformMatrix4fv(ironModelMatrixLoc, 1, false, value_ptr(swordMatrix));

    glUseProgram(woodProg);
    glUniformMatrix4fv(woodViewMatrixLoc, 1, false, value_ptr(swordViewMat));
    glUniformMatrix4fv(woodModelMatrixLoc, 1, false, value_ptr(swordMatrix));

    glUseProgram(darkProg);
    glUniformMatrix4fv(darkViewMatrixLoc, 1, false, value_ptr(swordViewMat));
    glUniformMatrix4fv(darkModelMatrixLoc, 1, false, value_ptr(swordMatrix));

    glUseProgram(ceilingProg);
    glUniformMatrix4fv(ceilingViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(ceilingModelMatrixLoc, 1, false, value_ptr(modelMatrix));

    glUseProgram(gridProg);
    glUniformMatrix4fv(gridViewMatrixLoc, 1, false, value_ptr(viewMatrix));
    glUniformMatrix4fv(gridModelMatrixLoc, 1, false, value_ptr(modelMatrix));
}

void GLWidget::resizeGL(int w, int h) {
    width = w;
    height = h;

    float aspect = (float)w/h;

    projMatrix = perspective(45.0f, aspect, .01f, 100.0f);

    glUseProgram(cubeProg);
    glUniformMatrix4fv(cubeProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(wallProg);
    glUniformMatrix4fv(wallProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(doorProg);
    glUniformMatrix4fv(doorProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(enderProg);
    glUniformMatrix4fv(enderProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(zombieProg);
    glUniformMatrix4fv(zombieProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(creepProg);
    glUniformMatrix4fv(creepProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(castleProg);
    glUniformMatrix4fv(castleProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(swordProg);
    glUniformMatrix4fv(swordProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(ironProg);
    glUniformMatrix4fv(ironProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(darkProg);
    glUniformMatrix4fv(darkProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(woodProg);
    glUniformMatrix4fv(woodProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(floorProg);
    glUniformMatrix4fv(floorProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(ceilingProg);
    glUniformMatrix4fv(ceilingProjMatrixLoc, 1, false, value_ptr(projMatrix));

    glUseProgram(gridProg);
    glUniformMatrix4fv(gridProjMatrixLoc, 1, false, value_ptr(projMatrix));
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //floor
    for (int i = -5; i < 6; i++){
       for (int j = -13; j < 2; j++){
            transform = glm::translate(modelMatrix, vec3(i,-1,j));
            renderFloor(transform);
       }
    }

    for (int i = -5; i < 6; i++){
       for (int j = -13; j < 2; j++){
           if (i == 0 && j == 0){
               transform = glm::translate(modelMatrix, vec3(i,5,j));
           }
           else{
            transform = glm::translate(modelMatrix, vec3(i,5,j));
            renderFloor(transform);
           }
       }
    }

    //ceiling
    for (int i = -5; i < 6; i++){
       for (int j = -13; j < 2; j++){
           if (i == 0 && j == 0){
               transform = glm::translate(modelMatrix, vec3(i,4,j));
           }else{
            transform = glm::translate(modelMatrix, vec3(i,4,j));
            renderCeiling(transform);
           }
       }
    }

    for (int i = -5; i < 6; i++){
       for (int j = -13; j < 2; j++){
            transform = glm::translate(modelMatrix, vec3(i,9,j));
            renderCeiling(transform);
       }
    }

    //walls until next comment
    for (int i = -13; i < 2; i++){
        for (int j = 0; j < 4; j++){
            transform = glm::translate(modelMatrix, vec3(-5,j,i));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(5,j,i));
            renderWall(transform);
        }
    }

    for (int i = -13; i < 2; i++){
        for (int j = 6; j < 9; j++){
            transform = glm::translate(modelMatrix, vec3(-5,j,i));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(5,j,i));
            renderWall(transform);
        }
    }

    for (int i = -4; i < 5; i++){
        for (int j = 2; j < 4; j++){
            transform = glm::translate(modelMatrix, vec3(i,j,-13));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,1));
            renderWall(transform);
        }
    }

    for (int i = -4; i < 5; i++){
        for (int j = 6; j < 9; j++){
            transform = glm::translate(modelMatrix, vec3(i,j,-13));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,1));
            renderWall(transform);
        }
    }

    for (int i = -4; i < 0; i++){
        for (int j = 0; j < 2; j++){
            transform = glm::translate(modelMatrix, vec3(i,j,-13));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,1));
            renderWall(transform);
        }
    }

    for (int i = 1; i < 5; i++){
        for (int j = 0; j < 2; j++){
            transform = glm::translate(modelMatrix, vec3(i,j,-13));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,1));
            renderWall(transform);
        }
    }

    for (int i = 0; i < 2; i++){
        transform = glm::translate(modelMatrix, vec3(0,i,1));
        renderWall(transform);
    }

    for (int i = -13; i < 2; i++){
        for (int j = 2; j < 4; j++){
            transform = glm::translate(modelMatrix, vec3(2,j,i));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-2,j,i));
            renderWall(transform);
        }
    }

    for (int i = 0; i < 2; i++){
        transform = glm::translate(modelMatrix, vec3(2,i,0));
        renderWall(transform);
        transform = glm::translate(modelMatrix, vec3(-2,i,0));
        renderWall(transform);
        transform = glm::translate(modelMatrix, vec3(2,i,-12));
        renderWall(transform);
        transform = glm::translate(modelMatrix, vec3(-2,i,-12));
        renderWall(transform);
    }

    for (int i = 0; i < 2; i++){
        for (int j = -5; j < -1; j++){
            transform = glm::translate(modelMatrix, vec3(2,i,j));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-2,i,j));
            renderWall(transform);
        }
    }

    for (int i = 0; i < 2; i++){
        for (int j = -10; j < -6; j++){
            transform = glm::translate(modelMatrix, vec3(2,i,j));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-2,i,j));
            renderWall(transform);
        }
    }

    for (int i = 3; i < 5; i++){
        for (int j = 0; j < 4; j++){
            transform = glm::translate(modelMatrix, vec3(i,j,-3));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,-4));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,-8));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(i,j,-9));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-i,j,-3));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-i,j,-4));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-i,j,-8));
            renderWall(transform);
            transform = glm::translate(modelMatrix, vec3(-i,j,-9));
            renderWall(transform);
        }
    }

    //door
    transform = glm::translate(modelMatrix, vec3(0,.5,-13));
    renderDoor(transform);

    //sword
    transform = glm::translate(swordMatrix, vec3(3.5,0,-.5));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,0,-.55));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,0,-.6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-.5));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-.6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-.5));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-.55));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-.6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-1.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-1.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-1.15));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-1.2));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.65,-1.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.65,-1.25));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.7,-1.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.7,-1.3));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.75,-1.15));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.75,-1.3));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.8,-1.2));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.8,-1.25));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.8,-1.3));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-.55));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.9));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-.85));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-.8));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-.8));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-.75));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-.85));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-.75));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.7));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.9));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-1.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-1.1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.65,-1.15));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.7,-1.2));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.75,-1.25));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.75,-1.2));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.7,-1.25));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.7,-1.15));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.65,-1.1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.65,-1.2));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-1.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-1.15));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-1.1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-.95));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-1.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-.9));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.85));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-.95));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-.9));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-.6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-.65));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-.7));
    renderWood(transform);

    //pickaxe
    transform = glm::translate(swordMatrix, vec3(3.5,0,-5.75));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-5.8));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-5.85));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-5.9));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-5.95));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-6.05));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-6.15));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6.25));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6.3));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,0,-5.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-5.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-5.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-5.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-5.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-5.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-5.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-5.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-5.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-6.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-6.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-6.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-6.2));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-6.15));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6.3));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6.25));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-6.3));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-6.3));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-6.3));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.3));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-6.3));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-6.25));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-6.25));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-6.2));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6.2));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6.15));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6.15));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6.1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.9));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-5.95));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.95));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-6));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-6.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-6.1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-6.1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-6.15));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-6.2));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.25));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-6.25));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-6.25));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-6.25));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-6.3));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-6.3));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.2,-6.35));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-6.35));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-6.35));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.35));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-6.35));
    renderDark(transform);

    //shovel
    transform = glm::translate(swordMatrix, vec3(3.5,0,-6.15));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-6.1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-6.05));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-5.9));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-5.85));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-5.8));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-5.7));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-5.7));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-5.75));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-5.65));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.7));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.75));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.8));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.65));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.7));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.75));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.65));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.7));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.65));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,-.05,-6.2));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,-.05,-6.15));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,-.05,-5.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,-.05,-5.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,0,-5.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,0,-6.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,0,-6.2));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-6.15));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.05,-6.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.1,-6.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.15,-6.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.25,-5.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-5.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-5.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.3,-5.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-5.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-5.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-5.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-5.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.4,-5.6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.45,-5.55));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.5,-5.55));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.55,-5.55));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-5.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-5.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.6,-5.6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5,.35,-6.15));
    renderSword(transform);

    //ender head on spear
    transform = glm::translate(swordMatrix, vec3(-3.5,-.45,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.4, -6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.35,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.3,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.25,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.2,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.15,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.1,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.05,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,0,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.55,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.6,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.65,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.7,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.75,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.8,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.85,-6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-6.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-5.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.45,.9,-6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.55,.9,-6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.95,-6));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,1,-6));
    renderIron(transform);
    transform = glm::translate(enderMatrix, vec3(-3.5,.25,-6));
    renderEnder(transform);

    //zombie head on a spear
    transform = glm::translate(swordMatrix, vec3(-3.5,-.45,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.4, -11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.35,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.3,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.25,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.2,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.15,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.1,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.05,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,0,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.55,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.6,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.65,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.7,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.75,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.8,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.85,-11));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-11.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-10.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.45,.9,-11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.55,.9,-11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.95,-11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,1,-11));
    renderIron(transform);
    transform = glm::translate(enderMatrix, vec3(-3.5,.25,-11));
    renderZombie(transform);

    //creeper head on a spear
    transform = glm::translate(swordMatrix, vec3(-3.5,-.45,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.4, -1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.35,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.3,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.25,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.2,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.15,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.1,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,-.05,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,0,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.55,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.6,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.65,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.7,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.75,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.8,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.85,-1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-1.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.9,-.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.45,.9,-1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.55,.9,-1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,.95,-1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(-3.5,1,-1));
    renderIron(transform);
    transform = glm::translate(enderMatrix, vec3(-3.5,.25,-1));
    renderCreep(transform);

    //axe
    transform = glm::translate(swordMatrix, vec3(3.5, .05, -10.6));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .1, -10.65));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .15, -10.7));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .2, -10.75));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .25, -10.8));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .3, -10.85));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .35, -10.9));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .4, -10.95));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -11.1));
    renderWood(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .05, -10.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .1, -10.6));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .1, -10.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .15, -10.65));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .15, -10.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .2, -10.7));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .2, -10.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .25, -10.75));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .25, -10.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .3, -10.8));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .3, -10.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .35, -10.85));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .35, -10.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .4, -10.9));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .4, -11));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -10.95));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -11.1));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -11.05));
    renderSword(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .35, -11.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .35, -11.1));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .4, -11.15));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -11.15));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -10.9));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -10.85));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -10.8));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -10.8));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .6, -10.85));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .6, -11.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .65, -10.9));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .65, -11.05));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .7, -10.95));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .7, -11));
    renderDark(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .4, -11.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .4, -11.1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -11.1));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -11.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .45, -11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -11.05));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -10.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -10.9));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .5, -10.85));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -10.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -10.9));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .55, -10.85));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .6, -11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .6, -10.95));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .6, -10.9));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .65, -11));
    renderIron(transform);
    transform = glm::translate(swordMatrix, vec3(3.5, .65, -10.95));
    renderIron(transform);

    //Program2 object 1
    transform = glm::translate(castleMatrix, vec3(-4,6,-3));
    if (yscale <= 2){
        transform = glm::scale(transform, vec3(1,2,1));
    }
    else{
        transform = glm::scale(transform, vec3(1,yscale,1));
    }
    renderCastle(transform);

    //Program2 object 2
    for (int i = 12; i < (rowNum + 12); i++){
        float k = i * yspace;
        transform = glm::translate(castleMatrix, vec3(-4,k,-5.5));
        transform = glm::scale(transform, vec3(1,1,2));
        renderCastle(transform);
    }

    //Program2 object 3
    for (int i = 12; i < (rowNum + 12); i++){
        float k = i * .5;
        int temp = rowNum + 11;
        if (i >= temp){
            transform = glm::translate(castleMatrix, vec3(4,k,0));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(3.5,k,0));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(4,k,-1));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(3.5,k,-1));
            renderCastle(transform);
        }
        else{
            for (int j = 0; j > -3; j--){
                float z = j * zspace;
                transform = glm::translate(castleMatrix, vec3(4,k,z));
                renderCastle(transform);
                transform = glm::translate(castleMatrix, vec3(3.5,k,z));
                renderCastle(transform);
            }
        }
    }

    //Program2 object 4
    for (int i = 12; i < (rowNum + 12); i++){
        float k = i * .5;
        int temp = rowNum + 11;
        if (i < temp){
            transform = glm::translate(castleMatrix, vec3(-4,k,-.5));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(-3,k,-.5));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(-4,k,0));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(-3,k,0));
            renderCastle(transform);
        }
        else{
            for (int j = -8; j < -5; j++){
                float x = j * .5;
                transform = glm::translate(castleMatrix, vec3(x,k,-.5));
                renderCastle(transform);
                transform = glm::translate(castleMatrix, vec3(x,k,0));
                renderCastle(transform);
            }
        }
    }

    //Program2 object 5
    for (int i = -12; i < -9; i++){
        float z = i * .5;
        for (int k = 12; k < (rowNum + 12); k++){
            float y = k * .5;
            transform = glm::translate(castleMatrix, vec3(4,y,z));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
        }
    }

    //Program2 object 6
    for (int i = 6; i < (rowNum + 6); i++){
        if (i < (rowNum + 5)){
            transform = glm::translate(castleMatrix, vec3(4,i,-10));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(4,i,-11));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(4,i,-12));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(3,i,-12));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(2,i,-12));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
        }
        else{

            transform = glm::translate(castleMatrix, vec3(4,i,-10));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(4,i,-12));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
            transform = glm::translate(castleMatrix, vec3(2,i,-12));
            transform = glm::scale(transform, vec3(xscale,yscale,zscale));
            renderCastle(transform);
        }
    }

    //Program2 object 7
    transform = glm::translate(castleMatrix, vec3(-4,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3.5,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-2.5,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-2,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-1.5,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-1,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-.5,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(0,5.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3.5,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-2.5,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-2,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-1.5,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-1,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-.5,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(0,6.25,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-2,6.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-1,6.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(0,6.75,-12));
    transform = glm::scale(transform, vec3(xscale,yscale,zscale));
    renderCastle(transform);

    //Program2 object 8
    for (int i = 6; i < (rowNum + 6); i++){
        transform = glm::translate(castleMatrix, vec3(-.5,i,-3.5));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(-.5,i,-4.5));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(0,i,-4));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(.5,i,-3.5));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(.5,i,-4.5));
        renderCastle(transform);
    }

    //Program2 object 9
    transform = glm::translate(castleMatrix, vec3(-4,5.75,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,5.75,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,5.75,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,5.75,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.25,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.25,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.25,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.25,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.75,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.75,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.75,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.75,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,5.75,-8.5));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3.5,5.75,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3.5,5.75,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,5.75,-8.5));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-4,6.25,-8.5));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3.5,6.25,-9));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3.5,6.25,-8));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);
    transform = glm::translate(castleMatrix, vec3(-3,6.25,-8.5));
    transform = glm::scale(transform, vec3(1,yscale,1));
    renderCastle(transform);

    //Program2 object 10
    for (int i = 12; i < (rowNum + 12); i++){
        float y = i * .5;
        transform = glm::translate(castleMatrix, vec3(1,y,-8));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(1.5,y,-7.5));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(1,y,-7));
        renderCastle(transform);
        transform = glm::translate(castleMatrix, vec3(.5,y,-7.5));
        renderCastle(transform);
    }
    for (int j = 12; j < (rowNum + 13); j++){
        float m = j * .5;
        transform = glm::translate(castleMatrix, vec3(1,m,-7.5));
        renderCastle(transform);
    }

    renderGrid();

}

void GLWidget::renderWall(mat4 transform) {
    glUseProgram(wallProg);
    glBindVertexArray(wallVao);
    glUniformMatrix4fv(wallModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, walltexObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderDoor(mat4 transform) {
    glUseProgram(doorProg);
    glBindVertexArray(doorVao);
    glUniformMatrix4fv(doorModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, doortexObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderEnder(mat4 transform) {
    glUseProgram(enderProg);
    glBindVertexArray(enderVao);
    glUniformMatrix4fv(enderModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, enderObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderZombie(mat4 transform) {
    glUseProgram(zombieProg);
    glBindVertexArray(zombieVao);
    glUniformMatrix4fv(zombieModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, zombieObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderCreep(mat4 transform) {
    glUseProgram(creepProg);
    glBindVertexArray(creepVao);
    glUniformMatrix4fv(creepModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, creepObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderFloor(mat4 transform) {
    glUseProgram(floorProg);
    glBindVertexArray(floorVao);
    glUniformMatrix4fv(floorModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, floortexObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderCeiling(mat4 transform) {
    glUseProgram(ceilingProg);
    glBindVertexArray(ceilingVao);
    glUniformMatrix4fv(ceilingModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, ceilingtexObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}


void GLWidget::renderSword(mat4 transform) {
    glUseProgram(swordProg);
    glBindVertexArray(swordVao);
    glUniformMatrix4fv(swordModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, swordtexObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}

void GLWidget::renderCastle(mat4 transform) {
    glUseProgram(castleProg);
    glBindVertexArray(castleVao);
    glUniformMatrix4fv(castleModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, castleObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}

void GLWidget::renderDark(mat4 transform) {
    glUseProgram(darkProg);
    glBindVertexArray(darkVao);
    glUniformMatrix4fv(darkModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, darkObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}

void GLWidget::renderIron(mat4 transform) {
    glUseProgram(ironProg);
    glBindVertexArray(ironVao);
    glUniformMatrix4fv(ironModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, ironObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}

void GLWidget::renderWood(mat4 transform) {
    glUseProgram(woodProg);
    glBindVertexArray(woodVao);
    glUniformMatrix4fv(woodModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, woodObject);

    glDrawElements(GL_TRIANGLE_FAN, 29, GL_UNSIGNED_INT, 0);
}

void GLWidget::renderCube(mat4 transform) {
    glUseProgram(cubeProg);
    glBindVertexArray(cubeVao);
    glUniformMatrix4fv(cubeModelMatrixLoc, 1, false, value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, textureObject);

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
    {
        GLint linked;
        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if ( !linked ) {
            GLsizei len;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetProgramInfoLog( program, len, &len, log );
            std::cout << "Shader linker failed: " << log << std::endl;
            delete [] log;
        }
    }

    return program;
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_W:
            forward = true;
            break;
        case Qt::Key_A:
            left = true;
            break;
        case Qt::Key_S:
            back = true;
            break;
        case Qt::Key_D:
            right = true;
            break;
        case Qt::Key_Tab:
            fly = !fly;
            break;
        case Qt::Key_Shift:
            down = true;
            break;
        case Qt::Key_Space:
            up = true;
            break;
        case Qt::Key_R:
            run = true;
            break;
        case Qt::Key_Q:
            quick = true;
            break;
        case Qt::Key_T:
            turtle = true;
            break;
        case Qt::Key_U:
            xscale = xscale + .5;
            break;
        case Qt::Key_I:
            if (xscale <= .5){
                xscale = .5;
            }
            else{
                xscale = xscale - .5;
            }
            break;
        case Qt::Key_J:
            yscale = yscale +.5;
            break;
        case Qt::Key_K:
            if (yscale <= .5){
                yscale = .5;
            }
            else{
                yscale = yscale - .5;
            }
            break;
        case Qt::Key_N:
            zscale = zscale +.5;
            break;
        case Qt::Key_M:
            if (zscale <= .5){
                zscale = .5;
            }
            else{
                zscale = zscale - .5;
            }
            break;
        case Qt::Key_Up:
            rowNum = rowNum + 1;
            break;
        case Qt::Key_Down:
            if (rowNum <= 1){
                rowNum = 1;
            }
            else{
                rowNum = rowNum - 1;
            }

    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_W:
            forward = false;
            break;
        case Qt::Key_A:
            left = false;
            break;
        case Qt::Key_S:
            back = false;
            break;
        case Qt::Key_D:
            right = false;
            break;
        case Qt::Key_Tab:
            //fly = false;
            break;
        case Qt::Key_Shift:
            down = false;
            break;
        case Qt::Key_Space:
            up = false;
            break;
        case Qt::Key_R:
            run = false;
            break;
        case Qt::Key_Q:
            quick = false;
            break;
        case Qt::Key_T:
            turtle = false;
            break;
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    vec2 pt(event->x(), event->y());
    lastPt = pt;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    vec2 pt(event->x(), event->y());
    vec2 d = pt-lastPt;

    yaw += d.x/100;
    pitch += d.y/100;

    if (pitch > M_PI/2){
        pitch = M_PI/2;
    } else if (pitch < -M_PI/2){
        pitch = -M_PI/2;
    }

    lastPt = pt;

}

void GLWidget::updateView(){
    yawMatrix = glm::rotate(mat4(1.0f), -yaw, vec3(0,1,0));
    pitchMatrix = glm::rotate(mat4(1.0f), -pitch, vec3(1,0,0));
    mat4 trans = glm::translate(mat4(1.0f), currentPosition);

    orientation = yawMatrix*pitchMatrix;
    viewMatrix = inverse(trans*orientation);

    glUseProgram(cubeProg);
    glUniformMatrix4fv(cubeViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(wallProg);
    glUniformMatrix4fv(wallViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(doorProg);
    glUniformMatrix4fv(doorViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(castleProg);
    glUniformMatrix4fv(castleViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(enderProg);
    glUniformMatrix4fv(enderViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(zombieProg);
    glUniformMatrix4fv(zombieViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(creepProg);
    glUniformMatrix4fv(creepViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(ceilingProg);
    glUniformMatrix4fv(ceilingViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(floorProg);
    glUniformMatrix4fv(floorViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(swordProg);
    glUniformMatrix4fv(swordViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(ironProg);
    glUniformMatrix4fv(ironViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(darkProg);
    glUniformMatrix4fv(darkViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(woodProg);
    glUniformMatrix4fv(woodViewMatrixLoc, 1, false, value_ptr(viewMatrix));

    glUseProgram(gridProg);
    glUniformMatrix4fv(gridViewMatrixLoc, 1, false, value_ptr(viewMatrix));

}
