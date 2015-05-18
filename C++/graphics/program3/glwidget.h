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
        void renderCube(mat4 transform);

        GLuint cubeProg;
        GLuint cubeVao;
        GLint cubeProjMatrixLoc;
        GLint cubeViewMatrixLoc;
        GLint cubeModelMatrixLoc;
        GLuint textureObject;

        void initializeCastle();
        void renderCastle(mat4 transform);

        GLuint castleProg;
        GLuint castleVao;
        GLint castleProjMatrixLoc;
        GLint castleViewMatrixLoc;
        GLint castleModelMatrixLoc;
        GLuint castleObject;

        void initializeWall();
        void renderWall(mat4 transform);

        GLuint wallProg;
        GLuint wallVao;
        GLint wallProjMatrixLoc;
        GLint wallViewMatrixLoc;
        GLint wallModelMatrixLoc;
        GLuint walltexObject;

        void initializeDoor();
        void renderDoor(mat4 transform);

        GLuint doorProg;
        GLuint doorVao;
        GLint doorProjMatrixLoc;
        GLint doorViewMatrixLoc;
        GLint doorModelMatrixLoc;
        GLuint doortexObject;

        void initializeFloor();
        void renderFloor(mat4 transform);

        GLuint floorProg;
        GLuint floorVao;
        GLint floorProjMatrixLoc;
        GLint floorViewMatrixLoc;
        GLint floorModelMatrixLoc;
        GLuint floortexObject;

        void initializeCeiling();
        void renderCeiling(mat4 transform);

        GLuint ceilingProg;
        GLuint ceilingVao;
        GLint ceilingProjMatrixLoc;
        GLint ceilingViewMatrixLoc;
        GLint ceilingModelMatrixLoc;
        GLuint ceilingtexObject;

        void initializeSword();
        void renderSword(mat4 transform);

        GLuint swordProg;
        GLuint swordVao;
        GLint swordProjMatrixLoc;
        GLint swordViewMatrixLoc;
        GLint swordModelMatrixLoc;
        GLuint swordtexObject;

        void initializeIron();
        void renderIron(mat4 transform);

        GLuint ironProg;
        GLuint ironVao;
        GLint ironProjMatrixLoc;
        GLint ironViewMatrixLoc;
        GLint ironModelMatrixLoc;
        GLuint ironObject;

        void initializeDark();
        void renderDark(mat4 transform);

        GLuint darkProg;
        GLuint darkVao;
        GLint darkProjMatrixLoc;
        GLint darkViewMatrixLoc;
        GLint darkModelMatrixLoc;
        GLuint darkObject;

        void initializeWood();
        void renderWood(mat4 transform);

        GLuint woodProg;
        GLuint woodVao;
        GLint woodProjMatrixLoc;
        GLint woodViewMatrixLoc;
        GLint woodModelMatrixLoc;
        GLuint woodObject;

        void initializeEnder();
        void renderEnder(mat4 transform);

        GLuint enderProg;
        GLuint enderVao;
        GLint enderProjMatrixLoc;
        GLint enderViewMatrixLoc;
        GLint enderModelMatrixLoc;
        GLuint enderObject;
        void initializeZombie();
        void renderZombie(mat4 transform);

        GLuint zombieProg;
        GLuint zombieVao;
        GLint zombieProjMatrixLoc;
        GLint zombieViewMatrixLoc;
        GLint zombieModelMatrixLoc;
        GLuint zombieObject;

        void initializeCreep();
        void renderCreep(mat4 transform);

        GLuint creepProg;
        GLuint creepVao;
        GLint creepProjMatrixLoc;
        GLint creepViewMatrixLoc;
        GLint creepModelMatrixLoc;
        GLuint creepObject;

        void initializeGrid();
        void renderGrid();

        GLuint gridProg;
        GLuint gridVao;
        GLint gridProjMatrixLoc;
        GLint gridViewMatrixLoc;
        GLint gridModelMatrixLoc;

        mat4 projMatrix;
        mat4 viewMatrix;
        mat4 castleMatrix;
        mat4 modelMatrix;
        mat4 enderMatrix;
        mat4 transform;
        mat4 swordMatrix;
        mat4 swordViewMat;

        mat4 yawMatrix;
        mat4 pitchMatrix;
        mat4 orientation;

        float yaw;
        float pitch;

        QTimer *timer;
        QImage img;

        bool forward;
        bool back;
        bool left;
        bool right;
        bool up;
        bool down;
        bool fly;
        bool run;
        bool quick;
        bool turtle;

        GLint lightPosition;

        vec3 forwardVec;
        vec3 rightVec;
        vec3 upVec;
        vec3 currentPosition;
        vec3 velocity;

        int width;
        int height;
        int rowNum;

        float speed;
        float xspace;
        float yspace;
        float zspace;
        float xscale;
        float yscale;
        float zscale;

        glm::vec2 lastPt;
        void updateView();

        GLint modelLightPosLoc;
        GLint modelLightColorLoc;
        GLint modelLightIntensityLoc;

        GLint modelDiffuseColorLoc;
        GLint modelAmbientColorLoc;
};

#endif
