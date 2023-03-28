#include <avr/pgmspace.h>
#include "config.h"
#include "memstrings.h"

#ifdef TAPUINO_LANGUAGE_HU_ANSI

// macros for ANSI codes of special characters used
#define aa "\xE1" //á
#define ee "\xE9" //é
#define oe "\xF6" //ö
#define ue "\xFC" //ü
#define uu "\xFA" //ú
#define oo "\xF3" //ó

const char S_DEFAULT_RECORD_DIR[] PROGMEM =  "/recorded";
const char S_RECORDING[] PROGMEM = "Ment ";
const char S_SELECT_RECORD_MODE[] PROGMEM = "N"ee"v m"oo"d:";
const char S_REC_MODE_MANUAL[] PROGMEM = "K"ee"zi";
const char S_REC_MODE_AUTO[] PROGMEM = "Auto";
const char S_ENTER_FILENAME[] PROGMEM = "N"ee"v";

const char S_INIT[] PROGMEM = "Felk"ee"szit...";
const char S_INIT_FAILED[] PROGMEM = "Nem siker"ue"lt!";
const char S_INIT_OK[] PROGMEM = "Felk"ee"szit"ee"s OK.";

const char S_NO_FILES_FOUND[] PROGMEM = "Nincs f"aa"jl!";
const char S_SELECT_FILE[] PROGMEM = "V"aa"lassz f"aa"jlt:";
const char S_SELECT_MODE[] PROGMEM = "V"aa"lassz m"oo"dot:";
const char S_MODE_PLAY[] PROGMEM = "Play";
const char S_MODE_RECORD[] PROGMEM = "Ment";
const char S_READY_RECORD[] PROGMEM = "K"ee"sz..";
const char S_PRESS_START[] PROGMEM = "Nyomj STARTot";

const char S_MODE_OPTIONS[] PROGMEM = "Opci"oo"k";
const char S_OPTION_SIGNAL[] PROGMEM = "Invert"aa"l"aa"s";
const char S_OPTION_KEY_REPEAT[] PROGMEM = "Gomb sebess"ee"g";
const char S_OPTION_TICKER_SPEED[] PROGMEM = "Ticker sebess"ee"g";
const char S_OPTION_TICKER_HOLD[] PROGMEM = "Ticker hold";
const char S_OPTION_REC_FINALIZE[] PROGMEM = "Ment"ee"s befejez"ee"s";
const char S_OPTION_REC_AUTO_FINALIZE[] PROGMEM = "Auto befejez"ee"s";
const char S_OPTION_MOTOR_CTL[] PROGMEM = "Motorvez"ee"rl"ee"s";

const char S_MKDIR_FAILED[] PROGMEM = "MKDIR hiba!";
const char S_CHDIR_FAILED[] PROGMEM = "CHDIR hiba!";
const char S_READ_FAILED[] PROGMEM = "READ hiba!";
const char S_OPEN_FAILED[] PROGMEM = "OPEN hiba!";
const char S_INVALID_TAP[] PROGMEM = "Hib"aa"s TAP!";
const char S_INVALID_SIZE[] PROGMEM = "Hib"aa"s m"ee"ret!";

const char S_LOADING[] PROGMEM = "T"oe"lt:";
const char S_OPERATION_COMPLETE[] PROGMEM = "K"ee"sz!";
const char S_OPERATION_ABORTED[] PROGMEM = "Megszakitva!";

const char S_OPTION_MACHINE_TYPE[] PROGMEM = "G"ee"p";
const char S_OPTION_VIDEO_MODE[] PROGMEM = "Video ";//video

#endif
