#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template<class T>
class CacheManager {
    private:
        int capacity;
        map <string, pair<T, string>> cache_data;
        bool write_file(string, T);
    public:
        CacheManager(int); // recibe la capacidad en el int
        ~CacheManager();

        void insert(string key, T obj); // recibe la key y el objeto a guardar
        T get(string key); // recibe la key y retorna el objeto

        // agregar las funciones necesarias
}

template<class T>
CacheManager<T>::CacheManager(int capacity) {
    this->capacity = capacity;
}

template<class T>
CacheManager<T>::~CacheManager() {}

template<class T>
bool CacheManager<T>::write_file(string key, T obj){
    return true;
}

template<class T>
void CacheManager<T>::insert(string key, T obj) {
    // Cada llamada a insert(), La inserci ́on del T Obj se realizar ́a en la cache y
    // en el archivo. Si ya exist ́ıa la clave, actualiza el Obj.
    

}

template<class T>
T CacheManager<T>::get(string key) {
    /**
    Al realizar un get(), si no se encuentra en la cache en RAM se lo buscar ́a en
    el archivo. Si se lo encuentra, se retorna y guarda en la cache de RAM, si
    esta esta completa, se quitar ́a el menos usados (LRU) m ́as bajo 
    
    En el archivo no debe guardarse el MRU ya que este es v ́alido para la cache
    de RAM. Ejemplo de lo que se ha dicho anteriormente. Si al buscar la clave, no
    esta en RAM, pero se encuentra en el archivo, este Obj se incorpora a la cache
    RAM y el MRU se setear ́a con el valor mas alto, o sea, si el MRU existente es
    10, el nuevo par incresar ́a con MRU 11.
    */

}