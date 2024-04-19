#include <iostream>
#include <stdio.h>
#include <math.h>
#include "include/strings.hpp" // Librería de manipulación de cadenas
#include "include/tokens.hpp" // Librería para manejar tokens
#include "include/coll.hpp" // Librería para funciones de colección

using namespace std;

struct BigInt
{
    string s; // Cadena que representa un número grande
};

BigInt bigInt(string s) // Función para crear un BigInt a partir de una cadena
{
    BigInt b;
    b.s = s;
    return b;
}

string minuendoComplemento(string a) // Función para calcular el complemento a 10 de un número en formato de cadena
{
    char sep = '|';
    string c = emptyTString(length(a) - 2, sep); // Genera una cadena de separadores '|'
    int i = length(a) - 1;
    while (a[i] == '0') // Encuentra el primer dígito diferente de cero desde el final
    {
        setTokenAt(c, sep, "0", i - 1); // Establece los dígitos del complemento a 10
        i--;
    }
    setTokenAt(c, sep, "10", i - 1); // Establece el primer dígito no cero del complemento
    i--;
    while (i > 0) // Completa el complemento con 9s
    {
        setTokenAt(c, sep, "9", i - 1);
        i--;
    }
    return c;
}

BigInt complementoBigInt(BigInt a) // Función para calcular el complemento a 10 de un BigInt
{
    BigInt l;
    string m = minuendoComplemento(a.s), c;
    int i = 0, p;
    while (i < length(a.s) - 1)
    {
        p = stringToInt(getTokenAt(m, '|', i)) - charToInt(a.s[i + 1]); // Resta los dígitos
        c += intToString(p); // Concatena los dígitos al complemento
        i++;
    }
    l = bigInt(c); // Crea un BigInt a partir del complemento
    return l;
}

int signosOperacion(BigInt a, BigInt b) // Función para determinar el tipo de operación (suma, resta) basada en los signos
{
    if (a.s[0] == '-')
    {
        if (b.s[0] == '-')
        {
            return 1; // Ambos negativos (suma)
        }
        else
        {
            return 2; // a negativo, b positivo (resta)
        }
    }
    if (b.s[0] == '-')
    {
        return 3; // a positivo, b negativo (resta)
    }
    return 4; // Ambos positivos (suma)
}

void prepararBigInt(BigInt &a, BigInt &b) // Función para igualar la longitud de los BigInt antes de operar
{
    if (length(a.s) > length(b.s))
    {
        b.s = lpad(b.s, length(a.s), '0'); // Agrega ceros a la izquierda a b
    }
    if (length(a.s) < length(b.s))
    {
        a.s = lpad(a.s, length(b.s), '0'); // Agrega ceros a la izquierda a a
    }
}

BigInt sumaGenerica(BigInt a, BigInt b) // Función para sumar dos BigInt
{
    prepararBigInt(a, b); // Ajusta la longitud de los BigInt
    BigInt sum;
    sum.s = cpad(sum.s, length(a.s) + 1, '0'); // Inicializa la cadena de suma con ceros
    int c = 0, x = length(a.s) - 1, s;
    while (x >= 0) // Realiza la suma dígito por dígito
    {
        s = charToInt(a.s[x]) + charToInt(b.s[x]) + c; // Suma los dígitos y el acarreo
        c = getDigit(s, 1); // Obtiene el acarreo
        s = getDigit(s, 0); // Obtiene el dígito de la suma
        sum.s[x + 1] = intToChar(s); // Establece el dígito en la cadena de suma
        x--;
    }
    if (c > 0) // Si queda un acarreo al final, se agrega a la cadena de suma
    {
        sum.s[x + 1] = intToChar(c);
    }
    if (startsWith(sum.s, "0")) // Elimina los ceros no significativos al principio
    {
        sum.s = removeAt(sum.s, 0);
    }
    return sum;
}

BigInt restarComplemento(BigInt sum, int p) // Función para restar el complemento a 10
{
    int i = length(sum.s) - 1;
    BigInt empty = bigInt("");
    empty.s = cpad(empty.s, length(sum.s), '0'); // Inicializa una cadena vacía con ceros
    BigInt aRestar = bigInt("1"); // Representación del número 1 como BigInt
    aRestar.s = rpad(aRestar.s, p, '0'); // Agrega ceros al final del número 1
    prepararBigInt(empty, aRestar); // Iguala la longitud de los BigInt
    while (aRestar.s[i] == '0') // Copia los dígitos de la suma original a la resta
    {
        empty.s[i] = sum.s[i];
        i--;
    }
    if (sum.s[i] != '0') // Si el dígito es distinto de cero, se resta uno y se copian los demás dígitos
    {
        empty.s[i] = intToChar(charToInt(sum.s[i]) - 1);
        i--;
        while (i >= 0)
        {
            empty.s[i] = sum.s[i];
            i--;
        }
    }
    if (sum.s[i] == '0') // Si el dígito es cero, se realiza la resta con el complemento a 10
    {
        empty.s[i] = intToChar(charToInt(sum.s[i]) + 10 - charToInt(aRestar.s[i]));
        i--;
        while (i >= 0)
        {
            if (sum.s[i + 1] == '0') // Si hay un acarreo, se ajustan los dígitos
            {
                if (sum.s[i] != '0')
                {
                    empty.s[i] = intToChar(charToInt(sum.s[i]) - 1);
                }
                else
                {
                    empty.s[i] = intToChar(9);
                }
            }
            else
            {
                empty.s[i] = intToChar(charToInt(sum.s[i]));
            }
            i--;
        }
    }
    return empty;
}

