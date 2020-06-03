//
//  Landscape.h
//  Final_FLIGHT_SIM
//
//  Created by PRATIK SANNAKKI on 15/05/19.
//  Copyright © 2019 PRATIK SANNAKKI. All rights reserved.
//


#ifndef LANDSCAPE_H_
#define LANDSCAPE_H_

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <cmath>
#include <cstdlib>

class Landscape {
    int rows;
    int columns;
    double highest;
    std::vector< std::vector<double>  > d;
    int solidId;
    int wireFrameId;                        
    static double unused;
    void generate(int x1, int y1, int x2, int y2, double rug);
    double scale(double x) {return x * (((double)rand()/RAND_MAX) - 0.5);}
    void drawTriangle(int x1, int z1, int x2, int z2, int x3, int z3);
    void vertex(double x, double z);
    void createSolidDisplayList();
    void createWireFrameDisplayList();
public:
    Landscape(int rows, int columns);
    void create(double rug);
    void draw() {glCallList(solidId);}
    void drawWireFrame() {glCallList(wireFrameId);}
};

#endif
