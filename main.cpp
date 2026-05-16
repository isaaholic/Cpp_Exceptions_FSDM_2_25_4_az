#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>

using namespace std;

// Exception - proqram yazilan zaman ve ya program icrasi zamani yaranan xeta zamani programin cokme halina deyilir.

// Exception handling - tullanilan exceptionlarin tutulmasi ve oz kod strukturumuza uygun idare ve yeniden istifade edilmesidir

// try
// throw
// catch

class ZeroDivisionException : public exception
{
private:
    string _message;
    string _source;
    string _time;
    int _line;

public:
    ZeroDivisionException(const char *message = "Zero Division Exception",
                          const char *source = "",
                          const char *time = "",
                          const int line = 0) noexcept : exception()
    {
        _source = source;
        _time = time;
        _line = line;

        _message = "\033[31mMessage:  " + string("Zero Division Error") + "\nSource:   " + _source + "\nTime:     " + _time + "\nLine:     " + to_string(_line) + "\033[0m";
    }

    virtual const char *what() const noexcept override
    {
        return _message.c_str();
    }
};

// int divide(int a, int b) throw(ZeroDivisionException)
// {
//     if (b == 0)
//     {
//         throw ZeroDivisionException("Cannot divide by zero", __FILE__, __TIME__, __LINE__);
//     }
//     return a / b;
// }

// int main()
// {
//     try
//     {
//         /* code */
//         // throw (unsigned int) 10;
//         // throw string("Salam");
//         int a = 10;
//         int b = 0;
//         cout << divide(a, b) << endl;
//     }
//     catch (const ZeroDivisionException &ex)
//     {
//         cout << ex.what() << endl;
//     }
//     catch (unsigned int)
//     {
//         cout << "Unsigned integer exception caught" << endl;
//     }
//     catch (string)
//     {
//         cout << "String exception caught (C++-style)" << endl;
//     }
//     catch (const char *)
//     {
//         cout << "String exception caught (C-style)" << endl;
//     }
//     catch (int)
//     {
//         cout << "Integer exception caught" << endl;
//     }

//     return 0;
// }

// throw()
// throw(exception_type_name)
// noexcept

// rethrow
// inner exception

//// Standard Exceptions

/*
Standart Exceptions — iyerarxiya və qısa izahlar

- std::exception
    Baz (base) sinif: bütün standart istisnalar bu sinfdən birbaşa və ya dolayı olaraq törəyir.

- std::logic_error : public std::exception
    Proqramçının məntiqi səhvləri (compile zamanı yox, dizayn/argument səhvləri).
    - std::domain_error      : funksiya üçün qəbul olunmayan domen/dəyər
    - std::invalid_argument  : funksiyaya yanlış arqument verilib
    - std::length_error      : konteynerin yeni ölçüsü mümkün deyil (məs. çox uzun)
    - std::out_of_range      : indeks və ya aralıqdan kənar müraciət

- std::runtime_error : public std::exception
    İcra zamanı ortaya çıxan səhvlər (runtime). Adətən sistem/resurs problemləri.
    - std::range_error       : sayısal hesablamalarda aralıq problemi
    - std::overflow_error    : arifmetik overflow (taşma)
    - std::underflow_error   : arifmetik underflow

- Məxsusi və digər əlaqəli siniflər:
    - std::bad_alloc         : yaddaş ayırma (new) uğursuz olduqda atılır
    - std::bad_cast          : dynamic_cast uğursuz olduqda (RTTI ilə bağlı)
    - std::bad_typeid        : typeid ilə bağlı səhv
    - std::ios_base::failure : i/o axın xətaları (fayl, stream problemləri)
    - std::system_error      : sistem səviyyəli xətalar (errno, platform spesifik)
    - std::future_error      : std::future/std::promise ilə bağlı xətalar

- Digər faydalı obyektlar:
    - std::exception_ptr     : istisna obyektini tutub sonra başqa yerdə yenidən atmaq üçün istifadə olunur

Qaydalar və tövsiyələr:
- İstisnaları `catch(const std::exception &e)` şəklində referansla tutmaq ümumidir.
- Konkret növü (`std::out_of_range`, `std::invalid_argument`) əvvəlcə tutmaq daha spesifik informasiya verir.
- `what()` metodundan istifadə edərək xətanın mətn təsvirini almaq olar.
- Öz istisna siniflərinizi yarada bilərsiniz (std::exception-dən törədərək), amma `what()`-ın qaytardığı `const char*`-ın ömrünə diqqət edin.
*/

// Stack Unwinding
// Stack (Last in First out)

class MyFile
{
public:
    MyFile(const string &filename)
    {
        cout << "Opening file: " << filename << endl;
        // Simulate file opening
    }

    ~MyFile()
    {
        cout << "Closing file" << endl;
        // Simulate file closing
    }
};

void foo()
{
    throw ZeroDivisionException("Runtime error in foo");
}

void boo()
{
    MyFile file("example.txt");
    foo();
}

void voo()
{
    boo();
}

// Stack
// 1. main
// 2. voo
// 3. boo - (MyFile yarandi)
// 4. foo
// Stack Unwinding
// 1. foo throws an exception
// 2. foo stackden cixir
// 3. boo stackden cixir, MyFile destruktoru ishe dushur ve file baglanir
// 4. voo stackden cixir
// 5. main catch edir

int main() 
{
    // Stack unwiding - exception atildigi andan main funksiyasina qeder olan funksiyalarin stackden cixarilmasidir.
    // RAII - Resource Acquisition Is Initialization - resursun azad edilmesi - stack unwinding prosesinde resurslarin avtomatik azad edilmesi
    try
    {
        voo();
    }
    catch (const exception &ex)
    {
        cout << "Exception caught in main: " << ex.what() << endl;
    }
    catch (...) // catch all - butun exceptionlari tutmaq ucun istifade olunur
    {
        cout << "Unknown exception caught in main" << endl;
    }

    return 0;
}