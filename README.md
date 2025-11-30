# My-NBodySim
Simulation and visualitation of a dinamic N-Body sistem using OpenGl and OpenCV.


## Exectue arguments
    --file path     : estable data file for load simulation at scenes
    --mode (CPU_ONLY | GPU_CPUCONTROLLER | GPU_ONLY) : Set calulation mode for simulation.
                                                    CPU_ONLY : Full CPU calculation for simulation step
                                                    GPU_CPUCONTROLLER : CPU send and recive calculations from the GPU, heavy use in memory bandwidth.
                                                    GPU_ONLY : The GPU use and sent data direcly to OpenGL load shader pragmas in memory

    