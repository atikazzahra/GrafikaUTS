//#include <ncurses.h>
#include <iostream>
#include "poligon.h"
#include "parser.h"
#include <pthread.h>
#include <termios.h>

static struct termios oldt;

pthread_t t_bullet;
std::vector<Point> PTree;
std::vector<Poligon> vPoligon;
FramePanel panelMain(550, 500, 0, 0);
bool bTree = false;
bool bRoad = false;
bool bBuilding = false;
Parser parse2;
Framebuffer a;
std::vector< std::vector<Point> > v;
Parser parse;
std::vector< std::vector<Point> > PJalan;
Parser company;
std::vector<std::vector<Point>> PCompany;
Parser uts;
std::vector<std::vector<Point>> PUts;
Parser quiz;
std::vector<std::vector<Point> > PQuiz;
Parser tubes;
std::vector<std::vector<Point> > PTubes;
Parser pencil;
std::vector<std::vector<Point> > PPencil;
std::vector<std::vector<Point> > PBullet;
std::vector<std::vector<Point> > PTarget;


FramePanel panelSmall(100, 100, 50, 50);
FramePanel panelBig(500, 500, 500, 0);
FramePanel panelMiniMap(100, 100, 250, 600);
FramePanel panelForShooter(1355, 750, 0, 0);

int score = 0, level = 1, shooterXPos = 87, shooterYPos = 624, nBullet;
bool isEnd = false;
char c;

void *controller(void *args){
    while(!isEnd){
        c = getchar();
        if (c == 'q'){
            bTree = true;
            c='.';
        }
        if (c == 'w'){
            bTree = false;
            c='.';
        }
        if (c == 'a'){
            bRoad = true;
            c='.';
        }
        if (c == 's'){
            bRoad = false;
            c='.';
        }
        if (c == 'z'){
            bBuilding = true;
            c='.';
        }
        if (c == 'x'){
            bBuilding = false;
            c='.';
        }
        if(c == 'j'){
            if(panelSmall.getXMin() > 10){
                panelSmall.setXMin(panelSmall.getXMin() - 10);
            }
            c='.';
        }else if(c == 'k'){
            if(panelSmall.getYMin() > 10){
                panelSmall.setYMin(panelSmall.getYMin() + 10);
            }
            c='.';
        }else if (c == 'l'){
            if(panelSmall.getXMin() < panelMain.getXSize() - panelSmall.getXMin()-10){
                panelSmall.setXMin(panelSmall.getXMin() + 10);
            }
            c='.';
        }else if(c == 'i'){
            if(panelSmall.getYMin() < panelMain.getXSize() - panelSmall.getYMin()){
                panelSmall.setYMin(panelSmall.getYMin() - 10);
            }
            c='.';
        }else if(c == 'b'){
            panelSmall.setXSize(panelSmall.getXSize()+10);
            panelSmall.setYSize(panelSmall.getYSize()+10);
            c='.';
        }else if(c == 'n'){
            panelSmall.setXSize(panelSmall.getXSize()-10);
            panelSmall.setYSize(panelSmall.getYSize()-10);
            c='.';
        }
        else if (c == 'd') {
            for (int i = 0; i < PPencil.size(); i++) {
                for (int j = 0; j < PPencil[i].size(); j++) {
                    Point p = PPencil[i].at(0);
                    PPencil[i].erase(PPencil[i].begin());
                    p.setX(p.getX() - 5);
                    PPencil[i].push_back(p);
                }
            }
            shooterXPos -= 5;
            c = '.';
        }
        else if (c == 'g') {
            // if (panelForShooter.getXMin() < 1350)
            //     panelForShooter.setXMin(panelForShooter.getXMin() + 5);
            for (int i = 0; i < PPencil.size(); i++) {
                for (int j = 0; j < PPencil[i].size(); j++) {
                    Point p = PPencil[i].at(0);
                    PPencil[i].erase(PPencil[i].begin());
                    p.setX(p.getX() + 5);
                    PPencil[i].push_back(p);
                }
            }
            shooterXPos += 5;
            c = '.';
        }
        else if (c == 'f') {
            for (int i = 0; i < PPencil.size(); i++) {
                for (int j = 0; j < PPencil[i].size(); j++) {
                    Point p = PPencil[i].at(0);
                    PPencil[i].erase(PPencil[i].begin());
                    p.setY(p.getY() + 5);
                    PPencil[i].push_back(p);
                }
            }
            shooterYPos += 5;
            c = '.';
        }
        else if (c == 'r') {
            for (int i = 0; i < PPencil.size(); i++) {
                for (int j = 0; j < PPencil[i].size(); j++) {
                    Point p = PPencil[i].at(0);
                    PPencil[i].erase(PPencil[i].begin());
                    p.setY(p.getY() - 5);
                    PPencil[i].push_back(p);
                }
            }
            shooterYPos -= 5;
            c = '.';
        }
        else if(c == 'm'){
            break;
        }

    }
}

