# Analizador Léxico

Analizador léxico para el lenguaje D programado en C, diseñado para la materia de 3º año de la carrera de  Ingeniería Informática de la Universidad de Santiago de Compostela. 

## Descripción
El analizador obtiene los lexemas del lenguaje D, algunos de los lexememas menos comunes no están contemplados en el analizador, como por ejemplo los número en octal o algunos símbolos especiales.

## Ejecución
Para la ejecución debes tener el compilador de C, gcc, instalado en tu sistema operativo. Posteriormente, debes ejecuar el siguiente comando en la terminal:

```make```

Esto compilará el programa y generará un ejecutable llamado ```Compilador_cmd```. Para ejecutarlo, debes ejecutar el siguiente comando:

```./Compilador_cmd```

## Opciones
Para cambiar el número de bytes en cada bloque del sistema de entrada, debes modificar la variable ```BLOCK_SIZE``` en el archivo ```inputSystem.h```. Por defecto, el tamaño de cada bloque es de 32 bytes.

Si quieres analiziar otro fichero distinto al regression.d, debes modificar la variable ```FILE_NAME``` en el archivo ```inputSystem.h``` y recompilar el programa. El fichero debe estar en la misma carpeta que el ejecutable.

## Analisis con Valgrind
Para analizar el programa con Valgrind, debes ejecutar el siguiente comando:

```valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./Compilador_cmd``` o ```valgrind -s ./Compilador_cmd```

La salida de Valgrind con respecto a la memoria del HEAP es la siguiente:

```==5484==
==5484== HEAP SUMMARY:
==5484==     in use at exit: 0 bytes in 0 blocks
==5484==   total heap usage: 26 allocs, 26 frees, 5,785 bytes allocated
==5484==
==5484== All heap blocks were freed -- no leaks are possible
==5484==
==5484== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Autor
* **David Pacios** - [davidpacios]
