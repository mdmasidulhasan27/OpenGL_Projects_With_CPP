1. download codeblocks 20.03 or higher
2. install codeblocks as default
3. go to freeglut>include>GL copy all 4 files then paste these to C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\include\GL path
4. again copy file freeglut>lib>freeglut.lib or freeglut>lib>x64>freeglut.lib for 64 bit OS then paste to C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib
5. copy file freeglut>bin>freeglut.dll or freeglut>bin>x64>freeglut.dll for 64 bit OS then paste to C:\Windows path
6. open C:\Program Files\CodeBlocks\share\CodeBlocks\templates\glut.cbp with notepad++ then click on [Search]>[Find]>[Replace]
   find what: glut32
   Replace with freeglut
7. open C:\Program Files\CodeBlocks\share\CodeBlocks\templates\glut.cbp with notepad++ then click on [Search]>[Find]>[Replace]
   find what: glut32
   Replace with freeglut
