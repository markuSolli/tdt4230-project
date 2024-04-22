# TDT4230 Final Project
Final project for TDT4230 Graphics and Visualization

![Rendered image](https://github.com/markuSolli/tdt4230-project/blob/main/res/images/image.png)

## How to run
Create the directories `build`, `build/data`, `build/data/frames`, and `build/data/images`.  
Navigate to the `build` folder in the terminal.  
Build the Makefile using CMake:
```
cmake ..
```
The render parameters are defined in `main.cpp`, adjust if needed before building.  
Build the project:
```
make
```
Run the project, rendered frames are stored in `build/data/frames`:
```
./graphics_project
```
Convert the rendered ppm files to png and store to `build/data/images`:
```
make image
```
Generate a video from the frames stored in `build/data/frames`, the video is stored in `build/data`:
```
make video
```

## Resources used
- Base rendering code from [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- AABB and lighting from [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
- 3D models from [Low Poly Household Items](https://lowpolyassets.itch.io/low-poly-household-item-pack)
