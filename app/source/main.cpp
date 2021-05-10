#include "App.h"
#include <time.h> // time
#include <cstdlib>	// srand

int main()
{
	srand((unsigned int)time(NULL));
	App app(1250, 800, "Minecheap", "resources/Images/Logo/logo.png", true);
	app.Run();

	return 0;
}