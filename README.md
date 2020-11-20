# Light-Field-Viewer

This is a light field viewer impleamented in OpenGL based on Levoy and Hanrehan paper [1] using the ligh field dataset in [2].
The light field rendering calculation is done with shaders to esure fast rendering. The rendering is done at about 60 FPS.
The code can only handel squar image grid. The light field samples are loaded as a texture atlas.
All the light fields in the result have 17x17 grid.

[1] Levoy, Marc, and Pat Hanrahan. "Light field rendering." Proceedings of the 23rd annual conference on Computer graphics and interactive techniques. 1996.

[2] Jarabo, Adrian, et al. "How do people edit light fields." ACM Transactions on Graphics (Proc. SIGGRAPH). Vol. 33. No. 4. 2014.

## Results
![Lobby Light Field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/lobby.gif)
![Head Light Field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/head.gif)
![Garden Light field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/green.gif)
![Tea Pots Light Field](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/pots.gif)
## The control keys

To control the camera position:
 - A: move camera to right
 - D: move camera to left 
 - S: move camera Down
 - W: move camera Up
 - Z: move camera Inward
 - X: move camera Outward
 - P: pritn camera information

To control the Image Plane:
- I: move Image Plane Up
- K: move Image Plane Down
- L: move Image Plane Right 
- J: move Image Plane Left
- M: move Image Plane Outward
- N: move Image Plane Inward

Light field control Panel

![Control Panel](https://github.com/MEC402/Light-Field-Viewer/blob/main/pics/cp.PNG)

- With the control panel area you can change the Z position of the camera plane and the focal plane.
- The 0 button shows the camera plane, 1,2,3,4 are different bilinear interpolation, 5 is quadlinear interpolation
- The buttons on that last row allow for the user to switch to a diferent light field.

