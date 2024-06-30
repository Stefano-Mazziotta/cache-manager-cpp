#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager
{
private:
    int capacity;
    map<string, pair<T, string>> cache_data; // (id, (object, MRU))
    bool write_file(string, T);

public:
    CacheManager(int); // recibe la capacidad en el int
    ~CacheManager();

    void insert(string id, T object);
    T get(string id);
    void show_cache();
};

template <class T>
CacheManager<T>::CacheManager(int capacity)
{
    this->capacity = capacity;

    // get class name T and create a file with this name
    std::ofstream file(T::class_name + ".txt");
}

template <class T>
CacheManager<T>::~CacheManager() {}

template <class T>
bool CacheManager<T>::write_file(std::string id, T object)
{
    // write object into file
}

template <class T>
void CacheManager<T>::insert(std::string id, T object)
{
    // Cada llamada a insert(),

    // La inserción del T Object se realizará en la cache y en el archivo.

    // Si ya existía la clave, actualiza el Object. (en cache y en el archivo)
    // De lo contrario, escribirá el objeto en el sistema de archivos y la caché
    // Se actualizará el MRU del Object para que sea el mayor.

    // Check if the id already exists in the cache
    if (cache_data.find(id) != cache_data.end())
    {
        cache_data[id].first = object; // Id already exists, update the object
    }
    else
    {
        // id does not exist, insert the object into the cache
        cache_data[id] = std::make_pair(object, ""); // verify MRU
    }

    write_file(id, object);
}

template <class T>
T CacheManager<T>::get(std::string id)
{
    /**
    Al realizar un get(), si no se encuentra en la cache en RAM se lo buscará en
    el archivo. Si se lo encuentra, se retorna y guarda en la cache de RAM, si
    esta está completa, se quitará el menos usado (LRU) más bajo.

    En el archivo no debe guardarse el MRU ya que este es válido para la cache
    de RAM. Ejemplo de lo que se ha dicho anteriormente. Si al buscar la clave, no
    está en RAM, pero se encuentra en el archivo, este Object se incorpora a la cache
    RAM y el MRU se seteará con el valor más alto, o sea, si el MRU existente es
    10, el nuevo par incrementará con MRU 11.
    */

    // Check if the id exists in the cache
    if (cache_data.find(id) != cache_data.end())
    {
        // id found in cache, return the value
        return cache_data[id].first;
    }

    // id not found in cache, search in the file
    std::ifstream file("cache.txt");
    std::string line;
    while (std::getline(file, line))
    {
        // Parse the line to extract the id and value
        std::istringstream iss(line);
        std::string fileKey;
        T fileValue;
        if (iss >> fileKey >> fileValue)
        {
            // Check if the id matches
            if (fileKey == id)
            {
                // Id found in the file, add it to the cache
                cache_data[id] = std::make_pair(fileValue, "");
                file.close();
                return fileValue;
            }
        }
    }
    file.close();

    // If the id is found in the file, add it to the cache
    // TODO: Add the id-objet pair to the cache
    // Add the id-value pair to the cache
    cache_data[id] = std::make_pair(object, "MRU");

    // Implement LRU eviction logic if the cache is full
    if (cache_data.size() > capacity)
    {
        // Find the least recently used id
        auto it = cache_data.begin();
        for (auto i = cache_data.begin(); i != cache_data.end(); i++)
        {
            if (i->second.second < it->second.second)
            {
                it = i;
            }
        }
        // Remove the least recently used id from the cache
        cache_data.erase(it);
    }

    // TODO: Implement LRU eviction logic if the cache is full
    // Implement LRU eviction logic if the cache is full
    if (cache_data.size() > capacity)
    {
        // Find the least recently used id
        auto it = cache_data.begin();
        for (auto i = cache_data.begin(); i != cache_data.end(); i++)
        {
            if (i->second.second < it->second.second)
            {
                it = i;
            }
        }
        // Remove the least recently used id from the cache
        cache_data.erase(it);
    }

    // Return the value associated with the id
    return cache_data[id].first;
}

template <class T>
void CacheManager<T>::show_cache()
{
    // Muestra el contenido de la cache
    for (auto i = cache_data.begin(); i != cache_data.end(); i++)
    {
        std::cout << "Id: " << i->first << ", Value: (Student: " << i->second.first.name() << ", Info: " << i->second.second << ")" << std::endl;
    }
}