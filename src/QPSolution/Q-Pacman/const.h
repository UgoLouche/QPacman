#pragma once

//Program is supposedely robust to MINOR change in this file
//Expect to run into overflows (especially on wrt Q-register) if values
//changes too much. 

//Board
#define CELL_SIZE 25
#define BOARD_WIDTH 32
#define BOARD_HEIGHT 20

//GamePlay
#define TURN_LENGHT 0.25f
#define MAX_HEALTH 100
#define GUM_SCORE 10
#define GHOST_SCORE 100
#define GHOSTS_DAMAGE 100
#define GUM_RESPAWN 120
#define GHOSTS_RESPAWN 20

//Logger
#define OPENING_STR "===================NEW LOG==================="
#define CLOSING_STR "===================END LOG==================="

//Quantum  !! Don't expect anything to be robust to changes here !!
#define Q_REGISTER_SIZE 65536 //2^16
#define INTERNAL_STATE_SIZE 16

//Texture
#define TEST_TEXTURE "TextTest.png"
#define PLAYER_TEXTURE "PlayerText.png"//"PlayerText.png"
#define BUTTONS_TEXTURE "InputText.png"
#define GUM_TEXTURE "GumText.png"
#define SGUM_TEXTURE "SuperGumText.png"
#define GHOST_TEXTURE "GhostText.png"
#define UI_TEX_SIZE 25

//Window
#define WIN_WIDTH 800.0f
#define WIN_HEIGHT 600.0f
#define WIN_NAME "Q-Pacman"
#define HUD_HEIGHT 100.0f

//UI
#define FONT_FILE "arial.ttf"
#define FPS_TEXT  "FPS: "
#define SCORE_TEXT "SCORE: "
#define SCORE_SIZE 10
#define HEALTH_WIDTH 770
#define HEALTH_HEIGHT 30
#define PAUSE_TEXT "PAUSE"
#define PAUSE_SUBTEXT "Game Paused, press P to resume or N to start a new game"
#define GAMEOVER_TEXT "GAME OVER !"
#define GAMEOVER_SUBTEXT "Game Over, press N to start a new game"

//Ghosts AI
#define HUNTER_CHASE_TIME 30
#define HUNTER_SCATTER_TIME 10
#define LAZY_CHASE_TIME 10
#define LAZY_SCATTER_TIME 30
#define RANDOM_CHASE_TIME 10
#define RANDOM_SCATTER_TIME 10