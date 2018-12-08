#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <GLBatch.h>
#include <StopWatch.h>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

GLFrustum viewFrustum;

GLBatch    triangleBatch;
GLShaderManager    shaderManager;
GLTriangleBatch myCoolObject;
GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.0f, -0.5f, 0.0f };
///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 1000.0f);
}


///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context.
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
	// Blue background
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	shaderManager.InitializeStockShaders();

	// Load up a triangle
	/*triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();*/
	gltMakeTorus(myCoolObject, 0.4f, 0.15f, 30, 30);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}



///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	static CStopWatch rotTimer;
	float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Matrix Variables
	M3DMatrix44f mTranslate, mRotate, mModelview, mModelViewProjection;

	// Create a translation matrix to move the torus back and into sight
	m3dTranslationMatrix44(mTranslate, 0.0f, 0.0f, -2.5f);

	// Create a rotation matrix based on the current value of yRot
	m3dRotationMatrix44(mRotate, m3dDegToRad(yRot), 0.0f, 1.0f, 0.0f);

	// Add the rotation to the translation, store the result in mModelView
	m3dMatrixMultiply44(mModelview, mTranslate, mRotate);

	// Add the modelview matrix to the projection matrix, 
	// the final matrix is the ModelViewProjection matrix.
	m3dMatrixMultiply44(mModelViewProjection, viewFrustum.GetProjectionMatrix(), mModelview);

	GLfloat vRed[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_FLAT, mModelViewProjection, vRed);
	myCoolObject.Draw();


	// Perform the buffer swap to display back buffe
	glutSwapBuffers();
	glutPostRedisplay();

}


///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triangle");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();

	glutMainLoop();
	return 0;
}