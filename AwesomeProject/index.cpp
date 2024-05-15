#include <GL\glut.h>  //Thêm thu vien glut.h vào chuong trình de làm viec voi do hoa OpenGL
#include <stdlib.h> //Thêm thu vien stdlib.h vào chuong trình de quan lý bo nho và so ngau nhiên.
#include <stdio.h>  //Thêm thu vien stdio.h vào chuong trình de thao tác voi dau vào/dau ra.
#include <iostream> // //Thêm thu vien stdio.h vào chuong trình de thao tác voi d?u vào/dau ra voi c++
#include <cmath>  //Thêm thu vien cmath vào chuong trình d? s? d?ng các hàm toán hoc.

// khai bao cac bien bat tat den o tuong va tu
GLboolean redFlag = true, switchOne = false, switchTwo = false, switchLamp = false, amb1 = true, diff1 = true, spec1 = true, amb2 = true, diff2 = true, spec2 = true, amb3 = true, diff3 = true, spec3 = true;

// chieu dai va rong hien thi man hinh
double windowHeight = 800, windowWidth = 600;
// Kích thuoc

// tao struct camera kiem soat goc nhin
struct Camera {
    float eyeX;
    float eyeY;
    float eyeZ;
    float centerX;
    float centerY;
    float centerZ;
    float upX;
    float upY;
    float upZ;
};

// cai mac dinh khi vao cho camera 
Camera camera = {12.0, 5.5, 20.0, 1.0, 1.0, 1.0, 0.0, 100.0, 0.0};

// chua cac dinh khoi lap phuong
static GLfloat v_cube[8][3] = {
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

// chua cac dinh tao mat phang
static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, //back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


// Hàm tính toán và dat vecto pháp tuyen cua mot mat phang dua trên ba diem trên mat phang dó.
static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}


//nhan vào các thông so de thiet lap vat lieu và ve mot hình cau trong không gian 3D.
void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(3.0, 20, 16);
}

//  nhan vào các thông so de thiet lap vat lieu và ve mot hình lap phuong trong không gian 3D.
void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
	//Mang chua màu sac cua vat lieu khi không có ánh sáng nào chieu vào, duoc thiet lap là màu den và do trong suat là 1.0.
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 }; 
    //Mang chua màu sac cua ánh sáng phan xa xung quanh cua vat lieu
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    //Mang chua màu sac cua ánh sáng phan xx khác cua vat lieu,
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    //duoc thiet lap là màu trang.
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    // Mang chua do bóng cua vat lieu // shine
	 GLfloat mat_shininess[] = { shine };

   //mau sac phan xa
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    //do bong
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // ve hinh vuong
    glBegin(GL_QUADS);

    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
            v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
            v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
		// ve mat phang
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

//hinh vuong (lam cho be boi)
void drawCube2(GLfloat colorX, GLfloat colorY, GLfloat colorZ, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { colorX, colorY, colorZ, 1.0 }; // Màu xanh cho toàn b? kh?i
    GLfloat mat_diffuse[] = { colorX, colorY, colorZ, 1.0 }; // Màu xanh cho toàn b? kh?i
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
            v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
            v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        // v? m?t ph?ng
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}


// ve anh sao tren tranh
void drawStar(float size) {
    glBegin(GL_TRIANGLES);
    // Các d?nh c?a ngôi sao
    glVertex3f(0.0f, 0.0f, 0.0f); // Ð?nh chính gi?a
    glVertex3f(0.0f, size, 0.0f); // Ð?nh trên
    glVertex3f(size * 0.5f, size * 0.7f, 0.0f); // Ð?nh phía du?i bên ph?i

    glVertex3f(0.0f, 0.0f, 0.0f); // Ð?nh chính gi?a
    glVertex3f(size * 0.5f, size * 0.7f, 0.0f); // Ð?nh phía du?i bên ph?i
    glVertex3f(size * 0.5f, size * 0.3f, 0.0f); // Ð?nh phía trên bên ph?i

    glVertex3f(0.0f, 0.0f, 0.0f); // Ð?nh chính gi?a
    glVertex3f(size * 0.5f, size * 0.3f, 0.0f); // Ð?nh phía trên bên ph?i
    glVertex3f(size * 0.8f, 0.0f, 0.0f); // Ð?nh phía du?i bên trái

    glVertex3f(0.0f, 0.0f, 0.0f); // Ð?nh chính gi?a
    glVertex3f(size * 0.8f, 0.0f, 0.0f); // Ð?nh phía du?i bên trái
    glVertex3f(size * 0.2f, 0.0f, 0.0f); // Ð?nh phía trên bên trái

    glVertex3f(0.0f, 0.0f, 0.0f); // Ð?nh chính gi?a
    glVertex3f(size * 0.2f, 0.0f, 0.0f); // Ð?nh phía trên bên trái
    glVertex3f(0.0f, size, 0.0f); // Ð?nh trên

    glEnd();
}

