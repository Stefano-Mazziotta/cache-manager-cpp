#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <map>
#include <utility>
#include <string>
#include <cstring>

using namespace std;

template <class T>
class CacheManager
{
private:
    size_t capacity;
    map<string, pair<T, int>> cache_data; // (key, (object, MRU))
    bool write_file(string, T);
    int get_maximum_MRU();
    bool exists_in_cache(string key);
    void remove_least_recently_used();

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
    string filename = T::class_name + ".txt";
    fstream file(filename);
    file.open(filename, std::ios_base::app);
    file.close();
}

template <class T>
CacheManager<T>::~CacheManager() {}

template <class T>
void CacheManager<T>::remove_least_recently_used()
{
    // Find the least recently used object
    auto it = cache_data.begin();
    for (auto i = cache_data.begin(); i != cache_data.end(); i++)
    {
        if (i->second.second < it->second.second)
        {
            it = i;
        }
    }

    // Remove the least recently used object from the cache
    cache_data.erase(it);
}

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
    if (cache_data.size() >= capacity)
    {
        this->remove_least_recently_used();
    }

    int maximum_MRU = get_maximum_MRU() + 1;

    // insert to cache
    cache_data.emplace(key, make_pair(move(object), maximum_MRU));

    write_file(key, object);
}

template <class T>
T CacheManager<T>::get(string key)
{
    // Check if the key exists in the cache
    if (cache_data.find(key) != cache_data.end())
    {
        // key found in cache, return the value
        return cache_data[key].first;
    }

    // key not found in cache, search in the file
    ifstream file(T::class_name + ".txt");
    string line;
    while (std::getline(file, line))
    {
        istringstream iss(line);
        string file_key;
        T file_value;
        if (iss >> file_key >> file_value)
        {
            // Check if the key matches
            if (file_key == key)
            {
                if (cache_data.size() > capacity)
                {
                    this->remove_least_recently_used();
                }

                // key found in the file, add it to the cache
                int maximum_MRU = get_maximum_MRU() + 1;
                cache_data[key] = make_pair(file_value, maximum_MRU);
                file.close();
                return file_value;
            }
        }
    }
    file.close();

    // Return the value associated with the id
    return cache_data[key].first;
}

template <class T>
void CacheManager<T>::show_cache()
{
    // Muestra el contenido de la cache
    for (auto map_data = cache_data.begin(); map_data != cache_data.end(); map_data++)
    {
        cout << "Key: " << map_data->first << ", Value: (Object: ";
        map_data->second.first.print(); // Call print separately
        cout << ", MRU: " << map_data->second.second << ")" << std::endl;
    }
}