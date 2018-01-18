// readme.txt
// Horacio Lopez and Yifan Yu

*use up arrow to accelerate your spaceship, use down arrow key to decelerate*
*left and right arrow keys are for direction changes*
*dont get hit by asteroids and stay as long as possible*

*q to quit and save your score*
*./run leader.txt can save your highest scores!*

Our project is the representation of the game “Asteroids” in our own bouncy way.

On the user’s end, this program allows them to control the movement of a starship through the arrow keys and fire bullets. The game randomly generates 3 asteroids on the screen at the start of the game. If the user hits an asteroid, the asteroid shrinks.
If the user hits the shrunken asteroid again, the asteroid is “destroyed” and a new large asteroid spawns on the
screen. The winning strategy is to dodge and avoid the asteroids. If the user collides once, the game is over.

As the user stays alive, their score increments to a higher score. The user has the option to save their scores to a leaderboard
via text file. In order to do this, upon typing the executable “./run” the user can additional type a desired text file name to 
which top 10 scores from there on will be saved to this file to be accessed later.

We were unable to keep track of the random movements of each of the generated asteroids. Thus, in the freedom of space, they
gracefully “glide” past one another and only impact the user’s spaceship.
