# Dave Borja
import os
import time
import datetime

# Set the time when the computer should turn on
startup_time = datetime.time(6, 0)  # 6 am

# Get the current time
current_time = datetime.datetime.now().time()

# Check if it is time to turn on the computer
if current_time >= startup_time:
    os.system('schtasks /create /tn "Turn on PC" /tr "cmd /c powercfg -h off && shutdown /h" /sc once /st 06:00') # turn on the computer at 6 am
