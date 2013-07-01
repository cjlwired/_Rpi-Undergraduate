

#include "DVC_SdlEngine.h"
#include "App.h"
#include "DVC_AppConfig.h" //defines DVC_DATA_DIR

//include the gui if enabled
#ifdef USE_GUI
#include "DVC_GuiGtkmm.h"
#endif

#include <string>

int main(int argc, char **argv)
{
	App app(argc, argv);
	DVC_SdlEngine sdl;

	// set the path to the pref file
	app.SetPrefFile(std::string(DVC_DATA_DIR) + "/car.xml");

#ifdef USE_GUI
	DVC_GuiGtkmm gui(argc, argv);
	sdl.Start(app, &gui);
#else
	sdl.Start(app);
#endif

	return 0;
}
