//#include <GLTools.h>            // OpenGL toolkit
//#include <GLShaderManager.h>    // Shader Manager Class
//
//#ifdef __APPLE__
//#include <glut/glut.h>          // OS X version of GLUT
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>            // Windows FreeGlut equivalent
//#endif
//
//GLBatch    triangleBatch;
//GLShaderManager    shaderManager;
//GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
//	0.5f, 0.0f, 0.0f,
//	0.0f, -0.5f, 0.0f };
/////////////////////////////////////////////////////////////////////////////////
//// Window has changed size, or has just been created. In either case, we need
//// to use the window dimensions to set the viewport and the projection matrix.
//void ChangeSize(int w, int h)
//{
//	glViewport(0, 0, w, h);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//// This function does any needed initialization on the rendering context.
//// This is the first opportunity to do any OpenGL related tasks.
//void SetupRC()
//{
//	// Blue background
//	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//
//	shaderManager.InitializeStockShaders();
//
//	// Load up a triangle
//	triangleBatch.Begin(GL_TRIANGLES, 3);
//	triangleBatch.CopyVertexData3f(vVerts);
//	triangleBatch.End();
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//// Called to draw scene
//void RenderScene(void)
//{
//	// Clear the window with current clearing color
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
//	triangleBatch.Draw();
//
//	// Perform the buffer swap to display back buffe
//	glutSwapBuffers();
//	glutPostRedisplay();
//
//}
//void specialKey(int key, int x, int y) {
//	GLfloat stepSize = 0.025f;
//	GLfloat blockX = vVerts[0];
//	GLfloat blockY = vVerts[7];
//	if (key == GLUT_KEY_UP) {
//		blockY += stepSize;
//	}
//	if (key == GLUT_KEY_DOWN) {
//		blockY -= stepSize;
//	}
//	if (key == GLUT_KEY_LEFT) {
//		blockX -= stepSize;
//	}
//	if (key == GLUT_KEY_RIGHT) {
//		blockX += stepSize;
//	}
//	if (blockX < -1.0f) blockX = -1.0f;
//	if (blockX > 1.0f) blockX = 1.0f;
//	if (blockY < -1.0f) blockY = -1.0f;
//	if (blockY > 1.0f) blockY = 1.0f;
//	vVerts[0] = blockX;
//	vVerts[7] = blockY;
//	triangleBatch.CopyVertexData3f(vVerts);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Main entry point for GLUT based programs
//int main(int argc, char* argv[])
//{
//	gltSetWorkingDirectory(argv[0]);
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Triangle");
//	glutReshapeFunc(ChangeSize);
//	glutDisplayFunc(RenderScene);
//	glutSpecialFunc(specialKey);
//	GLenum err = glewInit();
//	if (GLEW_OK != err) {
//		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
//		return 1;
//	}
//
//	SetupRC();
//
//	glutMainLoop();
//	return 0;
//}