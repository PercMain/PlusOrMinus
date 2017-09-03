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
    outputProgram = "(Program Info:)\n";
    
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

string gcode::viewCurrentPosition()
{
    string Xco = to_string(status.position.X);
    string Yco = to_string(status.position.Y);
    string Zco = to_string(status.position.Z);
    return Xco + ", " + Yco + ", " + Zco;
}

string gcode::Units()
{
    return "G" + to_string(status.units) + SPACE;
}

string gcode::AbsOrInc()
{
    return "G" + to_string(status.absOrInc) + SPACE;
}

string gcode::WorkOffset()
{
    return "G" + to_string(status.workOffset) + SPACE;
}

string gcode::SpindleState()
{
    return "M0" + to_string(status.spindleState) + SPACE;
}

string gcode::CoolantState()
{
    return "M0" + to_string(status.coolantState) + SPACE;
}

string gcode::StoppingMode()
{
    return "G" + to_string(status.stoppingMode) + SPACE;
}

string gcode::Plane()
{
    return "G" + to_string(status.plane) + SPACE;
}

string gcode::MotionState()
{
    return "G0" + to_string(status.motionState) + SPACE;
}

string gcode::Feedrate()
{
    return "F" + to_string(status.feedrate) + SPACE;
}

string gcode::AuxFeedrate()
{
    return "F" + to_string(status.auxFeedrate) + SPACE;
}

string gcode::TerFeedrate()
{
    return "F" + to_string(status.terFeedrate) + SPACE;
}

//Tool functions
void gcode::setTool(tool t)
{
    status.currentTool = t;
}

void gcode::callAndSetTool(tool t)
{
    setTool(t);
    addToProgram(callCurrentTool());
}


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
    
    return returnVal + NEWLINE;
}

string gcode::callCurrentTool()
{
    return callTool(status.currentTool) + NEWLINE;
}


//Code for top of program
string gcode::boilerPlate()
{
    return Units() + AbsOrInc() + WorkOffset() + StoppingMode() + NEWLINE 
    + SpindleState() + CoolantState() + Plane() + MotionState() + NEWLINE;
}


//Add string of text to program
void gcode::addToProgram(string command)
{
    outputProgram += command;
}

void gcode::dispCurrentProgram()
{
    cout << outputProgram;
}
