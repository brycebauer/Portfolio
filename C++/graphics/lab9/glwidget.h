#ifndef __GLWIDGET__INCLUDE__
#define __GLWIDGET__INCLUDE__

#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <QTimer>
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS

using glm::mat3;
using glm::mat4;
using glm::vec3;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core { 
    Q_OBJECT

    public:
        GLWidget(QWidget *parent=0);
        ~GLWidget();

        GLuint loadShaders(const char* vertf, const char* fragf);
    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);

    public slots:
        void animate();

    private:
        void initializeCube();
        void renderCube();

        GLuint cubeProg;
        GLuint cubeVao;
        GLint cubeProjMatrixLoc;
        GLint cubeViewMatrixLoc;
        GLint cubeModelMatrixLoc;
        GLuint textureObject;

        void initializeGrid();
        void renderGrid();

        GLuint gridProg;
        GLuint gridVao;
        GLint gridProjMatrixLoc;
        GLint gridViewMatrixLoc;
        GLint gridModelMatrixLoc;

        mat4 projMatrix;
        mat4 viewMatrix;
        mat4 modelMatrix;

        mat4 yawMatrix;
        mat4 pitchMatrix;
        mat4 orientation;

        float yaw;
        float pitch;

        QTimer *timer;

        // Part 1 - Add two mat4 variables for pitch and yaw.
        // Also add two float variables for the pitch and yaw angles.

        // Part 2 - Add a QTimer variable for our render loop.

        bool forward;
        bool back;
        bool left;
        bool right;
        bool up;
        bool down;
        bool fly;

        // Part 3 - Add state variables for keeping track
        //          of which movement keys are being pressed
        //        - Add two vec3 variables for position and velocity.
        //        - Add a variable for toggling fly mode

        vec3 forwardVec;
        vec3 rightVec;
        vec3 upVec;
        vec3 currentPosition;
        vec3 velocity;

        int width;
        int height;

        float speed;

        glm::vec2 lastPt;
        void updateView();
};

#endif
