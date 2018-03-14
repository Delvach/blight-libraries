#ifndef BikeControlData_h
#define BikeControlData_h

/*
   Define data to be received; struct must be replicated in any code that sends this
*/
struct BikeControlData {
	byte version = 0;
	/*
	 * actionIndex:
	 *
	 * 0 - Change Mode
	 * 1 - Perform Action
	 * 2 - Set Hue
	 * 3 - Set Pos
	 * 4 - Set Bright
	 *
	 */
//     byte actionIndex = 0;
// 
//     byte setting = 0;
    
    byte changeHue = 0;
    short int hue = 0;
    
    byte changeBrightness = 0;
    byte brightness = 0;
    
    byte changeMode = 0;
    byte mode = 0;
    
    byte performAction = 0;
    byte action = 0;
    
    
    
};




#endif






