// thiet lap cac mat phang cho phong
void room()
{
    // Sau
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(3.5, 2, 0.05);
    drawCube1(0.6, 0.8, 0.4, 0.6, 0.8, 0.4);
    glPopMatrix();

    // Trái
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(0.05, 2, 3.75);
    drawCube1(1.0, 0.4, 0.4, 1.0, 0.4, 0.4);
    glPopMatrix();

    // Tran
    glPushMatrix();
    glTranslatef(0, 6, 0);
    glScalef(3.5, 0.05, 3.75);
    drawCube1(1.0, 0.9, 0.8, 0.5, 0.45, 0.4);
    glPopMatrix();

    // Sàn
    glPushMatrix();
    glScalef(3.5, 0.1, 3.75);
    glTranslatef(0, 0, 0);
    drawCube1(0.5, 0.1, 0.0, 0.25, 0.05, 0);
    glPopMatrix();
    
     // Buc tranh treo trên tuong
    glPushMatrix();
    glTranslatef(5.5, 3.5, 0.01); // Di chuy?n d?n v? trí trên tu?ng và t?o d? dày cho b?c tranh
    glScalef(0.75, 0.6, 0.1); // Kích thu?c b?c tranh (chi?u dài, chi?u r?ng, d? dày)
    drawCube1(0.7, 0.5, 0.3, 0.7, 0.5, 0.3); // Màu và d? bóng cho b?c tranh
    drawStar(1.0); // V? ngôi sao
    glPopMatrix();
    
    
    // Ve ngôi sao truc tiep tren buc tranh treo tuong
    glPushMatrix();
    glTranslatef(6.0, 4.0, 0.5); // Ð?t v? trí ngôi sao
    glScalef(0.4, 0.4, 0.4); // Kích thu?c c?a ngôi sao
    glColor3f(1.0, 1.0, 0.0); // Màu s?c (ví d?: vàng)
    drawStar(3.0); // V? ngôi sao tr?c ti?p
    glPopMatrix();

    glPopMatrix();

}

//ve giuong 
void bed() {
    //daugiuong
    glPushMatrix();
    glTranslatef(0.2, 0, 1);
    glScalef(0.1, 0.3, 0.3);
    drawCube1(0.5, 0.1, 0.0, 0.25, 0.05, 0);
    glPopMatrix();

    //giuong
    glPushMatrix();
    glTranslatef(0.5, 0, 1);
    glScalef(0.5, 0.15, 0.3);
    drawCube1(0.5, 0.75, 1.0, 0.5, 0.75, 1.0);
    glPopMatrix();


}

// guong 21
void bed2() {
    //daugiuong
    glPushMatrix();
    glTranslatef(0.2, 0, 3);
    glScalef(0.1, 0.3, 0.3);
    drawCube1(0.5, 0.1, 0.0, 0.25, 0.05, 0);
    glPopMatrix();

    //giuong
    glPushMatrix();
    glTranslatef(0.5, 0, 3);
    glScalef(0.5, 0.15, 0.3);
    drawCube1(0.5, 0.75, 1.0, 0.5, 0.75, 1.0);
    glPopMatrix();
}