void drawTree(){
    for(int i = 0; i < PTree.size(); i++){
        Poligon Shape = Poligon();
        Shape.drawTree(PTree[i]);
        Shape.draw(&panelMain);
    }
}

void drawBuilding(){
    for(int i = 0; i < v.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(v[i]);
        Shape.draw(&panelMain);
    }   
}

void drawRoad(){
    for(int i = 0; i < PJalan.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(PJalan[i]);
        Shape.setLineColor(Color::RED);
        Shape.setAllLineColor();
        Shape.draw(&panelMain);
    }
}

void poliRoad(){
    for(int i = 0; i < PJalan.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(PJalan[i]);
        Shape.setLineColor(Color::RED);
        Shape.setAllLineColor();
        vPoligon.push_back(Shape);
    }
}

void poliBuild(){
    for(int i = 0; i < v.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(v[i]);
        vPoligon.push_back(Shape);
    }   
}

void poliPlant(){
     for(int i = 0; i < PTree.size(); i++){
        Poligon Shape = Poligon();
        Shape.drawTree(PTree[i]);
        vPoligon.push_back(Shape);
    }
}

void drawPencil() {
    for (int i = 0; i < PPencil.size(); i++) {
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PPencil[i]);
        shape.setLineColor(Color::WHITE);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }
}

void drawTarget() {
    for (int i = 0; i < PTarget.size(); i++) {
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PTarget[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }

    // for (int i = 1; i < PTarget.size(); i++) {
    //     int x1 = P[i].at()
    // }
}

void drawUTS() {
    for (int i = 0; i < PTarget.size(); i++) {
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PUts[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelMain);
    }
}

void drawTubes() {
    for (int i = 0; i < PTubes.size(); i++) {
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PTubes[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelMain);
    }
}

void drawKP() {
    for (int i = 0; i < PCompany.size(); i++) {
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PCompany[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelMain);
    }
}

void drawQuiz() {
    for (int i = 0; i < PQuiz.size(); i++) {
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PQuiz[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }
}

void moveVertical(std::vector<std::vector<Point> > * P, int dy) {
    if (P->size() != 0) {
        Point p[P->size()][2];
        int nBullet = P->size();
        for(int i = 0; i < nBullet; i++) {
            p[i][0] = P[0][0].at(0);
            p[i][1] = P[0][0].at(1);
            // P[i].erase(P[i].begin());

            // printf("%d\n", (int) P[0][i].size());
            // printf("%d\n", p[i][0].getY());
            p[i][0].setY(p[i][0].getY() + dy);
            p[i][1].setY(p[i][1].getY() + dy);
            std::vector<Point> pointVTemp;
            pointVTemp.push_back(p[i][0]);
            pointVTemp.push_back(p[i][1]);
            P->erase(P->begin());
            P->push_back(pointVTemp);

            Poligon shape = Poligon();
            shape.makeLineFromArrPoint(P[0][i]);
            shape.setLineColor(Color::WHITE);
            shape.setAllLineColor();
            shape.draw(&panelForShooter);
        }
       
        for(int i = 0; i < P->size(); i++) {
            if (p[i][0].getY() < 10) {
                P->erase(P->begin());
            }
        }
    }
}

void * shoot(void * arg) {
    // int bulletYPos = shooterYPos;
    // printf("%d\n", bulletYPos);
    while(!isEnd) {
        if (c == '\n') {
            int x[1] = {shooterXPos};
            int y[2] = {shooterYPos, shooterYPos - 5};
            for (int i = 0; i < 1; i++ ) {
                Point p1 (x[0], y[0]);
                Point p2 (x[0], y[1]);
                std::vector<Point> pointVTemp;
                pointVTemp.push_back(p1);
                pointVTemp.push_back(p2);
                PBullet.push_back(pointVTemp);
            }
            // printf("k\n");
            c = '.';
        }
    }
}

bool isCollison(std::vector<std::vector<Point> > obj, Color color) {
    if (obj.size() != 0) {
        for (int i = 0; i < obj.size(); i++) {
            Point p1 = obj[i].at(0);
            Point p2 = obj[i].at(1);
            // printf("x %d y %d\n", p.getX(), p.getY());
            // printf("%d %d %d\n", (int)panelForShooter.get(p).getR(), (int)panelForShooter.get(p).getG(), (int)panelForShooter.get(p).getB());
            int y = p2.getY();
            for (int j = 0; j < abs(p2.getY() - p1.getY()); j++) {
                if (panelForShooter.get(p2.getX(), y) == color) {
                    PBullet.clear();
                    // printf("d\n");
                    return true;
                }
                y++;    
            }
        }
    }

    return false;
}

/*Digunakan biar gak perlu pencet enter lagi
Dimasukin kedalem loop yang di main*/
void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt);  /* Save terminal settings */
    newt = oldt;  /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
    tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}

