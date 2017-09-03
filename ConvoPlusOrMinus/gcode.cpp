//
//  gcode.cpp
//
//  Created by Ben Lewson on 9/2/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#include "gcode.hpp"

//Constructor
gcode::gcode()
{
    //Clear output and create beginning comment
    outputProgram = "(Program Start)\n";
    
    //Zero out position
    status.position.X = 0.0;
    status.position.Y = 0.0;
    status.position.Z = 0.0;
    status.position.A = 0.0;
    status.position.B = 0.0;
    
    //Programming in inches by default
    status.units = 20;
    
    //Absolute positioning
    status.absOrInc = 90;
    
    //Normal work offset
    status.workOffset = 54;
    
    //Spindle off
    status.spindleState = 5;
    
    //Coolant off
    status.coolantState = 9;
    
    //Stopping mode normal
    status.stoppingMode = 64;
    
    //XY plane default
    status.plane = 17;
    
    //Rapids by default
    status.motionState = 0;
    
    //All feedrates 0 by default;
    status.feedrate = 0.0;
    status.auxFeedrate = 0.0;
    status.terFeedrate = 0.0;
    
    //Set tool to 0 by default
    status.currentTool.number = 1;
    status.currentTool.heightOffsetNumber = 1;
    status.currentTool.width = 1.0;
    status.currentTool.length = 1.0;
    status.currentTool.guageLength = 3.0;
    
}

//Returns XYZ coordinates
string gcode::viewCurrentPosition()
{
    string Xco = to_string(status.position.X);
    string Yco = to_string(status.position.Y);
    string Zco = to_string(status.position.Z);
    return "(" + Xco + ", " + Yco + ", " + Zco + ")";
}

//Return functions below all produce formatted text with appropriate letter codes
//Returns units
string gcode::Units()
{
    return "G" + to_string(status.units) + SPACE;
}

//Returns absolute or incremental motion mode
string gcode::AbsOrInc()
{
    return "G" + to_string(status.absOrInc) + SPACE;
}

//Returns current work offset
string gcode::WorkOffset()
{
    return "G" + to_string(status.workOffset) + SPACE;
}

//Returns current spindle status
string gcode::SpindleState()
{
    return "M0" + to_string(status.spindleState) + SPACE;
}

//Returns current coolant status
string gcode::CoolantState()
{
    return "M0" + to_string(status.coolantState) + SPACE;
}

//Returns current stopping mode (may remove in future, does not seem necessary for standard FANUC control)
string gcode::StoppingMode()
{
    return "G" + to_string(status.stoppingMode) + SPACE;
}

//Returns current working plane
string gcode::Plane()
{
    return "G" + to_string(status.plane) + SPACE;
}

//Returns current motion state (G00, G01, G02, G03);
string gcode::MotionState()
{
    return "G0" + to_string(status.motionState) + SPACE;
}

//Returns current feedrate
string gcode::Feedrate()
{
    return "F" + to_string(status.feedrate) + SPACE;
}

//Returns current auxiliary feedrate
string gcode::AuxFeedrate()
{
    return "F" + to_string(status.auxFeedrate) + SPACE;
}

//Returns current tertiary feedrate
string gcode::TerFeedrate()
{
    return "F" + to_string(status.terFeedrate) + SPACE;
}

//Tool functions
void gcode::setTool(tool t)
{
    status.currentTool = t;
}

//Runs setTool and callCurrentTool
void gcode::callAndSetTool(tool t)
{
    setTool(t);
    addToProgram(callCurrentTool());
}

//Outputs tool change text formatted
string gcode::callTool(tool t)
{
    string returnVal;
    if(t.number < 10)
    {
        returnVal =  "T0" + to_string(t.number);
    }
    else
    {
        returnVal = "T" + to_string(t.number);
    }
    
    returnVal += " M06 G43 H";
    
    if(t.heightOffsetNumber < 10)
    {
        returnVal += "0" + to_string(t.heightOffsetNumber);
    }
    else
    {
        returnVal += to_string(t.heightOffsetNumber);
    }
    
    return returnVal;
}

//Runs callTool for current tool
string gcode::callCurrentTool()
{
    return callTool(status.currentTool) + NEWLINE;
}

