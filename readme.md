# University project

Se implementará un Manejador de cache generico. El sistema guardará un pair compuesto por clave y valor, ambos en RAM y en disco (files).

Dada una clave, el cache manager accede al valor. Si el valor existe en la memoria es retornado. En caso que no exista en memoria, entonces el cache deberá buscar la clave en el archivo y retornar el pair si es encontrado.

El cache también debe implementar un tamaño límite de capacidad, lo que significa una restricción sobre cuántos elementos pueden existir a la vez en la memoria.

Una vez que se ha alcanzado el límite, el menos utilizado recientemente (LRU) debe eliminarse de la memoria para ingresar al nuevo. En el momento de la inserción, todo nuevo par <key, valor> debe guardarse tanto en la memoria como en el archivo.

## Especificaciones

### 1.1. Class CacheManager

Las funciones públicas que deben existir en su clase son:

- `void insert(string key, T Obj)`: Si existe, actualizará al objeto tanto en cache como en el archivo. De lo contrario, escribirá el objeto en el sistema de archivos y la caché. Se actualizará el MRU del Obj para que sea el mayor.

- `T get(string key)`: Si el objeto existe, sea en la caché o en el archivo, lo retorna y actualiza el MRU. Si la clave no existe tanto en el sistema principal como en el sistema de archivos, el programa debe informarlo.

- `CacheManager(string capacity)`: Debe inicializar la capacidad de la caché. IMPORTANTE: cualquier llamada que utiliza una clave (insertar u obtener) actualizará el par <clave, <obj, valor>> para ser el Mayor Recientemente Usado.

La clave (key) siempre será un string. El Obj debe ser un objeto de tipo T creado en el main y pasado a las funciones. Se detallarán más adelante las especificaciones de dicho objeto. El constructor solo debe aceptar la capacidad del cache. Puede y debe agregar toda función que crea necesaria para el funcionamiento y la operatividad de la caché sea en RAM o en el archivo.

### 1.2. T Object

El tipo T debe ser un tipo de una clase que se implemente en el main. En los archivos adjuntos está el ejemplo de main. Se deberá tener en cuenta:

- Los miembros deben ser tipos primitivos (string, int, float, double, etc.). No deben usarse datos complejos ni punteros.
- Cada clase que se implemente debe tener un static con el nombre de la clase. Debe ser inicializado en el main.
- Por cada clase que se implemente debe tenerse una función `print()` o la respectiva sobrecarga del operador.
- No hay límites de los datos miembros de las clases.

### 1.3. Files

Cada llamada a `insert()`, la inserción del T Obj se realizará en la caché y en el archivo. Si ya existía la clave, actualiza el Obj.

Los nombres de los archivos serán arbitrarios y los podrán elegir según deseen.

Al realizar un `get()`, si no se encuentra en la caché en RAM se lo buscará en el archivo. Si se lo encuentra, se retorna y guarda en la caché de RAM. Si esta está completa, se quitará el menos usado (LRU) más bajo.

En el archivo no debe guardarse el MRU ya que este es válido para la caché de RAM. Ejemplo de lo que se ha dicho anteriormente: si al buscar la clave, no está en RAM, pero se encuentra en el archivo, este Obj se incorpora a la caché RAM y el MRU se seteará con el valor más alto, es decir, si el MRU existente es 10, el nuevo par incrementará con MRU 11.
