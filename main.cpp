#include "Application.h"

int main()
{
	Application* Instance = new Application("data.json");
	Instance->run();
	delete Instance;
	return EXIT_SUCCESS;
}