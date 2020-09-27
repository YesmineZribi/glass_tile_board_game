# glass_tile_board_game
An implementation of the Azul board game in C++ (this project is in french).

# To run the game: compile and run the projetCSI2772.cpp 
-Game: 
*Each player has a board with a random combination of the 5 colors: Grey, Red, Blue, Yellow, Orange
*The goal: who ever fills their board first, or whoever gains the most points wins 

Rules of the game: 
*Each game has 5 phases 
*Players have a group of random colors "le lot" from which they have to choose the colours they want 
to use to fill the board 
*A player can chose one column from the lot at a time, and from that column they can only pick one 
color, once they picked the color, they get all the cards with that color in that column, 
and the remainig cards from that column go into a "garbage list" or surplus 
*Players can also chose cards (of the same color) from the surplus 
*Players have a position, they can only move to the right, and they can fill one column at a time. 
once the player has their deck of colors they can chose any column on their board to fill that is found 
between 0 and their current postion (ex: player at position 4 can chose to fill column 4, 3, 2, 1 or 
0 but NOT column 5 or 6 because that implies going backwards) 
*During a turn a player can decide to pick colors and fill columns or reset their position back 
to the furthest column to the left 

*How the phase plays: 
Option 1: 
-Player 1 picks a column from the lot
-Player 1 picks a color from the column they chose, they know own all the cards with that colour from that column,
the other colours go in the surplus 
-Player 1 picks the column on their board in which they wish to put their cards 
-The cards get placed in the corresponding colors on the board  
Ex: 
Let's say the player picked a column that contains 3 cards with the colour B, 
and the board column they chose has only two tiles coloured in B, then after the cards are placed,
the player is left with one B card, -1 for that ! 

-It's now the next player's turn 

Option2: 
-Reset position to 6 
-Can only do this if your position was not 6, if it was you are forced to go with option 1 

*How to win points: 
-Say you are in position v at the moment, and you filled the whole column you are in, 
then you gain: 3 points for that column + 1 point for each column on the right of v that has at least 
one tile covered 
