#include <avr/pgmspace.h>
#include "config.h"
#include "memstrings.h"

#ifdef TAPUINO_LANGUAGE_HU

const char S_DEFAULT_RECORD_DIR[] PROGMEM =  "/felvetel";
const char S_RECORDING[] PROGMEM = "Rogzites";
const char S_SELECT_RECORD_MODE[] PROGMEM = "Filenev mod:";
const char S_REC_MODE_MANUAL[] PROGMEM = "Kezi";
const char S_REC_MODE_AUTO[] PROGMEM = "Automata";
const char S_ENTER_FILENAME[] PROGMEM = "Nev megadasa";

const char S_INIT[] PROGMEM = "Indulas...";
const char S_INIT_FAILED[] PROGMEM = "Hibas indulas!";
const char S_INIT_OK[] PROGMEM = "Indulas rendben.";

const char S_NO_FILES_FOUND[] PROGMEM = "Nincs file!";
const char S_SELECT_FILE[] PROGMEM = "File valasztas:";
const char S_SELECT_MODE[] PROGMEM = "Modvalasztas:";
const char S_MODE_PLAY[] PROGMEM = "Lejatszas";
const char S_MODE_RECORD[] PROGMEM = "Felvetel";
const char S_READY_RECORD[] PROGMEM = "Kesz...";
const char S_PRESS_START[] PROGMEM = "Nyomj START-ot";

const char S_MODE_OPTIONS[] PROGMEM = "Opciok";
const char S_OPTION_SIGNAL[] PROGMEM = "Jelforditas";
const char S_OPTION_KEY_REPEAT[] PROGMEM = "Bill. sebesseg";
const char S_OPTION_TICKER_SPEED[] PROGMEM = "Utem sebesseg";
const char S_OPTION_TICKER_HOLD[] PROGMEM = "Utem tartas";
const char S_OPTION_REC_FINALIZE[] PROGMEM = "Felv. lezaras";
const char S_OPTION_REC_AUTO_FINALIZE[] PROGMEM = "Auto lezaras";
const char S_OPTION_MOTOR_CTL[] PROGMEM = "Motorvezerles";
const char S_OPTION_REC_TYPE[] PROGMEM = "Felvetel verzio";

const char S_MKDIR_FAILED[] PROGMEM = "MKDIR hiba!";
const char S_CHDIR_FAILED[] PROGMEM = "CHDIR hiba!";
const char S_READ_FAILED[] PROGMEM = "READ hiba!";
const char S_OPEN_FAILED[] PROGMEM = "OPEN hiba!";
const char S_INVALID_TAP[] PROGMEM = "Hibas TAP!";
const char S_INVALID_SIZE[] PROGMEM = "Hibas meret!";

const char S_LOADING[] PROGMEM = "Loading:";
const char S_OPERATION_COMPLETE[] PROGMEM = "Kesz!";
const char S_OPERATION_ABORTED[] PROGMEM = "Megszakitva!";

const char S_OPTION_MACHINE_TYPE[] PROGMEM = "Geptipus";
const char S_OPTION_VIDEO_MODE[] PROGMEM = "Video";

#endif