// ve cai tu
void cabin() {
    glPushMatrix();
    glTranslatef(0.4, 0, 0.3);
    glScalef(0.25, 0.7, 0.1);
    drawCube1(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0, 0.3);
    glScalef(0.25, 0.7, 0.1);
    drawCube1(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
    glPopMatrix();
}

// cai ban
void sphericalObject()
{
    //table top part
    glPushMatrix();
    glTranslatef(2, 1, 9);
    glScalef(0.15, 0.05, 0.15);
    drawSphere(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //table leg
    glPushMatrix();
    glTranslatef(2, 0, 9);
    glScalef(0.05, 0.32, 0.05);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

// cai o
void umbrella()
{
    //table top part
    glPushMatrix();
    glTranslatef(2, 4, 6);
    glScalef(0.5, 0.1, 0.5);
    drawSphere(0.8, 0.65, 0.5, 0.8, 0.65, 0.5);
    glPopMatrix();

    //table leg
    glPushMatrix();
    glTranslatef(2, 0, 6);
    glScalef(0.05, 1.3, 0.05);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

// tach tra
void OnsolidTea() {
    glPushMatrix();
    glTranslatef(2, 1.2, 9);// dich chuyen vi tri
    glScalef(0.3, 0.3, 0.3);//thay doi kich thuoc
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };// khai bao gia tri mau
    GLfloat mat_ambient[] = { 0.5, 0.3, 0.2, 1.0 };//dinh nghia cho am tra
    GLfloat mat_diffuse[] = { 0.5, 0.3, 0.2, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 90 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glutSolidTeapot(0.5);
    glPopMatrix();
}

// ghe ngoi
void chair() {
    glPushMatrix();
    glTranslatef(2, 0, 8.5);
    glScalef(0.1f, 0.15f, 0.1f);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, 9.5);
    glScalef(0.1f, 0.15f, 0.1f);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}


// cua so
void window() {
    //cua trai
    glPushMatrix();
    glTranslatef(3, 2, 0);
    glScalef(0.2, 0.2, 0.1);
    drawCube1(0.0, 0.25, 0.5, 0.0, 0.25, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 2.6, 0);
    glScalef(0.2, 0.2, 0.1);
    drawCube1(0.0, 0.25, 0.5, 0.0, 0.25, 0.5);
    glPopMatrix();
    //cua phai
    glPushMatrix();
    glTranslatef(3.65, 2, 0);
    glScalef(0.2, 0.2, 0.1);
    drawCube1(0.0, 0.25, 0.5, 0.0, 0.25, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.65, 2.6, 0);
    glScalef(0.2, 0.2, 0.1);
    drawCube1(0.0, 0.25, 0.5, 0.0, 0.25, 0.5);
    glPopMatrix();


}

// hieu ung phan chieu
void lightOne()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 5.0, 8.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

// hieu ung phan chieu
void lightTwo()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 2.0, 1.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

// den 1 (tren tuong)
void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 1.000, 1,1, 0.0 };

    glPushMatrix();
    glTranslatef(2, 5.7, 2);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchOne == true) {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}


//den 2 (giuong)
void lightBulb2()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 1.000, 1,1, 0.0 };

    glPushMatrix();
    glTranslatef(0.2, 1.05, 1.5);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchTwo == true) glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    else glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

// cac day phao trên be boi
void drawBuoy(float x, float y, float z, float radius, float height, float red, float green, float blue) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(red, green, blue); // Màu s?c c?a phao
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluCylinder(quadratic, radius, radius, height, 20, 20); // V? hình tr? d?i di?n cho phao
    glPopMatrix();
}

// tao do co dinh de cac phao can theo be boi
float tubX = 4.0;
float tubY = -2.65;
float tubZ = 2.0;

