#ifndef __GLWIDGET__INCLUDE__
#define __GLWIDGET__INCLUDE__

#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS

using glm::mat4;

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

    private:
        void initializeCube();
        void renderCube(mat4 transform);

        GLuint cubeProg;
        GLuint cubeVao;
        GLint cubeProjMatrixLoc;
        GLint cubeViewMatrixLoc;
        GLint cubeModelMatrixLoc;

        void updateModelMatrix();

        float sx;
        float sy;
        float sz;
        float xspace;
        float yspace;
        float zspace;

        void initializeGrid();
        void renderGrid();

        GLuint gridProg;
        GLuint gridVao;
        GLint gridProjMatrixLoc;
        GLint gridViewMatrixLoc;
        GLint gridModelMatrixLoc;

        GLint lightPosition;
        GLfloat diff;
        GLfloat ambient;

        mat4 projMatrix;
        mat4 viewMatrix;
        mat4 modelMatrix;
        mat4 transform;
        mat4 modelGridMatrix;
        mat4 totRotation;

        int width;
        int height;
        int rowSize;
        int wallType;
        int colSize;

        glm::vec3 p;
        glm::vec3 lastVPt;
        glm::vec3 pointOnVirtualTrackball(const glm::vec2 &pt);
};

#endif
