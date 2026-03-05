The project path is in zephyr_project folder when I tested this. Hence the commands are per that.


activate the environment:
    C:\Users\virendra\zephyrproject>.venv\Scripts\activate.bat   

Then build the project, you have to build it from the zephyr folder else you might end up with errors:
    (.venv) C:\Users\virendra\zephyrproject\zephyr>west build -p always -b nucleo_u385rg_q ..\blinky_stm32f4


Then use: west flash
to flash the image on the target