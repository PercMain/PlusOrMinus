//
//  gcode.hpp
//
//  Created by Ben Lewson on 9/2/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#ifndef gcode_hpp
#define gcode_hpp


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>
 

#define PI      3.14159265
#define SPACE   " "
#define NEWLINE "\n"

struct pos
{
    double X;
    double Y;
    double Z;
    double A;
    double B;
};

struct tool
{
    int number;
    int heightOffsetNumber;
    float width;
    float length;
    float guageLength;
};

struct machineStatus
{
    pos     position;       //current position
    int     units;          //G20 or G21
    int     absOrInc;       //G90 or G91
    int     workOffset;     //G53, G54, G55 etc.
    int     spindleState;   //M03, M04, M05
    int     coolantState;   //M07, M08, M09
    int     stoppingMode;   //G64 or G61
    int     plane;          //G17, G18, G19
    int     motionState;    //G00, G01, G02, G03
    float   feedrate;       //ipm or mmpm for milling
    float   auxFeedrate;    //temporary feedrate for operations at non-nominal speed ie. ramping
    float   terFeedrate;    //Same as auxFeedrate, but one level deeper, just in case
    tool    currentTool;    //Tool currently in spindle
};


using namespace std;

class gcode
{
public:
    //constructor
    gcode();
    
    //Prints current XYZ Position
    string viewCurrentPosition();
    
    //Returns formatted strings of modes, status info, etc.
    
    //Returns unit mode
    string Units();
    
    //Returns absolute or incremental motion
    string AbsOrInc();
    
    //Returns work offset
    string  WorkOffset();
    
    //Returns spindle state;
    string SpindleState();
    
    //Returns coolant state
    string CoolantState();
    
    //Returns stopping mode();
    string StoppingMode();
    
    //Returns current work plane
    string Plane();
    
    //Returns motion state
    string MotionState();
    
    //Returns formatted feedrate
    string Feedrate();
    //Returns formatted auxiliary feedrate
    string AuxFeedrate();
    //Returns formatted tertiary feedrate
    string TerFeedrate();
    
    
    //Sets tool values into status register
    void setTool(tool t);
    //Runs setTool and outputs tool change into program
    void callAndSetTool(tool t);
    
    //Returns tool change command formatted
    string callTool(tool t);
    
    //Returns tool change command for current tool
    string callCurrentTool();
    
    
    //Movement commands
    //Set absolute or incremental (0 for absolute)
    void setAbsOrInc(int state = 0);
    
    //Sets Motion State (Rapids, feed, arc)
    void setMotionState(int state);
    
    //Updates coordinate status
    void updateX(double x);
    void updateY(double y);
    void updateZ(double z);
    void updateA(double a);
    void updateB(double b);
    
    //Calls Rapid in X and Y
    void rapidXY(double x, double y, int vectorMode = 0);
    
    //Calls Rapid in Z
    void rapidZ(double z);
    
    //Set feedrate
    void setFeedrate(float feed, int whichFeed = 1);
    
    //Move at feed in X and Y
    void moveXY(double x, double y, int vectorMode = 0);
    
    //Move at feed in Z
    void moveZ(double z);
    
    
    
    
    
    //Creates start of program boilerplate text
    void boilerPlate();
    
    //Calls program end code
    void endProgram();
    
    //Adds string to current program for output
    void addToProgram(string command);
    
    //Prints current program to console;
    void dispCurrentProgram();
    
private:

    machineStatus status;
    
    string outputProgram;
    
};

#endif /* gcode_hpp */
