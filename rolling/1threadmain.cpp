#include <iostream>
#include "poligon.h"
#include "circle.h"

int main(int argc, char** argv){
    FramePanel panelBig(900, 500, 200, 80);
    Framebuffer fp;
    
    while(1){
		Poligon player;
		player.drawPlayer(Point(100,495));
		player.draw(&panelBig);
		Circle Ball1(15, 870, 970, 1);
		Ball1.draw(&panelBig);
       
        fp.drawFrame(panelBig);
        fp.Draw();
        panelBig.EmptyFrame();
    }

    return 0;
}
