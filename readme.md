# Cache Manager in C++
## University project

Cache management using object oriented programming in c++.
- Use map and pair structures as data representations to save in RAM and files
- Key algorithms to get values from cache
- Logic to insert and retrieve data from multiple cache or file structures
- Limit cache capacity
- Implementing the cache using Most Recently Used (MRU) and Least Recently Used (LRU) algorithms


# 1. Specifications
## 1.1. Class CacheManager

Public functions required in your class:

- `void insert(string key, T Obj)`: If the key exists, update the object in both cache and file. Otherwise, write the object to the filesystem and cache. Update the object's MRU to be the highest.

- `T get(string key)`: If the object exists in either cache or file, return it and update the MRU. If the key does not exist in both primary system and filesystem, notify the program.

- `CacheManager(string capacity)`: Initialize the cache capacity. 

> [!IMPORTANT]
> - Any call using a key (insert or get) will update the key-value pair to be the Most Recently Used (MRU).
> - The object Obj must be of type T created in the main and passed to the functions. 
> - The constructor should only accept the cache capacity. 


## 1.2. T Object

- Each implemented class should have a static member called `class_name`, initialized in the main.
- Each class should have a `print()` function or an appropriate operator overload.
- No limit on the number of member data in the classes.

## 1.3. Files
- Each call `to insert()`, the insertion of T Obj will be performed in both cache and file. 
    - If the key already exists, update the Obj.

- File names will be created as `class_name.txt`
- When performing a get(): 
    - If the object is not found in the RAM cache it will be searched for in the file.  
    - If found, it is returned and stored in the RAM cache. 
    - If the cache is full, the least recently used (LRU) object will be removed.

- The MRU should not be stored in the file as it is only valid for the RAM cache. 

> [!Tip]
> Example: if the key is not in RAM but found in the file, the object is incorporated into the RAM cache, and the MRU is set to the highest value. If the existing MRU is 10, the new pair will increment to MRU 11.


# 2. How to run?
1. Compile:
```
compile g++ -Wall -std=c++11 main.cpp -o main
```
2. Execute `./main` in terminal.