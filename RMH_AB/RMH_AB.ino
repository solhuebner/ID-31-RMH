/*
 REVERSE MARMAID HOCKEY: http://www.team-arg.org/rmh-manual.html

 Arduboy version 1.4 : http://www.team-arg.org/rmh-downloads.html
 
 MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

 2015 - DRAGULA96 - ART WORK: JO3RI & UNCLESPORKY

 Game License: MIT : https://opensource.org/licenses/MIT

 */


//determine the game
#define GAME_ID 31

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "rm_bitmaps.h"
#include "GO_bitmaps.h"
#include "menu_bitmaps.h"
#include "numbers_bitmaps.h"


//define menu states (on main menu)
#define STATE_MENU_MAIN          0
#define STATE_MENU_HELP          1
#define STATE_MENU_INFO          3
#define STATE_MENU_SOUNDFX       4

//define menu choices (on main menu)
#define CHOOSE_HELP              1
#define CHOOSE_PLAY              2
#define CHOOSE_INFO              3
#define CHOOSE_CONF              4

//define game states (on main menu)
#define STATE_GAME_INIT          2
#define STATE_GAME_PLAYING       8
#define STATE_GAME_PAUSE         9
#define STATE_GAME_OVER          10

//define player & AI states (in game)
#define NORMAL_POSTURE           0
#define KICKING_POSTURE          1
#define HIT_IN_FACE_POSTURE      2

//define sound tones
#define KICK_TONE                500
#define SCORE_TONE               175
#define WALL_TONE                80
#define FACE_TONE                50
#define SUPERKICK_MAX            20

Arduboy2Base arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);

unsigned char gameState = STATE_MENU_MAIN;
int menuSelection;

byte ballState = 0;

byte currentBallFrame = 0;
byte playerScore = 0;
byte AIScore = 0;
byte playerState = NORMAL_POSTURE;
byte AIstate = NORMAL_POSTURE;
byte playerAnimateTimer = 0;
byte AiAnimateTimer = 0;
boolean ballMoves = false;
byte ballTimer = 0; //for making sure ball releases after timer if player does not press "B".
byte scoreMax;
byte winlose;
byte howManyWins = 4;
byte superKickMeter ;
boolean isSuperkicking = false;

class GameObject {
  public:
    byte x, y, width, height;
    int8_t xSpeed, ySpeed;
};

GameObject player, AI, ball;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.clear();
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  arduboy.display();
  delay(3000);
  gameState = STATE_MENU_MAIN;
  arduboy.initRandomSeed();
  menuSelection = CHOOSE_PLAY;
}


void loop()
{
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  switch (gameState)
  {
    case STATE_MENU_MAIN:
      // show the splash art
      arduboy.clear();
      arduboy.drawBitmap(0, 0, title_bitmap, 128, 56, WHITE);
      arduboy.drawBitmap(22, 56, mainmenu_bitmaps[menuSelection - 1], 83, 8, WHITE);
      if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 4))menuSelection++;
      if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 1))menuSelection--;
      if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
      break;
    case STATE_MENU_HELP: // QR code
      arduboy.clear();
      arduboy.drawBitmap(32, 0, qrcode_bitmap, 64, 64, 1);
      if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_INFO: // infoscreen
      arduboy.clear();
      arduboy.drawBitmap(14, 4, info_bitmap, 100, 56, 1);
      if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_SOUNDFX: // soundconfig screen
      arduboy.clear();
      arduboy.drawBitmap(0, 0, title_bitmap, 128, 56, WHITE);
      arduboy.drawBitmap(27, 56, soundYesNo_bitmaps[arduboy.audio.enabled()], 73, 8, 1);
      if (arduboy.justPressed(RIGHT_BUTTON)) arduboy.audio.on();
      if (arduboy.justPressed(LEFT_BUTTON)) arduboy.audio.off();
      if (arduboy.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.audio.saveOnOff();
        gameState = STATE_MENU_MAIN;
      }
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
  arduboy.display();
}

void updateStage()
{

  moveBall();
  AI_Logic();
  superKick();
  checkIfScored();
  checkCollisions();
  drawPlayArea();
  drawScores();
  checkAnimations();
  drawBall();
  checkWinLose();
}

void setupGame() {
  delay(400); //delay to show how score was made
  ballMoves = false;
  ballTimer = 0;
  superKickMeter = 0;
  player.xSpeed = 3;
  player.ySpeed = 3;
  player.x = 16;
  player.width = 16;
  player.height = 24;
  player.y = HEIGHT / 2 - player.height / 2;

  AI.x = WIDTH - 16 - 16;
  AI.y = player.y;
  AI.height = 24;
  AI.width = 16;
  AI.xSpeed = player.xSpeed;
  AI.ySpeed = 1;

  ball.x = WIDTH / 2 - 4;
  ball.y = HEIGHT / 2 - 4;
  ball.xSpeed = 0;
  ball.ySpeed = 0;
  randomizeBallDirection();

  ball.width = 8;
  ball.height = 8;
}

