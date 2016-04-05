// Include OpenGL ES Engine utils
#include <es_util.h>
#include "PathFindingApp.h"


using namespace yam2d;

namespace
{
	PathFindingApp * g_app = 0;
}


// Initialize the game
bool init(ESContext *esContext)
{
	g_app = new PathFindingApp();
	return true;
}

// Deinitialize the game
void deinit(ESContext *esContext)
{
	// Delete map.
	delete g_app;
}


// Update game
void update(ESContext* ctx, float deltaTime)
{
	if (!g_app->update(ctx, deltaTime))
	{
		// Quit!
		esQuitApp(ctx);
	}
}


// Draw game
void draw(ESContext *ctx)
{
	// Render app
	g_app->render(ctx);
}


int main(int argc, char *argv[])
{
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Path finfing example", 1280, 720, ES_WINDOW_DEFAULT|ES_WINDOW_RESIZEABLE);

	esRegisterInitFunc(&esContext, init);
	esRegisterDrawFunc(&esContext, draw);
	esRegisterUpdateFunc(&esContext, update);
	esRegisterDeinitFunc(&esContext, deinit);

	esMainLoop(&esContext);
	return 0;
}