// be boi
void bathTub()
{
    glPushMatrix();
    glTranslatef(tubX, tubY, tubZ);
    glScalef(2, 1, 2.75);
    drawCube2(0.0, 0.0, 1.0);
    glPopMatrix(); 

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // V? các phao
    drawBuoy(tubX + 2, tubY + 3, tubZ, 0.07, 1, 0.0, 1.0, 0.0); // Phao màu xanh
    drawBuoy(tubX + 2, tubY + 3, tubZ + 1, 0.07, 1, 1.0, 0.0, 0.0); // Phao màu d?
    drawBuoy(tubX + 2, tubY + 3, tubZ + 2, 0.07, 1, 1.0, 1.0, 0.0); // Phao màu vang
    drawBuoy(tubX + 2, tubY + 3, tubZ + 3, 0.07, 1, 1.0, 0.0, 0.0); // Phao màu do
    drawBuoy(tubX + 2, tubY + 3, tubZ + 4, 0.07, 1, 0.0, 1.0, 0.0); // Phao màu xanh
    drawBuoy(tubX + 2, tubY + 3, tubZ + 5, 0.07, 1, 1.0, 1.0, 0.0); // Phao màu vang
    drawBuoy(tubX + 2, tubY + 3, tubZ + 6, 0.07, 1, 1.0, 0.0, 0.0); // Phao màu do
    drawBuoy(tubX + 2, tubY + 3, tubZ + 7, 0.07, 1.2, 0.0, 1.0, 0.0); // Phao màu xanh

    drawBuoy(tubX + 4, tubY + 3, tubZ, 0.07, 1, 0.0, 1.0, 0.0); // Phao màu xanh
    drawBuoy(tubX + 4, tubY + 3, tubZ + 1, 0.07, 1, 1.0, 0.0, 0.0); // Phao màu d?
    drawBuoy(tubX + 4, tubY + 3, tubZ + 2, 0.07, 1, 1.0, 1.0, 0.0); // Phao màu vang
    drawBuoy(tubX + 4, tubY + 3, tubZ + 3, 0.07, 1, 1.0, 0.0, 0.0); // Phao màu do
    drawBuoy(tubX + 4, tubY + 3, tubZ + 4, 0.07, 1, 0.0, 1.0, 0.0); // Phao màu xanh
    drawBuoy(tubX + 4, tubY + 3, tubZ + 5, 0.07, 1, 1.0, 1.0, 0.0); // Phao màu vang
    drawBuoy(tubX + 4, tubY + 3, tubZ + 6, 0.07, 1, 1.0, 0.0, 0.0); // Phao màu do
    drawBuoy(tubX + 4, tubY + 3, tubZ + 7, 0.07, 1.2, 0.0, 1.0, 0.0); // Phao màu xanh

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}



// Su dung ban phim
void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a': // Di chuy?n góc nhìn sang trái
        camera.eyeX -= 1.0; // Gi?m giá tr? c?a eyeX d? di chuy?n sang trái
        camera.centerX += 0.5;
        break;
    case 'd': // Di chuy?n góc nhìn sang ph?i
        camera = {20.0, 5.5, 10.0, -10.0, 1.0, 0.0, 0.0, 100.0, 0.0};
//        struct Camera {
//    float eyeX
//    float eyeY;
//    float eyeZ;
//    float centerX;
//    float centerY;
//    float centerZ;
//    float upX;
//    float upY;
//    float upZ;
//};
        camera.eyeX +=2;
        camera.eyeZ -=3;
        camera.centerX -=3;
        camera.centerZ-=0.1;
        break;
    case 's': // Di chuy?n góc nhìn sang ph?i
        camera = {12.0, 5.5, 20.0, 1.0, 1.0, 1.0, 0.0, 100.0, 0.0};
        break;
    case 'b': // bat den tran
        if (switchOne == false) {
            switchOne = true;
            glEnable(GL_LIGHT0);
        }
        else {
            switchOne = false;
            glDisable(GL_LIGHT0);
        }
        switchTwo = false;
        glDisable(GL_LIGHT1);
        break;
    case 'v':// bat den ngu
        if (switchTwo == false) {
            switchTwo = true;

            glEnable(GL_LIGHT1);
        }
        else if (switchTwo != false) {
            switchTwo = false;
            glDisable(GL_LIGHT1);
        }
        switchOne = false;
        glDisable(GL_LIGHT0);
        break;
    default:// out
        exit(1);
        break;
    }
    glutPostRedisplay();
}

// ham hien cac object ra man hinh
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100); // phep chieu

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//      gluLookAt(20, 6, 15 ,0.0, 1.0, 0.0, 0, 1.0, 0.0);// thay doi goc nhin
    gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ,
              camera.centerX, camera.centerY, camera.centerZ,
              camera.upX, camera.upY, camera.upZ);
    glEnable(GL_LIGHTING);
// goi cac ham
    lightOne();
    lightTwo();
    bathTub();
    room();
    bed();
    bed2();
    cabin();
    OnsolidTea();
    chair();
    window();
    sphericalObject();
    umbrella();
    lightBulb1();
    lightBulb2();
    glFlush();
    glutSwapBuffers();
}


// ham main 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("BaiTapCuoiKi");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);

    //glEnable(GL_LIGHT0);
    glutMainLoop();

    return 0;
}
//GL_BLEND: tinh nang trong suot
//GL_LIGHT...: Dai dien cho nguon sang
// 
