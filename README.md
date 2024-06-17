# Boid simulation

Boids is an artificial life simulation originally developed by Craig Reynolds. The aim of the simulation was to replicate the behavior of flocks of birds. Instead of controlling the interactions of an entire flock, however, the Boids simulation only specifies the behavior of each individual bird. With only a few simple rules, the program manages to generate a result that is complex and realistic enough to be used as a framework for computer graphics applications such as computer generated behavioral animation in motion picture films.


Here are the rules:

**Separation**
Each bird attempts to maintain a reasonable amount of distance between itself and any nearby birds, to prevent overcrowding.
<center>
<img src="./docs/separation.png">
 </center>


**Alignment**
Birds try to change their position so that it corresponds with the average alignment of other nearby birds.
<center>
<img src="./docs/alignment.png">
</center>

**Cohesion**
Every bird attempts to move towards the average position of other nearby birds.
<center>
<img src="./docs/cohesion.png">
</center>


# Simulation Description

Upon launching the program, we have several sliders that we can use.

Visual Range - the field of vision of the boid.
We can adjust the strength of each of the three previously mentioned rules:

Alignment Coefficient
Separation Coefficient
Cohesion Coefficient
We can also adjust the strength with which these rules affect the boids.

We can also adjust the number of boids using a slider.

Importantly, we can click on a selected boid – it will then be highlighted, and we will see its visual range in red and a green arrow showing the current strength acting on the boid.



https://github.com/daredevilq/boids-algorithm-visualizer/assets/110993908/635a8598-8d6d-4fa4-bd3d-b3adbe765aac





# Dependencies

[Raylib Site](https://www.raylib.com/)

[Raylib source code](https://github.com/raysan5/raylib)

raylib is a simple and easy-to-use library to enjoy videogames programming.
