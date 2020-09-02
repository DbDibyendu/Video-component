# Documentation for code1.cpp

### psuedo codes for the functions

##### 1. `loadJsonConfig()`

This function Parse and store JSON document into global variable

        initialise a var ret = -1 for returning
        Open the config.json file in read mode
        
        if file is not empty{
            
            Declare readbuffer
            Declare stream for reading the config file
            Parse config.json and store it in config global var
            Store the result in ok
            
            if it is empty{
                Print the JSON parse error
            }
            
            set ret = 0;
        }
        
        else if file is empty{
            
            Print Error in reading JSON file
        }
        
        close the file
        return -1 
        

##### 2. `ReadCameraSettings()`

This functions Prints out the Settings of the device entered by user which is stored in the respective Object in the main function

    
        Declare a character command to store the System command
        
        Copy the initial part "sudo v4l2-ctl --device=" into it
        
        Add the device location given by user from "device.loc" present in the Object 
        
        Then Add the rest of the command
        
        Use System(command) to run the system command which prints out the device settings
        


##### 3. CaptureFrametoMem()


### Info about the config.json file

It contains Multiple device and their basic Settings in Json format