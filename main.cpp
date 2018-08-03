
#include "Window.h"

int main(int argc, char *argv[])
{
	Window window("test", 640, 480);

	while (!window.isClosed())
	{
		window.pollEvents();
		window.clear();
	}

	return 0;
}

/*

window.show(){
while(!window.isClosed())
{
window.clear();
window.render();
window.pollEvents();
}
}


window.render()
{
foreach(obj int objs)
{
1. obj.render();
2. obj.getPixelsForRender(); renderPixels(pixels);
3. obj == pixelsForRender; renderPixels(pixels);
4. global pixels += obj.getPixels();
}
4.renderPixels(global pixels);
}


different render functions(find best)
Ray tracing

camera+transform objects

obj picker
*/