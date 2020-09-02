# Documentation for code1.cpp

### psuedo codes for the functions

##### 1. loadJsonConfig()

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
        

##### 2. ReadCameraSettings()


##### 3. CaptureFrametoMem()


### Info about the config.json file

It contains Multiple device and their basic Settings in Json format