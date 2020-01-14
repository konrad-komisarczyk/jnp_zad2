#include "dict.h"

#include "dictglobal.h"
#include <unordered_map>
#include <iostream>
#include <cassert>

#ifndef DNDEBUG
static const bool debug = true;
#else
static const bool debug = false;
#endif

#define DICTS_STRUCTURE std::unordered_map<unsigned long, std::unordered_map<std::string, std::string>>



/**
 * Licznik identyfikatorów słowników.
 * Przechowuje identyfikator ostatnio utworzonego słownika.
 */
static unsigned long new_dict_id = 0;

/**
 * Funkcja zwracająca globalną strukturę przechowującą słowniki. Dba o poprawną inicjalizację tej struktury.
 * @return mapa (id słownika -> słownik)
 */
static DICTS_STRUCTURE& dicts() {
    static DICTS_STRUCTURE* d = new DICTS_STRUCTURE();
    return *d;
}

/**
 * Wypisuje komunikat diagnostyczny @param content
 */
static void print_diagnostic_message(std::string content) {
    if (debug) {
        std::cerr << content << std::endl;
    }
}

/**
 * Informacja o tym, czy istnieje słownik o identyfikatorze @param id
 */
static bool dict_exists(unsigned long id) {
    return (dicts().find(id) != dicts().end());
}

/**
 * Informacja o tym, czy słownik o identyfikatorze @param id zawiera klucz @param key
 */
static bool dict_contains(unsigned long id, const char* key) {
    assert(dict_exists(id));
    assert(key);

    return (dicts()[id].find(key) != dicts()[id].end());
}

/**
 * Sprawdza, czy możemy stworzyć dodatkowy słownik - jeżeli tak, zwiększa licznik identyfikatorów.
 */
static bool update_new_dict_id() {
    if (new_dict_id + 1 == 0) {
        return false;
    } else {
        new_dict_id ++;
        return true;
    }
}

/**
 * Zwraca nazwę słownika o identyfikatorze @param id
 * Używana do wypisywania komunikatów diagnostycznych
 */
static std::string dict_name(unsigned long id) {
    if (id == dict_global()) {
        return "the Global Dictionary";
    } else {
        return ("dict " + std::to_string(id));
    }
}

/**
 * Jeżeli @param string jest pusty zwraca "NULL", w p. p. zwraca @param string
 * Używana do wypisywania komunikatów diagnostycznych
 */
static std::string string_or_null(const char *string) {
    return (string ? std::string(string) : "NULL");
}



unsigned long dict_new() {
    print_diagnostic_message("dict_new()");

    if (update_new_dict_id()) { //Możemy stworzyć nowy słownik
        unsigned long id = new_dict_id; //zaktualizowane przez update_new_dict_id() id słownika

        //Tworzymy słownik
        dicts()[id];

        print_diagnostic_message("dict_new: " + dict_name(id) + " has been created");
        
        return id;
    } else { //Nie możemy stworzyć nowego słownika
        print_diagnostic_message("Number of dictionaries exceeded. New dictionary can not be created. "
                                         "Returning id of the Global Dictionary");
        return dict_global();
    }
}

void dict_delete(unsigned long id) {
    print_diagnostic_message("dict_delete(" + std::to_string(id) + ")");

    if (id == dict_global()) {
        //Nie można usunąć Słownika Globalnego
        print_diagnostic_message("dict_delete: an attempt to remove the Global Dictionary");
    } else if (dict_exists(id)) {
        //Usuwamy elementy słownika
        dicts()[id].clear();
        //Usuwamy słownik
        dicts().erase(id);

        print_diagnostic_message("dict_delete: " + dict_name(id) + " has been deleted");
    } else { //Słownik nie istnieje
        print_diagnostic_message("dict_delete: an attempt to delete non-existent dictionary");
    }

}

size_t dict_size(unsigned long id) {
    print_diagnostic_message("dict_size(" + std::to_string(id) + ")");

    if (dict_exists(id)) {
        size_t size = dicts()[id].size();

        print_diagnostic_message("dict_size: " + dict_name(id) +
        " contains " + std::to_string(size) + " element(s)");

        return size;
    } else { //Słownik nie istnieje
        print_diagnostic_message("dict_size: " + dict_name(id) + " does not exist");

        return 0;
    }
}

void dict_insert(unsigned long id, const char* key, const char* value) {
    print_diagnostic_message("dict_insert(" + std::to_string(id) + ", " + string_or_null(key) + ", "
                             + string_or_null(value) + ")");

    if (!key) {
        print_diagnostic_message("dict_insert: " + dict_name(id) + ", an attempt to insert NULL key");
    }
    if (!value) {
        print_diagnostic_message("dict_insert: " + dict_name(id) + ", an attempt to insert NULL value");
    }
    if (!dict_exists(id)) {
        print_diagnostic_message("dict_insert: " + dict_name(id) + " does not exist");
    }

    if (dict_exists(id) && key && value) {
        if (id == dict_global()) { //Wstawianie do Słownika Globalnego

            //Jeżeli wstawiany klucz jest już w słowniku, usuwamy go
            if (dict_contains(id, key)) {
                dicts()[id].erase(key);
            }

            //Teraz, mamy pewnosć, że w słowniku nie ma wstawianego klucza, więc dodanie go zwiększy rozmiar słownika
            if (dicts()[id].size() + 1 > MAX_GLOBAL_DICT_SIZE) {
                //Nie możemy wstawić klucza, bo słownik globalny przekroczyłby maksymalny rozmiar

                print_diagnostic_message("dict_insert: an attempt to exceed max size of The Global Dictionary");
            } else { //Możemy wstawić klucz
                //Wstawiamy do slownika
                dicts()[id][key] = value;

                print_diagnostic_message("dict_insert: " + dict_name(id)
                                         + ", the pair (\"" + key + "\", \"" + value + "\") has been inserted");
            }

        } else { //Wstawianie do normalnego słownika (nie Słownika Globalnego)

            //Wstawiamy do slownika
            dicts()[id][key] = value;

            print_diagnostic_message("dict_insert: " + dict_name(id)
                                     + ", the pair (\"" + key + "\", \"" + value + "\") has been inserted");
        }
    }
}

