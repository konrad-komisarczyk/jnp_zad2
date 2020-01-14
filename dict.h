#ifndef JNP1ZAD2_DICT_H
#define JNP1ZAD2_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/**
 * Tworzy nowy, pusty słownik i zwraca jego identyfikator.
 */
unsigned long dict_new();

/**
 * Jeżeli istnieje słownik o identyfikatorze id, usuwa go, a w przeciwnym przypadku nic nie robi.
 */
void dict_delete(unsigned long id);

/**
 * Jeżeli istnieje słownik o identyfikatorze @param id, zwraca liczbę jego elementów, a w przeciwnym przypadku zwraca 0
 */
size_t dict_size(unsigned long id);

/**
 * Jeżeli istnieje słownik o identyfikatorze @param id oraz @param key != NULL
 * i @param value != NULL, wstawia wartość @param value pod kluczem key.
 * W przeciwnym przypadku nic nie robi.
 */
void dict_insert(unsigned long id, const char *key, const char *value);

/**
 * Jeżeli istnieje słownik o identyfikatorze @param id i zawiera klucz @param key,
 * to usuwa klucz oraz wartość związaną z tym kluczem,
 * a w przeciwnym przypadku nic nie robi.
 */
void dict_remove(unsigned long id, const char *key);

/**
 * Jeżeli istnieje słownik o identyfikatorze @param id i zawiera wartość pod kluczem @param key,
 * to zwraca wskaźnik do tej wartości,
 * a w przeciwnym przypadku zwraca wartość ze słownika globalnego.
 * Jeśli w słowniku globalnym nie ma wartości pod kluczem @param key, to zwraca NULL.
 */
const char *dict_find(unsigned long id, const char *key);

/**
 * Jeżeli istnieje słownik o identyfikatorze @param id, usuwa wszystkie jego elementy,
 * a w przeciwnym przypadku nic nie robi.
 */
void dict_clear(unsigned long id);

/**
 * Jeżeli istnieją słowniki o identyfikatorach @param src_id oraz @param dst_id,
 * to kopiuje zawartość słownika o identyfikatorze @param src_id do słownika o identyfikatorze @param dst_id,
 * a w przeciwnym przypadku nic nie robi.
 */
void dict_copy(unsigned long src_id, unsigned long dst_id);

#ifdef __cplusplus
}
#endif

#endif