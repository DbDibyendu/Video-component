# Documentation for code1.cpp

### Psuedo codes and flowcharts for the functions

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
                
            end
            }
            
            set ret = 0;
            
         end
        }
        
        else if file is empty{
            
            Print Error in reading JSON file
        end
        }
        
        
        close the file
        return -1 
        
        end
        

##### 2. `ReadCameraSettings()`

This function Prints out the Settings of the device entered by user which is stored in the respective Object in the main function

        {
            
        Declare a character command to store the System command
        
        Copy the initial part "sudo v4l2-ctl --device=" into it
        
        Add the device location given by user from "device.loc" present in the Object 
        
        Then Add the rest of the command
        
        Use System(command) to run the system command which prints out the device settings
        
        end
        
        }
        


##### 3. `CaptureFrametoMem()`

This function Starts the following device and captures a frame and store it into Memory



##### 4. `main()`

Gets device number from user and Calls the above functions

        In the main function
        {
        create a new object device1 
        
        New Variable k to get the device number from user
        Create a char device_id to copy the device location from JSON file according to the input from the user
        
        call loadJsonConfig() to load the JSON file into the global var
        
        Print out Options for the user
        Get the value of k
        
        Copy the device Id accroding to the value of K
        and print ERROR in case of wrong input
        
        Copy the device location in loc variable from the Object i.e. device1.loc
        
        print the device Id
        
        call ReadCameraSettings for device1
        
        call CaptureFrametoMem for device1
        
        end
        }

### Info about the config.json file

It contains Multiple device and their basic Settings in Json format