//Movement commands
//Set absolute or incremental (0 default for absolute)
void gcode::setAbsOrInc(int state)
{
    if(!state)
    {
        status.absOrInc = 90;
    }
    else
    {
        status.absOrInc = 91;
    }
    
    addToProgram(AbsOrInc() + NEWLINE);
}

//Sets motion state
void gcode::setMotionState(int state)
{
    status.motionState = state;
}


/*
 Updates individual coordinates during a move depending on if in absolute or incremental mode
 */

//Updates coordinate status
void gcode::updateX(double x)
{
    if(status.absOrInc == 90)
    {
        status.position.X = x;
    }
    else
    {
        status.position.X += x;
    }
}

//Updates coordinate status
void gcode::updateY(double y)
{
    if(status.absOrInc == 90)
    {
        status.position.Y = y;
    }
    else
    {
        status.position.Y += y;
    }
}

//Updates coordinate status
void gcode::updateZ(double z)
{
    if(status.absOrInc == 90)
    {
        status.position.Z = z;
    }
    else
    {
        status.position.Z += z;
    }
}

//Updates coordinate status
void gcode::updateA(double a)
{
    if(status.absOrInc == 90)
    {
        status.position.A = a;
    }
    else
    {
        status.position.A += a;
    }
}

//Updates coordinate status
void gcode::updateB(double b)
{
    if(status.absOrInc == 90)
    {
        status.position.B = b;
    }
    else
    {
        status.position.B += b;
    }
}

//




//Rapid in X and Y, default arg for vectorMode = 0
void gcode::rapidXY(double x, double y, int vectorMode)
{
    setMotionState(0);//Set to rapid
    
    string returnVal = MotionState();
    
    if(vectorMode == 0)
    {
        returnVal += "X" + to_string(x) + " Y" + to_string(y);
        updateX(x);
        updateY(y);
    }
    else if(vectorMode == 1)
    {
        returnVal += "X" + to_string(x);
        updateX(x);
    }
    else
    {
        returnVal += "Y" + to_string(y);
        updateY(y);
    }
    
    addToProgram(returnVal + NEWLINE);
}

//Rapid in Z
void gcode::rapidZ(double z)
{
    setMotionState(0);//Set to rapid
    
    string returnVal = MotionState();
    returnVal += "Z" + to_string(z);
    updateZ(z);
    addToProgram(returnVal + NEWLINE);

}

//Set feedrate, default which feed to primary
void gcode::setFeedrate(float feed, int whichFeed)
{
    if(whichFeed == 1)
    {
        status.feedrate = feed;
    }
    else if(whichFeed == 2)
    {
        status.auxFeedrate = feed;
    }
    else
    {
        status.terFeedrate = feed;
    }
    addToProgram("F " + to_string(feed) + NEWLINE);
}

//Move at feed in X and Y
void gcode::moveXY(double x, double y, int vectorMode)
{
    setMotionState(1);//Set to feedrate motion
    
    string returnVal = MotionState();
    
    if(vectorMode == 0)
    {
        returnVal += "X" + to_string(x) + " Y" + to_string(y);
        updateX(x);
        updateY(y);
    }
    else if(vectorMode == 1)
    {
        returnVal += "X" + to_string(x);
        updateX(x);
    }
    else
    {
        returnVal += "Y" + to_string(y);
        updateY(y);
    }
    
    addToProgram(returnVal + NEWLINE);
}

//Move at feed in Z
void gcode::moveZ(double z)
{
    setMotionState(1);//Set to rapid
    
    string returnVal = MotionState();
    returnVal += "Z" + to_string(z);
    updateZ(z);
    addToProgram(returnVal + NEWLINE);
    
}


//Code for top of program
void gcode::boilerPlate()
{
    addToProgram(Units() + AbsOrInc() + WorkOffset() + StoppingMode() + NEWLINE
    + SpindleState() + CoolantState() + Plane() + MotionState() + NEWLINE);
}


void gcode::endProgram()
{
    addToProgram("\nG30\nM30 (Program End)\n");
}

//Add string of text to program
void gcode::addToProgram(string command)
{
    outputProgram += command;
}

//send current program to console
void gcode::dispCurrentProgram()
{
    cout << outputProgram;
}
