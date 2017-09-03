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
    
    
    g.addToProgram(g.boilerPlate());
    g.callAndSetTool(endMill);
    
    g.dispCurrentProgram();
    
   
    return 0;
}