void invertirSignos(BigInt &a, BigInt &b) // Función para invertir los signos de a y b
{
    a = bigInt(removeAt(a.s, 0)); // Elimina el signo negativo de a
    b = bigInt(lpad(b.s, length(b.s) + 1, '-')); // Agrega un signo negativo a b
}

void permutarBigInt(BigInt &a, BigInt &b) // Función para intercambiar a y b
{
    BigInt aux = a;
    a = b;
    b = aux;
}

int cmpBigInt(BigInt a, BigInt b) // Función para comparar dos BigInt
{
    if (startsWith(a.s, "-")) // Si a es negativo, elimina el signo
    {
        a.s = removeAt(a.s, 0);
    }
    if (startsWith(b.s, "-")) // Si b es negativo, elimina el signo
    {
        b.s = removeAt(b.s, 0);
    }
    prepararBigInt(a, b); // Iguala la longitud de los BigInt
    return cmpString(a.s, b.s); // Compara las cadenas de los BigInt
}

void prepararDatosIn(BigInt &a, BigInt &b, int sig, int &sob, bool &inverso) // Función para preparar los datos antes de realizar operaciones
{
    BigInt auxA = a;
    BigInt auxB = b;

    if (sig == 1) // Ambos negativos (suma)
    {
        a.s = removeAt(a.s, 0);
        b.s = removeAt(b.s, 0);
    }
    if (sig == 2) // a negativo, b positivo (resta)
    {
        if (cmpBigInt(auxA, auxB) <= 0) // Si a es menor o igual que b en magnitud
        {
            permutarBigInt(a, b); // Intercambia a y b
            b = complementoBigInt(b); // Calcula el complemento a 10 de b
            sob = length(b.s) + 1; // Calcula la longitud del complemento
            inverso = false; // Indica que no se debe invertir el resultado al final
        }
        if (cmpBigInt(auxA, auxB) > 0) // Si a es mayor que b en magnitud
        {
            invertirSignos(a, b); // Invierte los signos de a y b
            b = complementoBigInt(b); // Calcula el complemento a 10 de b
            sob = length(b.s) + 1; // Calcula la longitud del complemento
            inverso = true; // Indica que se debe invertir el resultado al final
        }
    }
    if (sig == 3) // a positivo, b negativo (resta)
    {
        if (cmpBigInt(auxA, auxB) < 0) // Si a es menor que b en magnitud
        {
            permutarBigInt(a, b); // Intercambia a y b
            invertirSignos(a, b); // Invierte los signos de a y b
            b = complementoBigInt(b); // Calcula el complemento a 10 de b
            sob = length(b.s) + 1; // Calcula la longitud del complemento
            inverso = true; // Indica que se debe invertir el resultado al final
        }
        if (cmpBigInt(auxA, auxB) >= 0) // Si a es mayor o igual que b en magnitud
        {
            b = complementoBigInt(b); // Calcula el complemento a 10 de b
            sob = length(b.s) + 1; // Calcula la longitud del complemento
            inverso = false; // Indica que no se debe invertir el resultado al final
        }
    }
}

void limpiarBigInt(BigInt &a) // Función para eliminar ceros no significativos al principio de un BigInt
{
    while (a.s[0] == '0') // Mientras el primer dígito sea cero
    {
        a.s = removeAt(a.s, 0); // Elimina el cero
    }
    if (isEmpty(a.s)) // Si la cadena está vacía
    {
        a.s = "0"; // Asigna "0" al BigInt
    }
}

void prepararDatosOut(BigInt &suma, int sig, int sob, bool inverso) // Función para preparar los datos después de realizar operaciones
{
    if (sig == 1) // Ambos negativos (suma)
    {
        limpiarBigInt(suma); // Elimina ceros no significativos
        suma.s = lpad(suma.s, length(suma.s) + 1, '-'); // Agrega un signo negativo al resultado
    }
    if (sig == 2 || sig == 3) // a negativo, b positivo o a positivo, b negativo (resta)
    {
        if (inverso) // Si se invirtió el resultado
        {
            suma = restarComplemento(suma, sob); // Resta el complemento a 10 del resultado
            limpiarBigInt(suma); // Elimina ceros no significativos
            suma.s = lpad(suma.s, length(suma.s) + 1, '-'); // Agrega un signo negativo al resultado
        }
        else // Si no se invirtió el resultado
        {
            suma = restarComplemento(suma, sob); // Resta el complemento a 10 del resultado
            limpiarBigInt(suma); // Elimina ceros no significativos
        }
    }
    if (sig == 4) // Ambos positivos (suma)
    {
        limpiarBigInt(suma); // Elimina ceros no significativos
    }
}