void randomizeBallDirection() {
  ball.xSpeed = 0;
  ball.ySpeed = 0;
  while (ball.xSpeed == 0) {
    ball.xSpeed = random(-3, 4);
  }
  while (ball.ySpeed == 0) {
    ball.ySpeed = random(-3, 4);
  }
}

void amountOfWins()
{
  arduboy.drawBitmap(0, 0, BBQgrill_bitmap, 128, 64, WHITE);
  arduboy.drawBitmap(61, 23, number_bitmaps[howManyWins], 6, 8, WHITE);
  for (byte shrimpAmount = 0; shrimpAmount < howManyWins; shrimpAmount++)
  {
    arduboy.drawBitmap(5 + (shrimpAmount * 17), 35, BBQshrimp_mask_bitmap, 16, 24, BLACK);
    arduboy.drawBitmap(5 + (shrimpAmount * 17), 35, BBQshrimp_bitmap, 16, 24, WHITE);
  }
}

void AI_Logic() {
  //AI IS DUMB
  byte followBall = random(0, 3);

  if (ball.xSpeed > 0 && ball.x > 20 && followBall == 0 ) { //ball is moving right and is about half screen and followBall == 0
    if (ball.y > AI.y && AI.y < HEIGHT - AI.height - 4) {
      // move down
      AI.y += AI.ySpeed;
    }
    if (ball.y < AI.y ) { // go up but only if AI feet do not go past the bottom of screen
      // move up
      AI.y -= AI.ySpeed;
    }
  }
}

void checkAnimations()
{
  if ((playerAnimateTimer > 0) && (playerState != NORMAL_POSTURE)) playerAnimateTimer --;
  else playerState = NORMAL_POSTURE;
  if ((AiAnimateTimer > 0) && (AIstate != NORMAL_POSTURE)) AiAnimateTimer --;
  else AIstate = NORMAL_POSTURE;
  
  arduboy.drawBitmap(player.x, player.y, player_bitmaps[playerState], 16, 24, WHITE);
  arduboy.drawBitmap(AI.x, AI.y, AI_bitmaps[AIstate], 16, 24, WHITE);
}

void superKickMeterAdd(byte amnt_)
{
  superKickMeter += amnt_;
  if (superKickMeter > SUPERKICK_MAX) superKickMeter = SUPERKICK_MAX;
}

void superKick()
{
  if (arduboy.justPressed(B_BUTTON))
  {

    if (superKickMeter == SUPERKICK_MAX)
    {
      playerState = KICKING_POSTURE; // always perform postore kicking for super kick when button pressed and super meter is full
      checkSuperKickCollisions();
    }
  }
}

void checkSuperKickCollisions()
{
  Rect rect;
  Point point = {.x = ball.x + 3, .y = ball.y + 3};

  rect.x = player.x + player.width; rect.y = player.y + player.height / 2; rect.width = 20; rect.height = player.height / 2;

  if (arduboy.collide(point, rect)) {
    superKickMeter = 0;
    ball.xSpeed = 10;
    ball.ySpeed = 0;
    isSuperkicking = true;
  }
}
void checkCollisions()
{

  Rect rect;
  Point point = {.x = ball.x + 3, .y = ball.y + 3};

  //check if ball hit player
  rect.x = player.x; rect.y = player.y; rect.width = 16; rect.height = 24;
  if (arduboy.collide(point, rect)) {
    if ((point.y < rect.y + 24) && (point.y > rect.y + 24 - 10)) { // if ball is on the bottom side
      //change state to kicking
      playerState = KICKING_POSTURE;
      playerAnimateTimer = 10;
      superKickMeterAdd(10);
      sound.tone(KICK_TONE, 100);
      if (ball.xSpeed < 0) ball.xSpeed --; //if ball is going left speed up ball

      if (ball.ySpeed < 0) // if ball is going up
        ball.ySpeed *= -1;  //revers the y speed
    }


    if (point.y < rect.y + 8) { // if ball is on the top side
      //change state to hitInTheFace
      sound.tone(FACE_TONE, 100);
      playerState = HIT_IN_FACE_POSTURE;
      playerAnimateTimer = 15;
      if (ball.ySpeed > 0) // if ball is going down
        ball.ySpeed *= -1;  //revers the y speed

    }

    if (point.x > rect.x + 10) { // if ball is on the right side
      if (ball.xSpeed < 0) { // if ball is going left

        ball.xSpeed *= -1; //reverse ball x speed
      }
    }

    if (point.x < rect.x + 5) { // if ball is on the left side
      if (ball.xSpeed > 0) // if ball is going right
        ball.xSpeed *= -1; //reverse ball x speed
    }
  }



  //check if ball hit AI
  rect.x = AI.x; rect.y = AI.y; rect.width = 16; rect.height = 24;
  if (arduboy.collide(point, rect)) {
    if (isSuperkicking) {
      isSuperkicking = false;

      randomizeBallDirection();
      if (ball.xSpeed > 0) ball.xSpeed *= -1;

    }

    if (point.y < rect.y + 20) { // if ball is on the bottom side
      //change state to kicking
      AIstate = KICKING_POSTURE;
      sound.tone(KICK_TONE, 100);
      if (ball.xSpeed > 0) ball.xSpeed ++ ; //if ball is going right speed up ball
      if (ball.ySpeed < 0) // if ball is going up
        ball.ySpeed *= -1;  //revers the y speed
    }


    if (point.y < rect.y + 4) { // if ball is on the top side
      //change state to hitInTheFace
      sound.tone(FACE_TONE, 100);
      AIstate = HIT_IN_FACE_POSTURE;
      if (ball.ySpeed > 0) // if ball is going down
        ball.ySpeed *= -1;  //revers the y speed

    }

    if (point.x > rect.x + 10) { // if ball is on the right side
      if (ball.xSpeed < 0) // if ball is going left
        ball.xSpeed *= -1; //reverse ball x speed
    }

    if (point.x < rect.x + 5) { // if ball is on the left side
      if (ball.xSpeed > 0) // if ball is going right
        ball.xSpeed *= -1; //reverse ball x speed
    }


  }

}

