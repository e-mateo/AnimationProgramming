<h1> Animation Programming </h1>
<h2><b>Introduction </b></h2>
Animation Programming is a project well named to explain itself as it introduced us to implementing animations in C++. <br>
The people who took part of the project are Lenny Rabinne and Mateo Erbisti, two students from Isart Digital. <br>
It started on December 9th, 2022 and finished on January 2nd, 2023.
It has been made on Visual Studio 2019 and is expected to work in <B>Release x86 mode</B>. <br>
The engine was given to us and the source code that we've written can be found  in /AnimationProgramming/AnimationProgramming.

<h2><b> T-Pose and Skeleton </b></h2>
The first part of the project was to draw a skeleton in T-Pose. To do that we created a Body class and a Bone class that was useful to stock the needed data like positions and rotations of the T-Pose. <br>
We made a kinship tree to order bones and to be able to calculate the world transform matrix of each bone depending on its parent.

<h2><b> Walk and Run Animation </b></h2>
The next step of the project was to animate the skeleton with a walking and a running animations. We created an Animation class that stocked local transforms of the animation for each bone and each frame so that we could then calculate the world transforms and stock them.
There's also an update that calculates the current and next frame of the animation depending on its speed.

<h2><b> Bone movement </b></h2>
We needed to make a bone move by ourselves using hardcoded animations. <br>
To do that we created our own animation where we set up rotations and positions of the arms of the body for each frame to make them move. <br> 

<h2><b> Body Animation </b></h2>
Until this part, we only applied our animation on the skeleton but we also needed to apply it to the body. <br>
To do that we needed to modify the vertex shader of our program to calculate the right position of each vertex. <br>
We already had a function in our engine to send data to our vertex shader which was really useful. <br>

<h2><b> Blending :</b></h2>
<img src = "AnimationProgramming/Images/walk.gif"> <br>
Once we had our two animation done, we worked on the Blending which is useful for smoothing animation between frames. <br>
Our Blending uses the Lerp function to interpolate the position between the current frame and the next frame and uses the Slerp function to do the same for rotations. <br>
It can be found in our Animator class. <br>

<h2><b> Crossfade :</b> </h2>
The last part of our project was to do a crossfade on the two given animations. It works by blending both animation positions and rotations together with Lerp and Slerp again. <br>
Both animations also need to have the same time during the crossfade so that it works well so we needed to adjust the speed of the out animation. <br>
<img src = "AnimationProgramming/Images/crossfade.gif">