int siAlgunoEsCero(BigInt a, BigInt b) // Función para verificar si alguno de los BigInt es cero
{
    if (a.s == "0") // Si a es cero
    {
        return 0; // Devuelve 0
    }
    if (b.s == "0") // Si b es cero
    {
        return 1; // Devuelve 1
    }
    return -1; // Si ninguno es cero, devuelve -1
}

BigInt bigIntSumar(BigInt a, BigInt b) // Función para sumar dos BigInt
{
    BigInt suma;
    int sig = signosOperacion(a, b), sob;
    bool inverso;

    if (siAlgunoEsCero(a, b) == 0 || siAlgunoEsCero(a, b) == 1) // Si alguno de los BigInt es cero
    {
        if (siAlgunoEsCero(a, b) == 0) // Si a es cero
        {
            return b; // Devuelve b
        }
        else // Si b es cero
        {
            return a; // Devuelve a
        }
    }

    prepararDatosIn(a, b, sig, sob, inverso); // Prepara los datos para la operación
    suma = sumaGenerica(a, b); // Realiza la operación de suma
    prepararDatosOut(suma, sig, sob, inverso); // Prepara los datos del resultado

    return suma; // Devuelve la suma
}

string bigIntToString(BigInt a) // Función para convertir un BigInt en una cadena
{
    return a.s; // Devuelve la cadena del BigInt
}

string eliminarCerosNoSignificativos(const string& str) // Función para eliminar ceros no significativos al principio de una cadena
{
    size_t firstNonZero = str.find_first_not_of('0'); // Encuentra la posición del primer dígito diferente de cero
    if (firstNonZero == string::npos) // Si todos los dígitos son cero
    {
        return "0"; // Devuelve "0"
    }
    else // Si hay dígitos diferentes de cero
    {
        return str.substr(firstNonZero); // Devuelve la cadena sin ceros no significativos al principio
    }
}

BigInt bigIntRestar(BigInt a, BigInt b) // Función para restar dos BigInt
{
    if (a.s == "-" + b.s) // Si a y b son iguales en magnitud pero con diferente signo
    {
        return bigInt("0"); // Devuelve 0
    }

    bool resultadoNegativo = false; // Variable para indicar si el resultado es negativo
    if (a.s[0] == '-' && b.s[0] != '-') // Si a es negativo y b no
    {
        resultadoNegativo = true; // El resultado es negativo
        a.s = a.s.substr(1); // Elimina el signo negativo de a
    }
    else if (a.s[0] != '-' && b.s[0] == '-') // Si a es positivo y b negativo
    {
        resultadoNegativo = false; // El resultado es positivo
        b.s = b.s.substr(1); // Elimina el signo negativo de b
    }
    else if (a.s[0] == '-' && b.s[0] == '-') // Si ambos son negativos
    {
        b.s = b.s.substr(1); // Elimina el signo negativo de b
        return bigIntSumar(a, b); // Restar (-b) es equivalente a sumar b
    }

    if (cmpBigInt(a, b) < 0) // Si b es mayor que a en magnitud
    {
        resultadoNegativo = !resultadoNegativo; // El resultado es negativo
        permutarBigInt(a, b); // Intercambia a y b
    }

    BigInt resta;
    int maxLength = max(a.s.size(), b.s.size()); // Determina la longitud máxima entre a y b
    a.s = lpad(a.s, maxLength, '0'); // Agrega ceros a la izquierda a a
    b.s = lpad(b.s, maxLength, '0'); // Agrega ceros a la izquierda a b
    int carry = 0;

    for (int i = maxLength - 1; i >= 0; --i) // Realiza la resta dígito por dígito
    {
        int digitoA = a.s[i] - '0';
        int digitoB = b.s[i] - '0';
        int resultado = digitoA - digitoB - carry;

        if (resultado < 0) // Si el resultado es negativo
        {
            resultado += 10; // Suma 10 para corregir la resta
            carry = 1; // Establece el acarreo
        }
        else
        {
            carry = 0; // No hay acarreo
        }

        resta.s = char(resultado + '0') + resta.s; // Agrega el dígito al resultado
    }

    resta.s = eliminarCerosNoSignificativos(resta.s); // Elimina los ceros no significativos al principio del resultado

    if (resultadoNegativo) // Si el resultado es negativo
    {
        resta.s = "-" + resta.s; // Agrega el signo negativo al resultado
    }

    return resta; // Devuelve el resultado
}

BigInt bigIntFromString(string s) // Función para crear un BigInt a partir de una cadena
{
    BigInt a = bigInt(s); // Crea un BigInt a partir de la cadena
    return a; // Devuelve el BigInt
}

BigInt bigIntMultiplicar(BigInt a, BigInt b) // Función para multiplicar dos BigInt
{ 
    BigInt res = a; // Inicializa el resultado con a
    for(int i=1; intToString(i) != bigIntToString(b); i++){ // Realiza la multiplicación iterativa
        res = bigIntSumar(res,a); // Suma a al resultado
    }
    return res; // Devuelve el resultado
}
