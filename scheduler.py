import os
import time
import datetime

# Set the time when the computer should shut down
shutdown_time = datetime.time(17, 0)  # 5 pm

while True:
    # Get the current time
    current_time = datetime.datetime.now().time()
    
    # Check if it is time to shut down
    if current_time >= shutdown_time:
        os.system('shutdown /s /t 1')  # Shut down the computer with a 1 second delay
        break
    
    # Wait for a minute before checking again
    time.sleep(60)


#This code uses the datetime module to get the current time and compare it to the shutdown time (which is set to 5 pm). If the current time is later than or equal to the shutdown time, the os.system function is used to execute the Windows command shutdown /s /t 1, which shuts down the computer with a 1 second delay. The while True loop ensures that the code keeps checking the time until it is time to shut down, and the time.sleep(60) function causes the code to wait for 1 minute before checking the time again, to avoid constantly using up system resources.

