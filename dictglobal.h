#ifndef JNP1ZAD2_DICTGLOBAL_H
#define JNP1ZAD2_DICTGLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Stała określa maksymalny rozmiar globalnego słownika.
 * Do globalnego słownika można wstawiać kolejne klucze z wartościami tylko,
 * gdy jego rozmiar po wstawieniu nie będzie przekraczał maksymalnego rozmiaru.
 */
const unsigned int MAX_GLOBAL_DICT_SIZE = 42;

/**
 * Zwraca identyfikator globalnego słownika, którego nie można usunąć.
 */
unsigned long dict_global();

#ifdef __cplusplus
}
#endif

#endif