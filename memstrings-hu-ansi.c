// FIGYELEM!
// Ez a file ANSI kódolású karaktereket tartalmaz, nem alkalmas az Arduino IDE-ben történõ javításra 
// Olyan programmal kell szerkeszteni, ami képes kezelni az ANSI kódolást (pl. notepad++)
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
const char S_SELECT_RECORD_MODE[] PROGMEM = "Név mód:";
const char S_REC_MODE_MANUAL[] PROGMEM = "Kézi";
const char S_REC_MODE_AUTO[] PROGMEM = "Auto";
const char S_ENTER_FILENAME[] PROGMEM = "Név";

const char S_INIT[] PROGMEM = "Felkészit...";
const char S_INIT_FAILED[] PROGMEM = "Nem sikerült!";
const char S_INIT_OK[] PROGMEM = "Felkészités OK.";

const char S_NO_FILES_FOUND[] PROGMEM = "Nincs fájl!";
const char S_SELECT_FILE[] PROGMEM = "Válassz fájlt:";
const char S_SELECT_MODE[] PROGMEM = "Válassz módot:";
const char S_MODE_PLAY[] PROGMEM = "Play";
const char S_MODE_RECORD[] PROGMEM = "Ment";
const char S_READY_RECORD[] PROGMEM = "Kész..";
const char S_PRESS_START[] PROGMEM = "Nyomj STARTot";

const char S_MODE_OPTIONS[] PROGMEM = "Opciók";
const char S_OPTION_SIGNAL[] PROGMEM = "Invertálás";
const char S_OPTION_KEY_REPEAT[] PROGMEM = "Gomb sebesség";
const char S_OPTION_TICKER_SPEED[] PROGMEM = "Ticker sebesség";
const char S_OPTION_TICKER_HOLD[] PROGMEM = "Ticker hold";
const char S_OPTION_REC_FINALIZE[] PROGMEM = "Mentés befejezés";
const char S_OPTION_REC_AUTO_FINALIZE[] PROGMEM = "Auto befejezés";

const char S_MKDIR_FAILED[] PROGMEM = "MKDIR hiba!";
const char S_CHDIR_FAILED[] PROGMEM = "CHDIR hiba!";
const char S_READ_FAILED[] PROGMEM = "READ hiba!";
const char S_OPEN_FAILED[] PROGMEM = "OPEN hiba!";
const char S_INVALID_TAP[] PROGMEM = "Nem valós TAP!";
const char S_INVALID_SIZE[] PROGMEM = "Nem valós méret!";

const char S_LOADING[] PROGMEM = "Tölt:";
const char S_OPERATION_COMPLETE[] PROGMEM = "Kész!";
const char S_OPERATION_ABORTED[] PROGMEM = "Megszakitva!";

const char S_OPTION_MACHINE_TYPE[] PROGMEM = "Gép";
const char S_OPTION_VIDEO_MODE[] PROGMEM = "Video ";//video

#endif
