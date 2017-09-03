//
//  main.cpp
//  ConvoPlusOrMinus
//
//  Created by Ben Lewson on 9/1/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#include <iostream>
#include "gcode.hpp"

gcode g;

using namespace std;

int main(int argc, const char * argv[]) {
    
    tool endMill;
    endMill.number = 9;
    endMill.heightOffsetNumber = 9;
    endMill.width = 0.25;
    endMill.length = 1.75;
    endMill.guageLength = 4.25;
    
    
    g.boilerPlate();
    g.callAndSetTool(endMill);
    g.rapidXY(1, 3.5);
    g.rapidZ(0.1);
    
    g.addToProgram(g.viewCurrentPosition() + NEWLINE);
    
    g.setAbsOrInc(1);
    
    g.setFeedrate(20.0);
    
    g.moveXY(2, 2);
    g.moveXY(5, NULL, 1);
    
    g.addToProgram(g.viewCurrentPosition() + NEWLINE);
    
    g.endProgram();
    
    g.dispCurrentProgram();
    
   
    return 0;
}
