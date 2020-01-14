#include "dictglobal.h"

#include "dict.h"



/**
 * Zmienna globalna przechowująca ID Słownika Globalnego
 */
static unsigned long id;

/**
 * Zmienna globalna przechowująca informację o tym, czy Słownik Globalny został już zainicjalizowany
 */
static bool is_initialized = false;

unsigned long dict_global() {
    if (!is_initialized) { //Słownik nie był jeszcze zainicjalizowany
        //Oznaczamy, że był już zainicjalizowany
        is_initialized = true;
        //Inicjalizujemy
        id = dict_new();
    }

    return id;
}
