# TAD BigInt

El TAD BigInt es una implementación de enteros de tamaño arbitrario que desarrollé junto a [@msantucho1](https://github.com/msantucho1) en Mayo de 2023. Este proyecto surgió como un desafío personal cuando aún estábamos explorando los fundamentos de la programación estructurada.

## Funciones Principales

El código proporciona las siguientes funciones principales:

- `BigInt bigInt(string s)` : Función para crear un BigInt a partir de una cadena.
- `BigInt complementoBigInt(BigInt a)` : Función para calcular el complemento a 10 de un BigInt.
- `BigInt bigIntSumar(BigInt a, BigInt b)` : Función para sumar dos BigInt.
- `BigInt bigIntRestar(BigInt a, BigInt b)` : Función para restar dos BigInt.
- `BigInt bigIntMultiplicar(BigInt a, BigInt b)` : Función para multiplicar dos BigInt.
- `int cmpBigInt(BigInt a, BigInt b)` : Funcion para comprar dos BigInt

Además de estas funciones principales, el código también incluye funciones auxiliares para manipular cadenas y realizar operaciones matemáticas específicas en BigInts.

## Uso

Para usar el TAD BigInt, simplemente incluye el archivo `BigInt.cpp` en tu proyecto de C++ y utiliza las funciones proporcionadas según sea necesario.

```cpp
#include "BigInt.cpp"

int main() {
    BigInt a = bigInt("12345678901234567890");
    BigInt b = bigInt("-98765432109876543210");
    
    BigInt suma = bigIntSumar(a, b);
    BigInt resta = bigIntRestar(a, b);
    BigInt producto = bigIntMultiplicar(a, b);

    return 0;
}

```

## Acerca de la implementación

Para implementar este TAD, aprovechamos las bibliotecas de funciones que desarrollamos durante nuestro estudio de la materia de "Algoritmos y Estructuras de Datos". Estas bibliotecas están disponibles en mi repositorio de GitHub.

## Limitaciones conocidas

- Tiempos de procesamiento prolongados para operaciones como la multiplicación de números grandes.

> Las limitaciones que tiene el programa no serán corregidas ya que la idea no es mejorar este código, si no conservarlo como el logro que fué en aquel momento


