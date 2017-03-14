#include <iostream>
#include "poligon.h"
#include "circle.h"
#include <termios.h> 
#include <thread>

FramePanel panelBig(900, 500, 200, 80);
Framebuffer fp;
Poligon player;
int positionY=495;
int something =870;
int somethingY=885;
int radius=10;
int count=0;
int somethingBatasBounce=200;


void SpawnCircle(){
    //MAX SPAWN 6 KALI
    
    while (count<=4){
        //Posisi mulai dinaikin
        if (somethingBatasBounce>0)
        {
            somethingBatasBounce--;
            if ((somethingBatasBounce%2)==0){
                somethingY++;
            }
            
        }
        
        
        usleep(3000);
        something-=1;
        if (something <50){
            somethingBatasBounce=200;
            something=870;
            radius+=5;
            somethingY-=107;
            count++;
            
        }  

    }
}

void detectKeyStroke(){
    
    while(1){
        char KeyPressed=getchar();
        if (KeyPressed=='\n') {  
            for (int i=0;i<100;i++){
                positionY-=1;
                player.emptyVector();
                usleep(3000);
            }
            sleep(0.5);
            for (int i=0;i<100;i++){
                positionY+=1;   
                player.emptyVector();
                usleep(3000);
            }
            
            
            
        }
    }
}

int main(int argc, char** argv){
    thread thread1(detectKeyStroke);
    thread thread2(SpawnCircle);
    bool notCollision=true;
    
    while(notCollision){
        
        player.drawPlayer(Point(250,positionY), Color::RED);
        player.draw(&panelBig);

        if (count <5){
            
            Circle Ball1(radius,something, somethingY, 1);
            notCollision=Ball1.draw(&panelBig, Color::GREEN);   
            fp.drawFrame(panelBig);
        }
        
        fp.Draw();
        panelBig.EmptyFrame();   
    }
    printf("HJAHAHAHAHAHAHAHAHAHAHAHAHAAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAAHAHAHA\n");
    thread1.detach();
    thread2.detach();
    return 0;
}