int main(int argc, char** argv){

    parse.parseAdi("bangunan.txt");
    parse.parseTree("tree.txt");
    v = parse.getPoints();
    PTree = parse.getTrees();
    parse2.parseAdi("jalan.txt");
    PJalan = parse2.getPoints();
    company.parseAdi("company.txt");
    uts.parseAdi("UTS.txt");
    quiz.parseAdi("quiz.txt");
    tubes.parseAdi("tubes.txt");
    pencil.parseAdi("pencil.txt");
    PPencil = pencil.getPoints();
    // poliRoad();
    // poliPlant();
    // poliBuild();

    pthread_t t_shoot;
    pthread_create(&t_shoot, NULL, shoot, NULL);
    pthread_create(&t_bullet, NULL, controller, NULL);
    while(!isEnd){
    	disable_waiting_for_enter();
        //Draw Bangunan
        // if(bBuilding){   
        //     drawBuilding();
        // }

        // if(bTree){   
        //     //Draw Tree 
        //     drawTree();
        // }

        // if(bRoad){    
        //     drawRoad();
        // }

        if (level == 1) PTarget = quiz.getPoints();
        else if (level == 2) PTarget = tubes.getPoints();
        else if (level == 3) PTarget = company.getPoints();
        else if (level == 4) PTarget = uts.getPoints();
        drawTarget();
        //Minimap

        bool isCollide = isCollison(PBullet, Color::RED); 
        if (isCollide && level == 4) isEnd = true;
        else if (isCollide) level++;

        drawPencil();
        moveVertical(&PBullet, -10);
        // for(int i = 0; i < vPoligon.size(); i++){
        //     Poligon Shape = Poligon();
        //     Shape = vPoligon[i];
        //     Shape.scalePolygon(0.5,0.5);
        //     Shape.draw(&panelMiniMap);
        // }
        
        // //ZoomSelector
        // for(int i = 0; i<vPoligon.size();i++){
        //     vPoligon[i].drawInside(&panelSmall, &panelBig);
        // }

        //draw semua
        // a.drawFrame(panelMain);
        // a.drawFrame(panelMiniMap);
        // a.drawFrame(panelBig);
        // a.drawFrame(panelSmall);
        
        a.drawFrame(panelForShooter);
        // a.Draw();
        

        panelForShooter.EmptyFrame();
        panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
        // printf("mas\n");
        // usleep(500);
    }
    pthread_join(t_bullet, NULL);
    pthread_join(t_shoot, NULL);

    return 0;
}
