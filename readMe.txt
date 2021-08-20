How the program works:
Run make file perferably in ubuntu
1 - red piece
2 - white piece
3 - red king
4 - white king
When user launchs up the program they are first promoted with the option to input a custom position.

How custom positions work:
The user must give a valid txt file when inputting the name of the custom position
Custom positions must be in the form of a 32 line file with one digit at each line. 
0s represent an empty space and for specific pieces enter 1,2,3,4. 
The pieces from the input file are inserted starting from the top left of the board and then going left to right row by row.
Several example custom position files have been attached in the program folder.
Once a valid txt file is entered the user name is asked to say if the position is white (w) or red (r) to move.

If not a custom position:
If the user selected no after the custom position question, they are then asked if player 1 (r) and player 2 (w) is a bot.
Once this is done the game begins. 
Users enter the moves they want to select by entering the number move on the list.

Multi-jumps:
If there is a multi-jump avaliable the user makes the first jump.
The user then has the option of the choosing the next jumps until they have no more jumps.

Reading the board:
All squares and moves are represent as a grid of numbers 0-7.
The first number is the x axis and the second is the y axis.

Heuristics:
The hueristics below are listed in order of importance
1) The program values kings about 1.7 times a regular pieces
2) The program values regular pieces that are closer to promoting to a king
3) The program values kings that are closer to the center of the board 
4) The endgame is considered when there are less than 8 pieces
    a) In the endgame kings are worth twice as much they usually are
    b) Pieces that are not kings are worth a alot more the closer they are to promoting
    c) If a side is losing it tries to move kings to the corner it is closest to
    d) If a side is winning it looks to see which corner the opponents king is in and then goes twords that corner

Unfortunately, it seems like the end game hueristic made did not work too well and as a result the program played much worse, 
so after spending a long time trying to debug, I decided to comment out the endgame hueristic as a result. 
Because of this in the endgame there is alot of moving back and forth
and most of the time if the pieces are on opposite sides the bot will just end up moving back and forth.

Major Bugs:
Firstly, there is a bug (as mentioned in our meeting) that after doing all prompted question there is a seg-fault.
However, when running the debugger the seg-faults never happen
This happens occasionally when you input the bot is one of the players.
If this happens feel for to try 4-5 times (it usually works after a few tries).
If not then using the debugger would ensure the program runs.

How the program plays:
In general at the beggining of the game (first 5-10) moves the program plays ok.
However, after the beggining the program occasionally makes moves that are clear blunders.
As mentioned previously, the program usually gets stuck in the endgame and just starts moving back and forth unable to make progress.
In an endgame if given a position that is fairly close to victory the program usually does find a way to win.
(see states1 and state3 as an example)

Overall, a major theory that I have for why the program makes blunders and does not play optimally sometimes is because of the way I handle multi-jumps.
As mentioned I handle multi-jumps by giving the player who just jumped another move until there are no jumps avaliable.
This made me have to make sure that the max and min do not switch until all the jumps are done.
I believe that due to the nature of way I wrote my legal moves there are cases where the max and min are switched even before a the color is switched.
If doing this program again, I would rethink the way I handled jumps to try to avoid bugs and other complexities I ran into.