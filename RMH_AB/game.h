#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "playfield.h"

void stateGameInitLevel()
{
  playerScore = 0;
  AIScore = 0;
  scoreMax = howManyWins;
  setupGame();
  gameState = STATE_GAME_PLAYING ;
};



void stateGamePlaying()
{
  /*
    // pause render until it's time for the next frame
    if (!(arduboy.nextFrame())) return;
    arduboy.pollButtons();
    switch (gameState)
    {

      break;
    case STATE_GAME_INIT:
      arduboy.clear();
      amountOfWins();
      if (arduboy.justPressed(RIGHT_BUTTON | UP_BUTTON) && (howManyWins < 7))howManyWins++;
      if (arduboy.justPressed(LEFT_BUTTON | DOWN_BUTTON) && (howManyWins > 1))howManyWins--;
      if (arduboy.justPressed(B_BUTTON))
      {
        playerScore = 0;
        AIScore = 0;
        scoreMax = howManyWins;
        setupGame();
        gameState = STATE_GAME_PLAYING;
      }

      break;
    case STATE_GAME_PLAYING:
      arduboy.clear();
      updateStage();
      if (arduboy.everyXFrames(2))
      {
        if (!ballMoves)
        {
          ballTimer ++;
          if (ballTimer == 60)
          {
            ballMoves = true;
            ballTimer = 0;
          }
        }
      }
      if (arduboy.pressed(RIGHT_BUTTON) && (player.x < 20)) player.x += player.xSpeed;
      if (arduboy.pressed(LEFT_BUTTON) && (player.x > 4)) player.x -= player.xSpeed;
      if (arduboy.pressed(UP_BUTTON) && (player.y > 4)) player.y -= player.ySpeed;
      if (arduboy.pressed(DOWN_BUTTON) && (player.y + 24 < HEIGHT - 4)) player.y += player.ySpeed;
      if (arduboy.justPressed(B_BUTTON))ballMoves = true;


      if (arduboy.justPressed(A_BUTTON))
      {
        arduboy.clear();
        gameState = STATE_GAME_PAUSE;
      }
      break;
    case STATE_GAME_OVER:
      arduboy.clear();
      if (AIScore == scoreMax)
      {
        arduboy.drawBitmap(0, 0, fishstick_bitmap, 128, 64, WHITE);
      }
      if (playerScore == scoreMax)
      {
        switch (winlose)
        {
          case 0:
            arduboy.drawBitmap(0, 0, woman_bitmap, 128, 64, WHITE);
            break;
          case 1:
            arduboy.drawBitmap(0, 0, fish_bitmap, 128, 64, WHITE);
            break;
          case 2:
            arduboy.drawBitmap(0, 0, mermaid_bitmap, 128, 64, WHITE);
            break;
        }
      }
      if (arduboy.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.clear();
        gameState = STATE_MENU_MAIN;
      }
      break;
    case STATE_GAME_PAUSE:
      arduboy.drawBitmap(0, 0, pause_bitmap, 128, 64, WHITE);
      if (arduboy.justPressed(A_BUTTON))
      {

        //afterPause();
        gameState = STATE_GAME_PLAYING;
      }
      break;
    }
  */
};

void stateGamePause()
{

  if (arduboy.justPressed(UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON)) gameState = STATE_GAME_PLAYING ;
};

void stateGameOver()
{

  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
};


#endif
