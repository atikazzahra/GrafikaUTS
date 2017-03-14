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


FramePanel panelSmall(100, 100, 50, 50);
FramePanel panelBig(500, 500, 500, 0);
FramePanel panelMiniMap(100, 100, 250, 600);
//FramePanel panelForShooter(1355, 750, 0, 0);
FramePanel panelForShooter(1055, 750, 0, 0);

int score = 0, level = 1, shooterXPos = 109, shooterYPos = 548, nBullet;
int kpIdx = 0;
int utsIdx = 0;
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
                    if (p.getX() > 5)
                    	p.setX(p.getX() - 5);
                    PPencil[i].push_back(p);
                }
            }
            shooterXPos -= 5; //pinddahin moncong pensil kekiri -5
            c = '.';
        }
        else if (c == 'g') {
            for (int i = 0; i < PPencil.size(); i++) {
                for (int j = 0; j < PPencil[i].size(); j++) {
                    Point p = PPencil[i].at(0);
                    PPencil[i].erase(PPencil[i].begin());
                    if (p.getX() < 1050)
                    	p.setX(p.getX() + 5);
                    PPencil[i].push_back(p);
                }
            }
            shooterXPos += 5; //pinddahin moncong pensil kekanan +5
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

void drawUTS() {
    for (int i = 0; i < PUts.size(); i++) {
		if (utsIdx % 2 == 0) {
			for (int j = 0; j < PUts[i].size(); j++) {
				PUts[i][j].setX(PUts[i][j].getX() + 10);
				PUts[i][j].setY(PUts[i][j].getY() + 12);
			}
		} else {
			for (int j = 0; j < PUts[i].size(); j++) {
				PUts[i][j].setX(PUts[i][j].getX() + 10);
				PUts[i][j].setY(PUts[i][j].getY() - 6);	
			}			
		}
		if (PUts[0][0].getX() > 1055) {
			isEnd = true; //Kalah
		}
		utsIdx++;

        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PUts[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }
}

void drawTubes() {
    for (int i = 0; i < PTubes.size(); i++) {
		for (int j = 0; j < PTubes[i].size(); j++) {
			PTubes[i][j].setX(PTubes[i][j].getX() + 8);
			PTubes[i][j].setY(PTubes[i][j].getY() + 8);
		}
		if (PTubes[0][0].getX() > 1055) {
			isEnd = true; //Kalah
		}
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PTubes[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }
}

void drawKP() {
    for (int i = 0; i < PCompany.size(); i++) {
		if (kpIdx % 2 == 0) {
			for (int j = 0; j < PCompany[i].size(); j++) {
				PCompany[i][j].setX(PCompany[i][j].getX() + 10);
			}
		} else {
			for (int j = 0; j < PCompany[i].size(); j++) {
				PCompany[i][j].setY(PCompany[i][j].getY() + 10);
			}			
		}
		if (PCompany[0][0].getX() > 1055) {
			isEnd = true; //Kalah
		}
		kpIdx++;
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PCompany[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }
}

void drawQuiz() {
    for (int i = 0; i < PQuiz.size(); i++) {
		for (int j = 0; j < PQuiz[i].size(); j++) {
			PQuiz[i][j].setX(PQuiz[i][j].getX() + 5);
		}
		if (PQuiz[0][0].getX() > 1055) {
			isEnd = true; //Kalah
		}
        Poligon shape = Poligon();
        shape.makeLineFromArrPoint(PQuiz[i]);
        shape.setLineColor(Color::RED);
        shape.setAllLineColor();
        shape.draw(&panelForShooter);
    }
}

/*pindahin object dari atas ke bawah dan sebaliknya
    kalau mau dari atas ke bawah tanda dy +, sebaliknya - */
void moveVertical(std::vector<std::vector<Point> > * P, int dy) {
    if (P->size() != 0) {
        Point p[P->size()][2];
        int nBullet = P->size();
        for(int i = 0; i < nBullet; i++) {
            p[i][0] = P[0][0].at(0);
            p[i][1] = P[0][0].at(1);

            //kepala peluru ditambah dy
            //ekor peluru ditambah dy
            p[i][0].setY(p[i][0].getY() + dy);
            p[i][1].setY(p[i][1].getY() + dy);
            std::vector<Point> pointVTemp;
            pointVTemp.push_back(p[i][0]);
            pointVTemp.push_back(p[i][1]);

            //dihapus biar gak jadi panjang pelurunya
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

/*prosedur untuk membuat peluru (bukan gerakin dari bawah ke atas)
    peluru dibuat dan dimasukkan kedalam vector
    tujuannya biar bisa nembak beberapa kali dalam satu waktu
*/
void * shoot(void * arg) {
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
            c = '.';
        }
    }
}

//cek tabrakan antara 2 object
bool isCollison(std::vector<std::vector<Point> > obj, Color color) {
    if (obj.size() != 0) {
        for (int i = 0; i < obj.size(); i++) {
            Point p1 = obj[i].at(0);
            Point p2 = obj[i].at(1);
            int y = p2.getY();

            //cek collison dari kepala peluru sampai ekor apakah ada yang kena ke object
            for (int j = 0; j < abs(p2.getY() - p1.getY()); j++) {
                if (panelForShooter.get(p2.getX(), y).equals(color)) {
                    PBullet.clear();
                    return true;
                }
                y++;    
            }
        }
    }

    return false;
}

/* flood fill algorithm*/
void floodFill(FramePanel * vp, int x, int y, Color color) {
    int tempX, tempY;
    if((x > 0) && (x < 1055) && (y > 0) && (y < 750)) {
        tempX = x; tempY = y+1;
        if (!vp->get(tempX, tempY).equals(color)) {
            vp->set(color, tempX, tempY);
            floodFill(vp, tempX, tempY, color);
        }
        
        tempX = x; tempY = y-1;
        if (!vp->get(tempX, tempY).equals(color)) {
            vp->set(color, tempX, tempY);
            floodFill(vp, tempX, tempY, color);
        }

        tempX = x+1; tempY = y;
        if (!vp->get(tempX, tempY).equals(color)) {
            vp->set(color, tempX, tempY);
            floodFill(vp, tempX, tempY, color);
        }
        
        tempX = x-1; tempY = y;
        if (!vp->get(tempX, tempY).equals(color)) {
            vp->set(color, tempX, tempY);
            floodFill(vp, tempX, tempY, color);
        }
    }
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

    parse.parseAdi("shooter/bangunan.txt");
    parse.parseTree("shooter/tree.txt");
    v = parse.getPoints();
    PTree = parse.getTrees();
    parse2.parseAdi("shooter/jalan.txt");
    PJalan = parse2.getPoints();
    company.parseAdi("shooter/company.txt");
    uts.parseAdi("shooter/UTS.txt");
    quiz.parseAdi("shooter/quiz.txt");
    tubes.parseAdi("shooter/tubes.txt");
    pencil.parseAdi("shooter/pencil.txt");
    PPencil = pencil.getPoints();
    // poliRoad();
    // poliPlant();
    // poliBuild();
	PQuiz = quiz.getPoints();
	PTubes = tubes.getPoints();
	PCompany = company.getPoints();
	PUts = uts.getPoints();


    pthread_t t_shoot;
    pthread_create(&t_shoot, NULL, shoot, NULL);
    pthread_create(&t_bullet, NULL, controller, NULL);
    while(!isEnd){
    	disable_waiting_for_enter();

        if (level == 1) drawQuiz();
        else if (level == 2) drawTubes();
        else if (level == 3) drawKP();
        else if (level == 4) drawUTS();
        //Minimap

        bool isCollide = isCollison(PBullet, Color::RED); 
        if (isCollide && level == 4) isEnd = true;
        else if (isCollide) level++;

        drawPencil();

        //warnain pencil
        floodFill(&panelForShooter, shooterXPos, 580, Color::WHITE);

        moveVertical(&PBullet, -10);
        
        a.drawFrame(panelForShooter);
        

        panelForShooter.EmptyFrame();
        panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
    }
    pthread_join(t_bullet, NULL);
    pthread_join(t_shoot, NULL);

    return 0;
}
