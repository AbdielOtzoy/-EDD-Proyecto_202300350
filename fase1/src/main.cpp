#include <iostream>
#include <string>
#include "./headers/auth.h"

using namespace std;

int main()
{
    while (true)
    {
        // mostrar menu principal
        if (isLogged == false)
        {
            cout << "========= SOCIAL ESTRUCTURE =========" << endl;
            cout << "1. Iniciar sesion" << endl;
            cout << "2. Registrarse" << endl;
            cout << "3. informacion" << endl;
            cout << "4. Salir" << endl;
            cout << "=====================================" << endl;

            int opcion;
            cout << "Opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                cout << "Iniciar sesion" << endl;
                loginUser();
                break;
            case 2:
                cout << "Registrarse" << endl;
                registerUser();
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

        // mostrar menu de administrador
        if (isLogged == true && isAdmin == true)
        {
            cout << "========= ADMIN DASHBOARD =========" << endl;
            cout << "1. Cargar usuarios" << endl;
            cout << "2. Cargar relaciones" << endl;
            cout << "3. Cargar publicaciones" << endl;
            cout << "4. Gestionar usuarios" << endl;
            cout << "5. Reportes" << endl;
            cout << "6. Cerrar sesion" << endl;
            cout << "=====================================" << endl;

            int opcion;
            cout << "Opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                cout << "Cargar usuarios" << endl;
                break;
            case 2:
                cout << "Cargar relaciones" << endl;
                break;
            case 3:
                cout << "Cargar publicaciones" << endl;
                break;
            case 4:
                cout << "Gestionar usuarios" << endl;
                break;
            case 5:
                cout << "Reportes" << endl;
                break;
            case 6:
                cout << "Cerrar sesion" << endl;
                logoutUser();
                break;
            default:
                cout << "Opcion no valida" << endl;
            }
        }

        // mostrar menu de usuario logeado
        if (isLogged == true)
        {
            cout << "========= USER DASHBORAD =========" << endl;
            cout << "1. Perfil" << endl;
            cout << "2. Solicitudes" << endl;
            cout << "3. Publicaciones" << endl;
            cout << "4. Reportes" << endl;
            cout << "5. Cerrar sesion" << endl;
            cout << "=====================================" << endl;

            int opcion;
            cout << "Opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                cout << "Perfil" << endl;
                // mostrar opciones: ver perfil, eliminar perfil o volver
                int opcionPerfil;
                while (opcionPerfil != 3)
                {
                    cout << "1. Ver perfil" << endl;
                    cout << "2. Eliminar perfil" << endl;
                    cout << "3. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> opcionPerfil;

                    switch (opcionPerfil)
                    {
                    case 1:
                        cout << "Ver perfil" << endl;
                        break;
                    case 2:
                        cout << "Eliminar perfil" << endl;
                        break;
                    case 3:
                        cout << "Volver" << endl;
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                    }
                }
                break;
            case 2:
                cout << "Solicitudes" << endl;
                int opcionSolicitudes;
                // mostrar opciones: ver solicitudes, enviar solicitud o volver
                while (opcionSolicitudes != 3)
                {
                    cout << "1. Ver solicitudes" << endl;
                    cout << "2. Enviar solicitud" << endl;
                    cout << "3. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> opcionSolicitudes;

                    switch (opcionSolicitudes)
                    {
                    case 1:
                        cout << "Ver solicitudes" << endl;
                        break;
                    case 2:
                        cout << "Enviar solicitud" << endl;
                        break;
                    case 3:
                        cout << "Volver" << endl;
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                    }
                }
                break;
            case 3:
                cout << "Publicaciones" << endl;
                int opcionPublicaciones;
                // mostrar opciones: ver publicaciones, crear publicacion, eliminar o volver
                while (opcionPublicaciones != 4)
                {
                    cout << "1. Ver publicaciones" << endl;
                    cout << "2. Crear publicacion" << endl;
                    cout << "3. Eliminar publicacion" << endl;
                    cout << "4. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> opcionPublicaciones;

                    switch (opcionPublicaciones)
                    {
                    case 1:
                        cout << "Ver publicaciones" << endl;
                        break;
                    case 2:
                        cout << "Crear publicacion" << endl;
                        break;
                    case 3:
                        cout << "Eliminar publicacion" << endl;
                        break;
                    case 4:
                        cout << "Volver" << endl;
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                    }
                }
                break;
            case 4:
                cout << "Reportes" << endl;
                break;
            case 5:
                cout << "Cerrar sesion" << endl;
                logoutUser();
                break;
            default:
                cout << "Opcion no valida" << endl;
            }
        }
    }
}