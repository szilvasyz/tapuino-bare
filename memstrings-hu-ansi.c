// FIGYELEM!
// Ez a file ANSI k�dol�s� karaktereket tartalmaz, nem alkalmas az Arduino IDE-ben t�rt�n� jav�t�sra 
// Olyan programmal kell szerkeszteni, ami k�pes kezelni az ANSI k�dol�st (pl. notepad++)
//
// WARNING!
// This file contains ANSI-encoded charachers, that's why it is not suitable for editing in Arduino IDE!
// Please edit this file with an editor that is capable to handle ANSI charset (for example Notepad++)

#include <avr/pgmspace.h>
#include "config.h"
#include "memstrings.h"

#ifdef TAPUINO_LANGUAGE_HU_ANSI

const char S_DEFAULT_RECORD_DIR[] PROGMEM =  "/recorded";
const char S_RECORDING[] PROGMEM = "Ment ";
const char S_SELECT_RECORD_MODE[] PROGMEM = "N�v m�d:";
const char S_REC_MODE_MANUAL[] PROGMEM = "K�zi";
const char S_REC_MODE_AUTO[] PROGMEM = "Auto";
const char S_ENTER_FILENAME[] PROGMEM = "N�v";

const char S_INIT[] PROGMEM = "Felk�szit...";
const char S_INIT_FAILED[] PROGMEM = "Nem siker�lt!";
const char S_INIT_OK[] PROGMEM = "Felk�szit�s OK.";

const char S_NO_FILES_FOUND[] PROGMEM = "Nincs f�jl!";
const char S_SELECT_FILE[] PROGMEM = "V�lassz f�jlt:";
const char S_SELECT_MODE[] PROGMEM = "V�lassz m�dot:";
const char S_MODE_PLAY[] PROGMEM = "Play";
const char S_MODE_RECORD[] PROGMEM = "Ment";
const char S_READY_RECORD[] PROGMEM = "K�sz..";
const char S_PRESS_START[] PROGMEM = "Nyomj STARTot";

const char S_MODE_OPTIONS[] PROGMEM = "Opci�k";
const char S_OPTION_SIGNAL[] PROGMEM = "Invert�l�s";
const char S_OPTION_KEY_REPEAT[] PROGMEM = "Gomb sebess�g";
const char S_OPTION_TICKER_SPEED[] PROGMEM = "Ticker sebess�g";
const char S_OPTION_TICKER_HOLD[] PROGMEM = "Ticker hold";
const char S_OPTION_REC_FINALIZE[] PROGMEM = "Ment�s befejez�s";
const char S_OPTION_REC_AUTO_FINALIZE[] PROGMEM = "Auto befejez�s";

const char S_MKDIR_FAILED[] PROGMEM = "MKDIR hiba!";
const char S_CHDIR_FAILED[] PROGMEM = "CHDIR hiba!";
const char S_READ_FAILED[] PROGMEM = "READ hiba!";
const char S_OPEN_FAILED[] PROGMEM = "OPEN hiba!";
const char S_INVALID_TAP[] PROGMEM = "Nem val�s TAP!";
const char S_INVALID_SIZE[] PROGMEM = "Nem val�s m�ret!";

const char S_LOADING[] PROGMEM = "T�lt:";
const char S_OPERATION_COMPLETE[] PROGMEM = "K�sz!";
const char S_OPERATION_ABORTED[] PROGMEM = "Megszakitva!";

const char S_OPTION_MACHINE_TYPE[] PROGMEM = "G�p";
const char S_OPTION_VIDEO_MODE[] PROGMEM = "Video ";//video

#endif
