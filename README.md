# OGLT
OpenGL-Template  
  
Beginning of an OpenGL Template for a future youtube tutorial series.  
  
WINDOWS SETUP  
--------------  
Get GCC for windows -- This version is very stable  
https://nuwen.net/mingw.html  
  
Get GLFW3  
https://github.com/glfw/glfw/releases/download/3.3.7/glfw-3.3.7.bin.WIN64.zip  
Extract zip into libs folder.  
EXAMPLE : The include path should look like this -> libs/glfw-3.3.6.bin.WIN64/include  
  
Run this whole line at the command prompt.  
gcc -O2 -m64 -o test main.c libs/glad/glad/glad.c -I./libs/glad/ -I./libs/glfw-3.3.6.bin.WIN64/include/ -L./libs/glfw-3.3.6.bin.WIN64/lib-mingw-w64/ -lglfw3 -lgdi32
  
  
then run test.exe  
  
  
  
LINUX SETUP - Tested with Ubuntu using VirtualBox  
--------------  
NOTE : I was able to get OpenGL 4.5 on VirtualBox with this setup.  
  
Get GCC for Linux  
sudo apt install gcc  
  
If you need GLXINFO  
sudo apt install mesa-utils  
  
Get GLFW3  
sudo apt install libglfw3-dev  
  
gcc -O2 -m64 -o test main.c libs/glad/glad/glad.c -I./libs/glad/ -I/usr/include/libdrm -lglfw
  
  
then run ./test  
