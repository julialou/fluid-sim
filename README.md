Usage:

qmake FluidSim.pro 
make

./FluidSim data/params.txt


-----------------------------------


Run - starts the simulation if it's paused
Pause  - pauses simulation, useful if it's running slowly to change parameters
Reset - resets the fluid, does not reset parameters in the interface


-----------------------------------
Simulation Parameters.


Number of Particles
Container Size
Simulation Scale
Smoothing Radius
Time Step

Rest Density
Viscosity - viscosity coefficient
Collision Elasticity - restitution 
Surface Tension - surface tension coefficient
Stiffness - gas constant or pressure coefficient
Particle Mass
Gravity - acceleration

-----------------------------------

Create Sphere Obstacle

Allows the user to interactively create spheres for the fluid to collide with

Position
Radius

Add Obstacle - adds one sphere with the current settings, max 5 obstacles
Clear Obstacles - clear all obstacles


-----------------------------------

Config file: 

NumParticles i
ContainerDimension x y z
SimScale f
TimeStep f
SmoothRadius f
Elasticity f
RestDensity f
Mass f
Viscosity f
GasK f
Threshold f
Tension f
ParticleSize f
Gravity x y z