void dict_remove(unsigned long id, const char* key) {
    print_diagnostic_message("dict_remove(" + std::to_string(id) + ", \"" + string_or_null(key) + "\")");

    if (!key) {
        print_diagnostic_message("dict_remove: the key is NULL, so no dictionary contains it");
    }

    if (dict_exists(id)) {
        if (dict_contains(id, key)) {
            //Jeżeli słownik zawiera klucz, usuwamy ten klucz z niego
            dicts()[id].erase(key);

            print_diagnostic_message("dict_remove: " + dict_name(id) + ", the key \"" + key + "\" has been removed");
        } else { //Słownik nie zawiera klucza key
            print_diagnostic_message("dict_remove: " + dict_name(id) + " does not contain the key \"" + key + "\"");
        }
    } else { //Słownik id nie istnieje
        print_diagnostic_message("dict_remove: " + dict_name(id) + " does not exist");
    }
}

const char* dict_find(unsigned long id, const char* key) {
    print_diagnostic_message("dict_find(" + std::to_string(id) + ", \"" + string_or_null(key) + "\")");

    if (!key) {
        print_diagnostic_message("dict_find: the key is NULL, so not found");

        return NULL;
    }

    if (dict_exists(id) && dict_contains(id, key)) {
        //Jeżeli słownik istnieje i zawiera klucz, wyciągamy wskazywaną przez klucz wartość
        const char *value = dicts()[id].find(key)->second.c_str();

        print_diagnostic_message("dict_find: " + dict_name(id) + ", the key \"" + key
                                 + "\" has the value \"" + value + "\"");

        return value;
    } else { //Słownik nie istnieje lub nie zawiera klucza
        //Udajemy się do słownika globalnego

        if (!dict_exists(id)) {
            print_diagnostic_message("dict_find: " + dict_name(id) + " does not exist");
        }
        print_diagnostic_message("dict_find: the key \"" + string_or_null(key)
                                 + "\" not found, looking up " + dict_name(dict_global()));

        if (dict_contains(dict_global(), key)) {
            //Jeżeli Słownik Globalny zawiera klucz, wyciągamy wskazywaną przez klucz wartość
            const char *value = dicts()[dict_global()].find(key)->second.c_str();

            print_diagnostic_message("dict_find: " + dict_name(id) + ", the key \"" + key
                                     + "\" has the value \"" + value + "\"");

            return value;
        } else { //Słownik Globalny nie zawiera klucza key

            print_diagnostic_message("dict_find: the key \"" + string_or_null(key) + "\" not found");

            return NULL;
        }
    }
}

void dict_clear(unsigned long id) {
    print_diagnostic_message("dict_clear(" + std::to_string(id) + ")");

    if (dict_exists(id)) {
        //Czyścimy słownik
        dicts()[id].clear();

        print_diagnostic_message("dict_clear: " + dict_name(id) + " has been cleared");
    } else { //Słownik nie istnieje
        print_diagnostic_message("dict_clear: " + dict_name(id) + " does not exist");
    }
}

void dict_copy(unsigned long src_id, unsigned long dst_id) {
    print_diagnostic_message("dict_copy(" + std::to_string(src_id) + ", " + std::to_string(dst_id) + ")");

    if (dict_exists(src_id) && dict_exists(dst_id)) {
        if (src_id == dst_id) {
            //Jeżeli oba argumenty są równe nic nie robimy

            print_diagnostic_message("dict_copy: " + dict_name(src_id) + ", " + dict_name(dst_id)
                      + "are the same, so no copying will be done");
        } else { //Słowniki są różnymi słownikami
            //Przeglądamy kolejno każdy element pierwszego słownika
            for (auto it = dicts()[src_id].begin(); it != dicts()[src_id].end(); ++it) {
                //Wstawiamy element do słownika docelowego (dst_id)
                dict_insert(dst_id, (it->first).c_str(), (it->second).c_str());
            }

            print_diagnostic_message("dict_copy: " + dict_name(src_id) + " has been copied to "
                                     + dict_name(dst_id));
        }
    } else { //Conajmniej jeden ze słowników nie istnieje
        if (!dict_exists(src_id)) {
            print_diagnostic_message("dict_copy: " + dict_name(src_id)
                                     + " (source dictionary) does not exist");
        }
        if (!dict_exists(dst_id)) {
            print_diagnostic_message("dict_copy: " + dict_name(dst_id)
                                     + " (destination dictionary) does not exist");
        }
    }
}
