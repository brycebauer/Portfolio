#ifndef __GLWIDGET__INCLUDE__
#define __GLWIDGET__INCLUDE__


#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <glm/glm.hpp>
#include <vector>
#include <string>

// glm by default uses degrees, but that functionality
// is deprecated so GLM_FORCE_RADIANS turns off some
// glm warnings

#define GLM_FORCE_RADIANS

using glm::vec2;
using glm::vec3;
using std::vector;

class Color {
    public:
        float r;
        float g;
        float b;
        Color() : r(0), g(0), b(0) {}
        Color(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {}
};

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {

    Q_OBJECT

    public:
        GLWidget(char* imagepath, QWidget *parent=0);
        ~GLWidget();

    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void fill(int x, int y, float red, float blue, float green);

    private:
        GLuint loadShaders();
        static const GLchar* readShader(const char* filename);

        GLuint positionBuffer;
        GLuint colorBuffer;
        bool outline;
        GLenum drawMode;
        int width, heigth;
        int img_width, img_height;
        glm::mat4 projection;
        //GLint projectionIndex;
        std::vector<vec2> pts;
        std::vector<vec3> ptClr;
        //vector <vec2> pts;
        int num_pts;
        int num_mode;
        QImage image;
        GLuint uniformLoc;
        GLuint program1;
        GLuint vao;
        float ptSize;
};

#endif
