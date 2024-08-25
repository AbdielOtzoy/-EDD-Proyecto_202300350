#include <iostream>
#include <string>
#include "./headers/auth.h"

using namespace std;

int main()
{
    addTestData();
    while (true)
    {
        cout << endl;
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
                opcionPerfil = 0;
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
                        viewProfile();
                        break;
                    case 2:
                        cout << "Eliminar perfil" << endl;
                        deleteAccount();
                        opcionPerfil = 3;
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
                opcionSolicitudes = 0;
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
                        respondRequest();
                        break;
                    case 2:
                        cout << "Enviar solicitud" << endl;
                        sendRequest();
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
                opcionPublicaciones = 0;
                // mostrar opciones: ver publicaciones, crear publicacion, eliminar o volver
                while (opcionPublicaciones != 3)
                {
                    cout << "1. Ver publicaciones" << endl;
                    cout << "2. Crear publicacion" << endl;
                    cout << "3. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> opcionPublicaciones;

                    switch (opcionPublicaciones)
                    {
                    case 1:
                        cout << "Ver publicaciones" << endl;
                        viewAvailablePosts();
                        break;
                    case 2:
                        cout << "Crear publicacion" << endl;
                        createPost();
                        break;
                    case 3:
                        cout << "Volver" << endl;
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                    }
                }
                break;
            case 4:
                cout << "Reportes" << endl;
                int opcionReportes;
                opcionReportes = 0;
                // mostrar opciones: Solicitudes enviadas y recibidas, relaciones de amistad, publicaciones, mis amigos
                while (opcionReportes != 5)
                {
                    cout << "1. Solicitudes enviadas y recibidas" << endl;
                    cout << "2. Relaciones de amistad" << endl;
                    cout << "3. Publicaciones" << endl;
                    cout << "4. Mis amigos" << endl;
                    cout << "5. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> opcionReportes;

                    switch (opcionReportes)
                    {
                    case 1:
                        cout << "Solicitudes enviadas y recibidas" << endl;
                        break;
                    case 2:
                        cout << "Relaciones de amistad" << endl;
                        break;
                    case 3:
                        cout << "Publicaciones" << endl;
                        break;
                    case 4:
                        cout << "Mis amigos" << endl;
                        viewMyFriends();
                        break;
                    case 5:
                        cout << "Volver" << endl;
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                    }
                }
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