void checkIfScored() {
  Rect rect;
  Point point;
  byte goalSize = 12;
  point.x = ball.x + 3; point.y = ball.y + 3;

  //check upper right corner
  rect.x = 0; rect.y = 0; rect.width = goalSize; rect.height = goalSize;
  if (arduboy.collide(point, rect))
  {
    sound.tone(SCORE_TONE, 100);
    AIScore ++;
    setupGame();
  }
  //check lower right corner
  rect.x = 0; rect.y = HEIGHT - goalSize; rect.width = goalSize; rect.height = goalSize;
  if (arduboy.collide(point, rect))
  {
    sound.tone(SCORE_TONE, 100);
    AIScore ++;
    setupGame();
  }

  //check upper left corner
  rect.x = WIDTH - goalSize; rect.y = 0; rect.width = goalSize; rect.height = goalSize;
  if (arduboy.collide(point, rect))
  {
    sound.tone(SCORE_TONE, 100);
    playerScore ++;
    setupGame();
  }

  //check lower left corner
  rect.x = WIDTH - goalSize; rect.y = HEIGHT - goalSize; rect.width = goalSize; rect.height = goalSize;
  if (arduboy.collide(point, rect))
  {
    sound.tone(SCORE_TONE, 100);
    playerScore ++;
    setupGame();
  }

}

void drawScores()
{
  arduboy.drawBitmap(48, 54, number_bitmaps[playerScore], 6, 8, WHITE);
  arduboy.drawBitmap(75, 54, number_bitmaps[AIScore], 6, 8, WHITE);
}


void drawBall() {
  if (arduboy.everyXFrames(2))
  {
    currentBallFrame ++;
    if (currentBallFrame > 3) currentBallFrame = 0;
  }
  arduboy.drawBitmap(ball.x, ball.y, shrimp_bitmaps[currentBallFrame], 8, 8, WHITE);
}

void moveBall()
{
  if (ballMoves)
  {
    byte oldX = ball.x, oldY = ball.y;
    ball.x += ball.xSpeed;
    ball.y += ball.ySpeed;

    //IF BALL HITS LEFT WALL
    if (ball.x < 4)
    {
      sound.tone(WALL_TONE, 100);
      ball.x = oldX;
      ball.xSpeed *= -1;
    }
    //IF BALL HITS RIGHT WALL
    if (ball.x + ball.width > WIDTH - 4 )
    {
      sound.tone(WALL_TONE, 100);
      ball.x = oldX;
      if (!isSuperkicking) {
        ball.xSpeed *= -1;
      }
      else if (isSuperkicking) {
        isSuperkicking = false;
        randomizeBallDirection();
        if (ball.xSpeed > 0) ball.xSpeed *= -1;
      }
    }
    //IF BALL HITS TOP WALL
    if (ball.y < 4)
    {
      sound.tone(WALL_TONE, 100);
      ball.y = oldY;
      ball.ySpeed *= -1;
    }
    //IF BALL HITS BOTTOM WALL
    if (ball.y + ball.height > HEIGHT )
    {
      sound.tone(WALL_TONE, 100);
      ball.y = oldY;
      ball.ySpeed *= -1;
    }
  }

}
void checkWinLose()
{
  if (playerScore == scoreMax || AIScore == scoreMax )
  {
    winlose = random(0, 3);
    gameState = STATE_GAME_OVER;
  }
}

void drawPlayArea() {
  //draw play field
  arduboy.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  arduboy.drawFastVLine(WIDTH / 2, 0, HEIGHT, WHITE);
  arduboy.drawFastVLine(WIDTH / 2 - 28, 0, HEIGHT, WHITE);
  arduboy.drawFastVLine(WIDTH / 2 + 28, 0, HEIGHT, WHITE);
  arduboy.drawCircle(WIDTH / 2, HEIGHT / 2, 16, WHITE);

  //draw goal areas
  arduboy.fillCircle(0, 0, 12, WHITE);
  arduboy.fillCircle(0, HEIGHT, 12, WHITE);
  arduboy.fillCircle(WIDTH, HEIGHT, 12, WHITE);
  arduboy.fillCircle(WIDTH, 0, 12, WHITE);
}



