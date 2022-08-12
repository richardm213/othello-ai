# Othello AI
For this project, I implemented an Othello AI using a minimax algorithm with alpha-beta pruning. My algorithm won the class-wide tournament in my Data Structures and Algorithms course, which was composed of over 150 students.

<br />
<p align="center">
  <img
    width="500"
    alt="Screen Shot 2022-08-12 at 4 32 47 PM"
    src="https://user-images.githubusercontent.com/92076990/184457008-6e8f47e8-9b16-4b2e-bddb-f5b16cd0e39c.png"
  />
</p>
<br />

## Algorithm
The inspiration for my algorithm came from my experience playing the game of chess, where the evaluation for a position often depends on the stage of the game. As a result, I decided to have three separate evaluation functions for my AI, each one corresponding the early game, middlegame, and endgame respectively.

## Heuristic Function
The core feature that distinguishes a basic AI from a better one is the heuristic function. The heuristic function essentially takes in a number of different factors and uses them to determine the strength of a given board position. Listed below are all the factors that comprised my heuristic function along with their impact during the three stages of the game.
* Corners (High weight at all stages)
* C squares - (Squares adjacent to corner. High weight early game, but decreases as game progresses)
* X squares - (Square directly diagonal to corner. High weight early game, but decreases as game progresses)
* Mobility - (Number of possible moves the opponent can make. High weight in the early game, but decreases to zero weight in the end game)
* Score Difference - (No weight in the early or middle game, but most significant weight in the endgame)
* Parity - (Which player will make the last move. No weight in the early or middle game, but moderate weight in the end game)

## Tournament
The format of the tournament was simple: 
1. Each student in the class could submit as many AIs as they wanted
2. Our professor then gathered all the AIs together and matched them up against each other
3. Each AI played each other twice, once as white and once as black. 
4. Each AI had a maximum of 3 seconds to move otherwise it would be disqualified. 
5. The AI with the best winning percentage wins.

## Results:
<img
  width="1190"
  alt="Screen Shot 2022-08-11 at 4 48 50 PM"
  src="https://user-images.githubusercontent.com/92076990/184260775-ecaf97d2-0c71-4795-acda-aaecd815881f.png"
/>

As you can see, my best AI finished in 1st place, with a 97.2% win rate.
