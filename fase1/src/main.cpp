#include <iostream>

using namespace std;

int main()
{
    // mostrar menu
    while (true)
    {
        cout << "========= SOCIAL ESTRUCTURE =========" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. informacion" << endl;
        cout << "4. Salir" << endl;

        int opcion;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Iniciar sesion" << endl;
            break;
        case 2:
            cout << "Registrarse" << endl;
            break;
        case 3:
            cout << "Informacion" << endl;
            break;
        case 4:
            cout << "Salir" << endl;
            return 0;
        default:
            cout << "Opcion no valida" << endl;
        }
    }
}