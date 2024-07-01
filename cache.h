#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager
{
private:
    size_t capacity;
    map<string, pair<T, int>> cache_data; // (id, (object, MRU))
    bool write_file(string, T);
    int get_maximum_MRU();
    bool exists_in_cache(string key);

public:
    CacheManager(int); // recibe la capacidad en el int
    ~CacheManager();

    void insert(string id, T object);
    // T get(string id);
    int get(string id);
    void show_cache();
};

template <class T>
CacheManager<T>::CacheManager(int capacity)
{
    this->capacity = capacity;

    // get class name T and create a file with this name
    fstream file(T::class_name + ".txt");
}

template <class T>
CacheManager<T>::~CacheManager() {}

template <class T>
bool CacheManager<T>::write_file(string key, T object)
{
    string filename = T::class_name + ".txt";
    string temp_filename = filename + ".tmp";

    ifstream input_file(filename);
    ofstream temp_file(temp_filename);

    bool key_exists = false;
    bool write_success = false;

    if (!input_file || !temp_file)
    {
        cerr << "Error opening file." << endl;
        return false;
    }

    string line;
    while (getline(input_file, line))
    {
        istringstream iss(line);
        string file_key;
        T file_value;
        if (iss >> file_key)
        {
            if (file_key == key)
            {
                // Key matches, write updated object instead
                temp_file << key << " " << object << endl;
                key_exists = true;
                write_success = true;
            }
            else
            {
                // Write the original line to temp file
                temp_file << line << endl;
            }
        }
    }

    if (!key_exists)
    {
        // Key does not exist, append it to the temp file
        temp_file << key << " " << object << endl;
        write_success = true;
    }

    input_file.close();
    temp_file.close();

    if (write_success)
    {
        // Replace the original file with the updated temp file
        remove(filename.c_str());
        rename(temp_filename.c_str(), filename.c_str());
    }
    else
    {
        // Cleanup temp file if write was not successful
        remove(temp_filename.c_str());
    }

    return write_success;
}

template <class T>
bool CacheManager<T>::exists_in_cache(string key)
{
    // Check if the key already exists in the cache
    bool exists = cache_data.find(key) != cache_data.end();
    return exists;
}

template <class T>
int CacheManager<T>::get_maximum_MRU()
{
    // find the maximum MRU
    int maximum_MRU = 0;
    for (const auto &pair : cache_data)
    {
        if (pair.second.second > maximum_MRU)
        {
            maximum_MRU = pair.second.second;
        }
    }

    return maximum_MRU;
}

template <class T>
void CacheManager<T>::insert(string key, T object)
{
    // Check if the key already exists in the cache
    if (this->exists_in_cache(key))
    {
        cache_data[key].first = object;

        int previous_MRU = cache_data[key].second;
        cache_data[key].second = previous_MRU + 1;

        write_file(key, object);
        return;
    }

    // key doesn't exist

    // if the cache is full, remove the least recently used object
    if (cache_data.size() >= capacity)
    {
        // Find the least recently used object
        auto it = cache_data.begin();
        for (auto iterator = cache_data.begin(); iterator != cache_data.end(); iterator++)
        {
            if (iterator->second.second < it->second.second)
            {
                it = iterator;
            }
        }
        // Remove the least recently used object from the cache
        cache_data.erase(it);
    }

    int maximum_MRU = get_maximum_MRU() + 1;
    cache_data.emplace(key, make_pair(move(object), maximum_MRU)); // insert to cache

    write_file(key, object);
}

template <class T>
int CacheManager<T>::get(string key)
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
    // if (cache_data.find(id) != cache_data.end())
    // {
    //     // id found in cache, return the value
    //     return cache_data[id].first;
    // }

    // id not found in cache, search in the file
    // ifstream file("cache.txt");
    // string line;
    // while (std::getline(file, line))
    // {
    //     // Parse the line to extract the id and value
    //     istringstream iss(line);
    //     string fileKey;
    //     T fileValue;
    //     if (iss >> fileKey >> fileValue)
    //     {
    //         // Check if the id matches
    //         if (fileKey == id)
    //         {
    //             // Id found in the file, add it to the cache
    //             cache_data[id] = make_pair(fileValue, "");
    //             file.close();
    //             return fileValue;
    //         }
    //     }
    // }
    // file.close();

    // // If the id is found in the file, add it to the cache
    // // TODO: Add the id-objet pair to the cache
    // // Add the id-value pair to the cache
    // cache_data[id] = std::make_pair(object, "MRU");

    // // Implement LRU eviction logic if the cache is full
    // if (cache_data.size() > capacity)
    // {
    //     // Find the least recently used id
    //     auto it = cache_data.begin();
    //     for (auto i = cache_data.begin(); i != cache_data.end(); i++)
    //     {
    //         if (i->second.second < it->second.second)
    //         {
    //             it = i;
    //         }
    //     }
    //     // Remove the least recently used id from the cache
    //     cache_data.erase(it);
    // }

    // // TODO: Implement LRU eviction logic if the cache is full
    // // Implement LRU eviction logic if the cache is full
    // if (cache_data.size() > capacity)
    // {
    //     // Find the least recently used id
    //     auto it = cache_data.begin();
    //     for (auto i = cache_data.begin(); i != cache_data.end(); i++)
    //     {
    //         if (i->second.second < it->second.second)
    //         {
    //             it = i;
    //         }
    //     }
    //     // Remove the least recently used id from the cache
    //     cache_data.erase(it);
    // }

    // // Return the value associated with the id
    // return cache_data[id].first;
    return 0;
}

template <class T>
void CacheManager<T>::show_cache()
{
    // Muestra el contenido de la cache
    for (auto map_data = cache_data.begin(); map_data != cache_data.end(); map_data++)
    {
        std::cout << "Key: " << map_data->first << ", Value: (Object: " << map_data->second.first.print() << ", MRU: " << map_data->second.second << ")" << std::endl;
    }
}