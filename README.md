# object_texture_fill_OpenGL
Create the 'imageio.o' file running command: 
g++ -c imageio.cpp -ltiff -lpng

This command will creat imageio.o file
Then run following command to run the code:

For Mac: g++ textureFill.cpp -o textureFill -framework OpenGL -framework GLUT && ./textureFill

For Linux: textureFill.cpp -o textureFill -lglut -lGLU -lGL && ./textureFill

Since openGL is a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics. There is no feature for rendering image in OpenGL we have to use any third party libraries. So here i have used imageio library. For more :
https://www.ks.uiuc.edu/Research/vmd/doxygen/ImageIO_8h-source.html


Try to change all the arguments and value and play with the code.
