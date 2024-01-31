#include "asstes.h"
#include "Window.h"
#include <crtdbg.h>
using namespace std;
int main() 
{
	Window window;
	while (window.wypierdol)
	{	
		window.menu();
	}
	
	
	return 0;
}