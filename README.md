# OpenGL-Template  
  
An OpenGL Template for my Crafting_In_C youtube dev log series.  
https://www.youtube.com/channel/UCEoiNRR8b54dRWYoonnfoLA/videos  
  
Part 1  
https://www.youtube.com/watch?v=ks_BR217DM0  
  
Part 2  
https://www.youtube.com/watch?v=6PTPamwGtkg  
  
WINDOWS SETUP  
--------------  
Get GCC for windows -- Tested this stable version on windows 10  
https://nuwen.net/mingw.html  
  
Get GLFW3 - Get the 64-Bit Windows Pre-Compiled Binaries  
https://www.glfw.org/download.html  
EXAMPLE : https://github.com/glfw/glfw/releases/download/3.3.7/glfw-3.3.7.bin.WIN64.zip  
NOTE : Pay attention to the version number.  
Extract zip into libs folder.  
EXAMPLE : The include path should look like this -> libs/glfw-3.3.7.bin.WIN64/include  
  
Run this whole line at the command prompt.  
gcc -O2 -m64 -o test main.c libs/glad/glad/glad.c -I./libs/glad/ -I./libs/glfw-3.3.7.bin.WIN64/include/ -L./libs/glfw-3.3.7.bin.WIN64/lib-mingw-w64/ -lglfw3 -lgdi32
  
then run test.exe  
  
  
  
LINUX SETUP - Tested with Ubuntu using VirtualBox  
--------------  
NOTE : I was able to get OpenGL 4.5 on VirtualBox with this setup.  
  
Get GCC for Linux  
sudo apt install gcc  
  
NOTE : If you need to update MESA here is a link of info on how to do that. Mesa 22.1.2 is out, however at the time of my writing this, you can't access it yet. Mesa 22.1.2 fixes an OpenGL get string error, where it reports OpenGL 4.5 instead of 4.6. Sadly, I was not able to get it to use 4.6 with Mesa 22.1.1, which was the latest version I could test in virtualbox.  
https://itsfoss.com/install-mesa-ubuntu/  
  
If you need GLXINFO  
sudo apt install mesa-utils  
  
Get GLFW3  
sudo apt install libglfw3-dev  
  
gcc -O2 -m64 -o test main.c libs/glad/glad/glad.c -I./libs/glad/ -I/usr/include/libdrm -lglfw
  
then run ./test  
