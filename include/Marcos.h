#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto BAR_SIZE = 200;
constexpr auto M_PI = 3.14;



const std::string MAIN_FONT = "Browni.ttf";

constexpr auto battery = 'A';
constexpr auto bush = 'B';
constexpr auto dCar = 'C';
constexpr auto dHelicopter = 'D';
constexpr auto wall = 'E';
constexpr auto gate = 'F';
constexpr auto stone = 'G';
constexpr auto tree = 'H';
constexpr auto skeleton = 'I';
constexpr auto dTree = 'J';
constexpr auto heart = 'K';
constexpr auto weaponAnimation = 'L';
constexpr auto shild = 'M';
constexpr auto skeletons = 'N';
constexpr auto house = 'O';
constexpr auto AnimationPic = 'P';
constexpr auto Ruined = 'Q';
constexpr auto hhelicopter = 'R';
constexpr auto smallRuined = 'S';
constexpr auto grende = 'T';
constexpr auto Prisionr = 'U';
constexpr auto Clock = 'V';
constexpr auto spot = 'W';

constexpr auto load_Player = 1;
constexpr auto load_upperWallAlong = 2;
constexpr auto load_WAll = 3;
constexpr auto load_Door = 4;
constexpr auto load_Bush = 5;
constexpr auto load_dCar = 6;
constexpr auto load_dHelicopter = 7;
constexpr auto load_dTrre = 8;
constexpr auto load_Gate = 9;
constexpr auto load_solider = 10;
constexpr auto load_Stone = 11;
constexpr auto load_Tree = 12;
constexpr auto load_Cannon = 12;
constexpr auto load_Bullet = 13;
constexpr auto load_Tank = 15;


constexpr auto BLUE = 80;
constexpr auto GRREN = 60;
constexpr auto YELLOW = 40;
constexpr auto ORANGE = 20;
constexpr auto RED = 0;


const std::string bgTextures[6] = { "losePic.jpg","winPic.png","background.PNG","bgmenu.jpg", "settings.png" ,"help.png"};

enum MenuButtons
{
	_newGame, _help, _sound, _escape, NUM_OF_MBUTTONS
};
const std::vector<std::string> MENU_BUTTONS_STRINGS =
{
	{"NewGame"},  {"Help"},{"Sound"}, {"Exit"}
};

enum GameButtons {
	_pause, _continue, _restart, _exitButton,
	_pauseHL, _continueHL, _restartHL, _exitButtonHL,
	NUM_OF_GBUTTONS
};

const std::string gameButtonsTexts[NUM_OF_GBUTTONS] = {
	"pauseButton.png",
	"continueButton.png",
	"restartButton.png",
	"exitButton.png",
	"pauseButtonHL.png",
	"continueButtonHL.png",
	"restartButtonHL.png",
	"exitButtonHL.png",
};


enum ButtonIndexes {
	_continueIndex, _restartIndex, _exitIndex
};


const sf::Vector2f screenButtonsStart = sf::Vector2f(380, 120);
const int buttonOffset = 90;
const sf::Vector2f returnButtonPos(1020, 30);



const sf::Vector2f volButtonStart(570, 310);
enum VolumeButtons {
	_volInc, _volDec, _volMute,
	_volIncHL, _volDecHL, _volMuteHL,
	NUM_OF_VOL_BUTTONS,
};

const std::vector<std::string> volTextures =
{
	{"volInc.png"},
	{"volDec.png"},
	{"volMute.png"},
	{"volIncHL.png"},
	{"volDecHL.png"},
	{"volMuteHL.png"}
};


constexpr auto DEFAULT_VOLUME = 30;
const std::vector<std::string> soundList =
{

	"HoverSound.wav",
	"bonus.wav",
	"cannonfire.wav",
	"gameover.wav",
	"grenadeExplosion.wav",
	"warplanes.wav",
	"engine.wav",
	"shoot.wav",
	"applause.wav"
};
