#include "menuadmin.h"

MenuAdmin::MenuAdmin() {
    //ctor
}

MenuAdmin::~MenuAdmin() {
    //dtor
}

MenuAdmin::MenuAdmin(const Academico& academico, const Usuario& usuario) {
    //Inicializa el No de registro para proximas insersiones
    ifstream file_reg(string(DIR) + string(ARCH_NO_REG));
    file_reg.read((char*)&this->noReg, sizeof(int));
    file_reg.close();

    //Nace el menu con los datos de la cuenta usuario y del academico
    this->academico = academico;
    this->usuario = usuario;
    menuPrincipal();
}

void MenuAdmin::menuPrincipal() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Menu del administrador -> " << academico.getNombre() << " ***" << endl << endl;
        cout << "1) Administrar perfil."<< endl;
        cout << "2) Administrar usuarios."<< endl;
        cout << "3) Administrar académicos."<< endl;
        cout << "4) Administrar producción academica."<< endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "0");
        if(opc == "1") {
            administrarPerfil();
        } else if(opc == "2") {
            administrarUsuarios();
        } else if(opc == "3") {
            administrarAcademicos();
        } else if(opc == "4") {
            administrarProduccion();
        } else {
            cout << endl << "Gracias por usar el menú de administradores...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::administrarPerfil() {
    //Abre el menu de usuario, especificamente para el Administrador loggeado
    new MenuUsr(this->academico, this->usuario);
}

void MenuAdmin::administrarUsuarios() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administracion de usuarios ***" << endl << endl;
        cout << "1) Agregar usuario." << endl;
        cout << "2) Mostrar usuario." << endl;
        cout << "3) Modificar usuario." << endl;
        cout << "4) Eliminar usuario." << endl;
        cout << "0) Salir..." << endl<< endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "0");
        if(opc == "1") {
            agregarUsuario();
        } else if(opc == "2") {
            mostrarUsuario();
        } else if(opc == "3") {
            modificarUsuario();
        } else if(opc == "4") {
            eliminarUsuario();
        } else {
            cout << endl << endl << "Gracias por usar el administrador de usuarios...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::agregarUsuario() {
    system(CLEAR);
    cout << "*** Agregar nuevo usuario ***" << endl << endl;
    Usuario newUsuario;
    string auxStr;
    //Implementar unico usuario
    bool existencia = false;
    do {
        cout << "Ingrese el username: ";
        getline(cin, auxStr);
        if(existeUsername(auxStr)) {
            existencia = true;
            cout << "Username ya existe. Intente de nuevo." << endl << endl;
        } else {
            existencia = false;
        }
    } while(existencia);
    newUsuario.setUsername(auxStr);

    cout << "Ingrese la contraseña: ";
    getline(cin, auxStr);
    newUsuario.setPassword(auxStr);

    cout << endl << "Elija el tipo de usuario." << endl;
    cout << "1) Administrador." << endl;
    cout << "2) Usuario." << endl << endl;
    do {
        cout << ">> ";
        getline(cin, auxStr);
    } while(auxStr != "1" and auxStr != "2");
    if(auxStr == "1") {
        newUsuario.setTipo("Admin");
    } else {
        newUsuario.setTipo("User");
    }
    this->noReg++;
    newUsuario.setNoReg(this->noReg);
    insertarUsuario(newUsuario);
    cout << endl << "Usuario registrado exitosamente.";
}

void MenuAdmin::mostrarUsuario() {
    system(CLEAR);
    cout << "*** Mostrar usuario ***" <<endl << endl;
    ifstream arch_usr(string(DIR) + string(ARCH_USR));
    if(!arch_usr.good()) {
        cout << "ERROR. No existe el archivo.";
        arch_usr.close();
        return;
    }
    ifstream arch_ac(string(DIR) + string(ARCH_AC));
    while(!arch_usr.eof()) {
        Usuario usr;
        arch_usr.read((char*)&usr, sizeof(Usuario));
        if(arch_usr.eof()) { break; }
        Academico ac;
        cout << "Usuario #" << usr.getNoRegistro() << endl;
        cout << usr.toString() << endl;
        arch_ac.seekg(usr.getDireccionFisica(), ios::beg);
        arch_ac.read((char*)&ac, sizeof(Academico));
        cout << ac.toString()<< endl << endl;
    }
    arch_ac.close();
    arch_usr.close();
}

void MenuAdmin::modificarUsuario() {
    system(CLEAR);
    string username;
    cout << "*** Modificación de usuario ***" << endl << endl;
    cout << "Ingrese el usuario (username) a modificar: ";
    getline(cin, username);
    if(existeUsername(username)) {
        long int posArchivo;
        Usuario usr;
        fstream arch_usr(string(DIR) + string(ARCH_USR), ios::in|ios::out);
        while(!arch_usr.eof()) {
            arch_usr.read((char*)& usr, sizeof(Usuario));
            if(arch_usr.eof()) { break; }
            if(string(usr.getUsername()) == username) {
                posArchivo = arch_usr.tellg();
                posArchivo -= sizeof(Usuario);
                break;
            }
        }
        arch_usr.close();

        string opc;
        do {
            system(CLEAR);
            cout << "*** Modificación de datos del usuario " << usr.getUsername() << " ***" << endl << endl;
            cout << "1) Restaurar contraseña." << endl;
            cout << "2) Cambiar tipo de usuario" << endl;
            cout << "0) Salir..." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opc);
            } while(opc != "1" and opc != "2" and opc != "0");
            if(opc == "1") {
                cout << endl << "El usuario se restaurara con una contraseña simple. Contraseña de temporal: 123" << endl;
                usr.setPassword("123");
            } else if(opc == "2") {
                string tipo;
                cout << endl << "Elija el tipo de usuario." << endl;
                cout << "1) Administrador." << endl;
                cout << "2) Usuario." << endl << endl;
                do {
                    cout << ">> ";
                    getline(cin, tipo);
                } while(tipo != "1" and tipo != "2");
                if(tipo == "1") {
                    usr.setTipo("Admin");
                } else {
                    usr.setTipo("User");
                }
            } else {
                fstream arch(string(DIR) + string(ARCH_USR), ios::in|ios::out);
                arch.seekg(posArchivo,ios::beg);
                arch.write((char*)&usr, sizeof(Usuario));
                arch.close();
                cout << "Modificación completa de usuario..." << endl;
            }
            if(opc != "0") {
                pausa();
            }
        } while(opc != "0");
    } else {
        cout << "No existe el usuario buscado.";
    }
}

void MenuAdmin::eliminarUsuario() {
    system(CLEAR);
    string username;
    cout << "*** Eliminación de usuario ***" << endl << endl;
    cout << "Tome en cuenta que la eliminación de usuario, " << endl << "no eliminara la información como académico." << endl;
    cout << "Si desea eliminar su información de académico," << endl << "debe entrar al menú de 'Administración de académicos'." << endl;
    cout << "Ingrese el usuario (username) a eliminar: ";
    getline(cin, username);
    if(existeUsername(username)) {
        ifstream leer(string(DIR) + string(ARCH_USR));
        while(!leer.eof()) {
            Usuario usr;
            leer.read((char*)&usr, sizeof(Usuario));
            if(leer.eof()) { break; }
            if(string(usr.getUsername()) == username) {
                cout << endl << "Eliminando al usuario: " << usr.getUsername() << endl;
            } else {
                ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                escribir.write((char*)&usr, sizeof(Usuario));
                escribir.close();
            }
        }
        leer.close();
        string rm = string(DIR) + string(ARCH_USR);
        string rname = string(DIR) + "Temporal.txt";
        remove(rm.c_str());
        rename(rname.c_str(), rm.c_str());
    } else {
        cout << "No existe el usuario buscado.";
    }
}

void MenuAdmin::administrarAcademicos() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administracion de académicos ***" << endl << endl;
        cout << "1) Mostrar académico." << endl;
        cout << "2) Modificar académico." << endl;
        cout << "3) Eliminar académico." << endl;
        cout << "0) Salir..." << endl<< endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "0");
        if(opc == "1") {
            mostrarAcademicos();
        } else if(opc == "2") {
            modificarAcademico();
        } else if(opc == "3") {
            eliminarAcademico();
        } else {
            cout << endl << endl << "Gracias por usar el administrador de académicos...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::mostrarAcademicos() {
    cout << "*** Mostrar académicos ***"<< endl << endl;
    ifstream arch_ac(string(DIR) + string(ARCH_AC));
    if(!arch_ac.good()){
        cout << "No hay academicos registrados." << endl;
    }
    else{
        int i = 1;
        while(!arch_ac.eof()) {
            Academico ac;
            arch_ac.read((char*)&ac, sizeof(Academico));
            if(arch_ac.eof()) { break; }
            cout << "Académico #" << i << endl;
            cout << ac.toString()<< endl << endl;
            i++;
        }
    }
    arch_ac.close();
}

void MenuAdmin::modificarAcademico() {
    system(CLEAR);
    cout << "*** Modificar Academico ***" << endl << endl;
    string nombre;
    cout << endl << "Ingrese el nombre (Completo o parcial) del académico a modificar: ";
    getline(cin, nombre);

    Lista listaResultado;
    ifstream arch_ac(string(DIR) + string(ARCH_AC));
    if(!arch_ac.good()){
        cout << "No hay academicos registrados." << endl;
        arch_ac.close();
        return;
    }

    while(!arch_ac.eof()) {
        Academico ac;
        arch_ac.read((char*)&ac, sizeof(Academico));
        if(arch_ac.eof()) { break; }
        if(strstr(ac.getNombre(), nombre.c_str())) {
            listaResultado.insertar(listaResultado.ultimaPos(), ac);
        }
    }
    arch_ac.close();

    if(listaResultado.estaVacia()) {
        cout << "Ningún academico coincidio en la busqueda." << endl;
    } else {
        string opc;
        bool bandera = false;
        cout << listaResultado.toString();
        cout << "0-> No modificar nada nada..." << endl;
        cout << "Elija un académico para modificar su información." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
            if(!formatoNumero(opc)) {
                bandera = false;
            } else {
                if(atoi(opc.c_str()) < 0 or atoi(opc.c_str()) > listaResultado.datosTotales()) {
                    bandera = false;
                } else {
                    bandera = true;
                }
            }
        } while(!bandera);

        if(opc != "0") {
            infoPersonal(listaResultado[atoi(opc.c_str())]);
        } else {
            cout << endl << "Cancelación de modificación..." << endl;
        }
        listaResultado.eliminarNodos();
    }
}

void MenuAdmin::infoPersonal(Academico& ac) {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de información personal - "<< ac.getNombre() <<" ***" << endl << endl;
        cout << "1) Actualizar nombre." << endl;
        cout << "2) Actualizar domicilio." << endl;
        cout << "3) Actualizar ciudad." << endl;
        cout << "4) Actualizar telefono." << endl;
        cout << "5) Actualizar email." << endl;
        cout << "6) Actualizar estado civil." << endl;
        cout << "7) Administrar dependientes economicos." << endl;
        cout << "8) Administrar formación académica." << endl;
        cout << "9) Administrar docencia académica." << endl;
        cout << "10) Administrar tutoria académica." << endl;
        cout << "11) Mostrar información de académico." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and
                opc != "5" and opc != "6" and opc != "7"  and opc != "8" and
                opc != "9" and opc != "10"  and opc != "11" and opc != "0");
        //Edicion del perfil de usuario
        if(opc == "1") {
            string nombre;
            cout << endl << "Ingrese el nuevo nombre del académico: ";
            getline(cin, nombre);
            ac.setNombre(nombre);
            cout << endl << "¡Nombre actualizado!";
        } else if(opc == "2") {
            string domicilio;
            cout << endl << "Ingrese el nuevo domicilio del académico: ";
            getline(cin, domicilio);
            ac.setDomicilio(domicilio);
            cout << endl << "¡Domicilio actualizado!";
        } else if(opc == "3") {
            string ciudad;
            cout << endl << "Ingrese la nueva ciudad del académico: ";
            getline(cin, ciudad);
            ac.setCiudad(ciudad);
            cout << endl << "¡Ciudad actualizada!";
        } else if(opc == "4") {
            string telefono;
            cout << endl;
            do {
                cout << "Ingrese el nuevo telefono del académico (10 Dígitos): ";
                getline(cin, telefono);
                if(telefono.length() != 10 or !formatoNumero(telefono)) {
                    cout << "El formato de telefono es incorrecto. Intente de nuevo." << endl;
                }
            } while(telefono.length() != 10 or !formatoNumero(telefono));
            ac.setTelefono(telefono);
            cout << endl << "¡Telefono actualizado!";
        } else if(opc == "5") {
            string email;
            cout << endl;
            do {
                cout << "Ingrese el nuevo email del académico: ";
                getline(cin, email);
                if(!formatoEmail(email)) {
                    cout << "Formato incorrecto de email. Intente de nuevo." << endl;
                }
            } while(!formatoEmail(email));
            ac.setEmail(email);
            cout << endl << "¡Email actualizado!";
        } else if(opc == "6") {
            string estadoCivil;
            cout << endl << "Seleccione el estado civil del académico." << endl;
            cout << "1) Soltero." << endl;
            cout << "2) Casado." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, estadoCivil);
            } while(estadoCivil != "1" and estadoCivil != "2");
            if(estadoCivil == "1") {
                ac.setEstadoCivil("Soltero");
            } else {
                ac.setEstadoCivil("Casado");
            }
            cout << endl << "¡Estado civil actualizado!";
        } else if(opc == "7") {
            dependientesEconomicos(ac);
        } else if(opc == "8") {
            formacion(ac);
        } else if(opc == "9") {
            docencia(ac);
        } else if(opc == "10") {
            tutoria(ac);
        } else if(opc == "11") {
            system(CLEAR);
            cout << "---------------------------------------------------------------" << endl;
            cout << "Academico: " << ac.getNombre() << "    | Email: " << ac.getEmail() << endl;
            cout << "Domicilio: " << ac.getDomicilio() << " ->  Ciudad: " << ac.getCiudad() << endl;
            cout << "Telefono: " << ac.getTelefono() << "       | Estado civil: " << ac.getEstadoCivil() << endl;
            cout << "---------------------------------------------------------------" << endl;
        } else {
            //Guarda la información recien modificada
            ifstream leer(string(DIR) + string(ARCH_AC));
            while(!leer.eof()) {
                Academico auxAcademico;
                leer.read((char*)&auxAcademico, sizeof(Academico));
                if(leer.eof()) { break; }
                if(ac.getNoReg() == auxAcademico.getNoReg()) {
                    ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                    escribir.write((char*)&ac, sizeof(Academico));
                    escribir.close();
                } else {
                    ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                    escribir.write((char*)&auxAcademico, sizeof(Academico));
                    escribir.close();
                }
            }
            leer.close();
            string rm = string(DIR) + string(ARCH_AC);
            string rname = string(DIR) + "Temporal.txt";
            remove(rm.c_str());
            rename(rname.c_str(), rm.c_str());
            cout << endl << "Terminando de modificar información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::dependientesEconomicos(Academico& ac) {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Dependientes económicos de " << ac.getNombre() << " ***" << endl << endl;
        cout << "1) Agregar dependiente." << endl;
        cout << "2) Mostrar dependientes." << endl;
        cout << "3) Modificar dependiente." << endl;
        cout << "4) Eliminar dependiente." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "0" and opc != "1" and opc != "2"
                and opc != "3" and opc != "4");
        if(opc == "1") {
            string nombre, edad;
            bool bandera = true;
            do {
                //Revisar si no hay homonimos
                cout << endl << "Ingrese el nombre del dependiente: ";
                getline(cin, nombre);
                if(existeDependiente(nombre, ac)) {
                    cout << "El nombre del dependiente ya existe. Intente de nuevo." << endl;
                    bandera = true;
                } else {
                    bandera = false;
                }
            } while(bandera);
            do {
                cout << "Ingrese la edad del dependiente: ";
                getline(cin, edad);
                if(!formatoNumero(edad)) {
                    cout << "El formato no es númerico. Intente de nuevo." << endl;
                }
            } while(!formatoNumero(edad));

            //Ingresa informacion dentro del objeto
            Dependiente dep;
            dep.setNoReg(ac.getNoReg());
            dep.setNombre(nombre);
            dep.setEdad(atoi(edad.c_str()));

            //Guarda dentro del archivo el objeto
            guardaDependiente(dep, string(DIR) + string(ARCH_DEPENDIENTE));

            cout << endl <<"¡Nuevo dependiente agregado exitosamente!";
        } else if(opc == "2") {
            system(CLEAR);
            cout << "*** Mostrando dependientes económicos del academico " << ac.getNombre() << " ***" << endl << endl;
            ifstream file(string(DIR) + string(ARCH_DEPENDIENTE));
            if(!file.good()) {
                file.close();
                ofstream file_dep(string(DIR) + string(ARCH_DEPENDIENTE));
                file_dep.close();
                cout << "ERROR. No existe el archivo. Creando archivo...";
                return;
            }
            int i = 1;
            bool bandera = false;
            while(!file.eof()) {
                Dependiente dep;
                file.read((char*)&dep, sizeof(Dependiente));
                if(file.eof()) { break; }
                //Busca si existe el nombre de dependiente por el usuario
                if(dep.getNoReg() == ac.getNoReg()) {
                    bandera = true;
                    cout << "Dependiente #" << i << endl;
                    cout << "Nombre: " << dep.getNombre() << endl;
                    cout << "Edad: " << dep.getEdad() << endl << endl;
                    i++;
                }
            }
            file.close();
            if(!bandera) {
                cout << "No hay dependientes para este usuario." << endl;
            }
        } else if(opc == "3") {
            string nombre;
            cout << endl << "Ingrese el nombre del dependiente a modificar: ";
            getline(cin, nombre);
            if(existeDependiente(nombre, ac)) {
                Dependiente dep;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_DEPENDIENTE), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&dep, sizeof(Dependiente));
                    if(file_out.eof()) {
                        break;
                    }
                    //Rompe el ciclo cuando encuentra al Dependiente para modificarlo
                    if(string(dep.getNombre()) == nombre and dep.getNoReg() == ac.getNoReg()) {
                        //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                        posArchivo = file_out.tellg();
                        posArchivo -= sizeof(Dependiente);
                        break;
                    }
                }
                file_out.close();
                //Menú de modificación
                string opc;
                do {
                    system(CLEAR);
                    cout << "** Dependiente: " << dep.getNombre() << " -> Edad: " << dep.getEdad() << " ***" << endl << endl;
                    cout << "¿Que desea modificar?" << endl;
                    cout << "1) Nombre." << endl;
                    cout << "2) Edad." << endl;
                    cout << "0) Salir..." << endl << endl;
                    do {
                        cout << ">> ";
                        getline(cin, opc);
                    } while(opc != "1" and opc != "2" and opc != "0");

                    if(opc == "1") {
                        string nombre;
                        bool bandera = false;
                        do {
                            cout << endl << "Ingrese el nuevo nombre del dependiente: ";
                            getline(cin, nombre);
                            if(existeDependiente(nombre, ac)) {
                                cout << "El nombre de dependiente ya existe, intente con uno nuevo." << endl;
                                bandera = true;
                            } else {
                                bandera = false;
                            }
                        } while(bandera);
                        dep.setNombre(nombre);
                    } else if(opc == "2") {
                        string edad;
                        do {
                            cout << endl << "Ingrese la nueva edad del dependiente: ";
                            getline(cin, edad);
                            if(!formatoNumero(edad)) {
                                cout << "El formato no es númerico. Intente de nuevo." << endl;
                            }
                        } while(!formatoNumero(edad));
                        dep.setEdad(atoi(edad.c_str()));
                    } else {
                        //Sobreescribe el dependiente en la posicion de memoria previamente obtenida
                        fstream file(string(DIR) + string(ARCH_DEPENDIENTE), ios::in|ios::out);
                        file.seekg(posArchivo, ios::beg);
                        file.write((char*)& dep, sizeof(Dependiente));
                        file.close();
                        cout << endl << "Modificación completa del dependiente.";
                    }
                    if(opc != "0") {
                        pausa();
                    }
                } while(opc != "0");

            } else {
                cout << endl << "No existe el dependiente.";
            }
        } else if(opc == "4") {
            string nombre;
            cout << endl << "Ingrese el nombre del dependiente a eliminar: ";
            getline(cin, nombre);
            if(existeDependiente(nombre, ac)) {
                ifstream file_out(string(DIR) + string(ARCH_DEPENDIENTE));
                while(!file_out.eof()) {
                    Dependiente dep;
                    file_out.read((char*)&dep, sizeof(Dependiente));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(dep.getNombre()) == nombre and dep.getNoReg() == ac.getNoReg()) {
                        cout << "Eliminando: " << dep.getNombre() << endl;
                    } else {
                        guardaDependiente(dep, string(DIR) + "Temporal.txt");
                    }
                }
                file_out.close();
                //Eliminacion del archivo viejo y sustitucion por el nuevo
                string rem = string(DIR) + string(ARCH_DEPENDIENTE);
                string rena = string(DIR) + "Temporal.txt";
                remove(rem.c_str());
                rename(rena.c_str(), rem.c_str());
                cout << "Se elimino el dependiente exitosamente.";
            } else {
                cout << endl << "No existe el dependiente.";
            }
        } else {
            cout << endl << "Regresando al menú de administración de información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::formacion(Academico& ac) {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de la formación académica de - "<< ac.getNombre() <<" ***" << endl << endl;
        cout << "1) Agregar nuevo grado de estudios." << endl;
        cout << "2) Mostrar grados de estudio." << endl;
        cout << "3) Modificar grado de estudio." << endl;
        cout << "4) Eliminar grado de estudio." << endl;
        cout << "0) Salir..." << endl << endl;
        cout << ">> ";
        getline(cin, opc);
        if(opc == "1") {
            system(CLEAR);
            string tipoGrado, opc;
            cout << "*** Ingresando formación del académico " << ac.getNombre() << " ***" << endl << endl;
            cout << "Elija el tipo de grado." << endl;
            cout << "1) Licenciatura." << endl;
            cout << "2) Especialidad." << endl;
            cout << "3) Maestria." << endl;
            cout << "4) Doctorado." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opc);
            } while(opc != "1" and opc != "2" and opc != "3" and opc != "4");
            if(opc == "1") {
                tipoGrado = "Licenciatura";
            } else if(opc == "2") {
                tipoGrado = "Especialidad";
            } else if(opc == "3") {
                tipoGrado = "Maestria";
            } else {
                tipoGrado = "Doctorado";
            }
            cout << endl;
            string nombreGrado, institucion;
            cout << "Ingrese el nombre del grado: ";
            getline(cin, nombreGrado);
            //Si ya existe el grado no lo guarda y regresa al menu principal
            if(existeFormacion(tipoGrado, nombreGrado, ac)) {
                cout << endl << "La formación intenta agregar ya existe. Es imposible registrarla." << endl;
                return;
            }
            cout << "Ingrese la institución de procedencia: ";
            getline(cin, institucion);
            Fecha fechaIni, fechaFin, fechaOb;
            //Corroborar el formato despues
            string fecha;
            do {
                cout << "Ingrese la fecha de inicio de cursos (Formato: DD/MM/AAAA): ";
                getline(cin, fecha);
                if(!fechaCorrecta(fecha)) {
                    cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                }
            } while(!fechaCorrecta(fecha));
            fechaIni = regresaFecha(fecha);
            do {
                cout << "Ingrese la fecha de fin de cursos (Formato: DD/MM/AAAA): ";
                getline(cin, fecha);
                if(!fechaCorrecta(fecha)) {
                    cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                }
            } while(!fechaCorrecta(fecha));
            fechaFin = regresaFecha(fecha);
            do {
                cout << "Ingrese la fecha de obtención (Formato: DD/MM/AAAA): ";
                getline(cin, fecha);
                if(!fechaCorrecta(fecha)) {
                    cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                }
            } while(!fechaCorrecta(fecha));
            fechaOb = regresaFecha(fecha);
            string cedula;
            cout << "Ingrese el número de cédula profesional: ";
            getline(cin, cedula);

            //Crea el objeto de la formación profesional
            Formacion form;
            form.setNoReg(ac.getNoReg());
            form.setTipo(tipoGrado);
            form.setNombre(nombreGrado);
            form.setInstitucion(institucion);
            form.setFechaInicio(fechaIni);
            form.setFechaFinal(fechaFin);
            form.setFechaObtencion(fechaOb);
            form.setCedula(cedula);
            guardaFormacion(form, string(DIR) + string(ARCH_FORMACION));

            cout << endl <<"¡Nueva formación agregada exitosamente!";
        } else if(opc == "2") {
            system(CLEAR);
            cout << "*** Formación académica actual de " << ac.getNombre() << " ***" << endl << endl;
            ifstream file(string(DIR) + string(ARCH_FORMACION));
            if(!file.good()) {
                file.close();
                ofstream file_form(string(DIR) + string(ARCH_FORMACION));
                file_form.close();
                cout << "ERROR. No existe el archivo. Creando archivo...";
                return;
            }
            bool bandera = false;
            while(!file.eof()) {
                Formacion form;
                file.read((char*)&form, sizeof(Formacion));
                if(file.eof()) { break; }
                //Busca si existe el nombre de dependiente por el usuario
                if(form.getNoReg() == ac.getNoReg()) {
                    bandera = true;
                    cout << "Titulo: " << form.getTipo() << " " << form.getNombre() << endl;
                    cout << "Institución académica: " << form.getInstitucion() << endl;
                    cout << "Fecha de inicio: " << form.getFechaInicio().toString() << " -> Fecha de fin: " << form.getFechaFinal().toString() << endl;
                    cout << "Fecha de obtencion: " << form.getFechaObtencion().toString() << " -> Cedula: " << form.getCedula() << endl << endl;
                }
            }
            file.close();
            if(!bandera) {
                cout << "No hay formación académica para este usuario." << endl;
            }
        } else if(opc == "3") {
            system(CLEAR);
            string tipoGrado, opc;
            cout << "*** Modificar formación académica de " << ac.getNombre() << " ***" << endl << endl;
            cout << "Elija el tipo y nombre de grado a modificar." << endl;
            cout << "1) Licenciatura." << endl;
            cout << "2) Especialidad." << endl;
            cout << "3) Maestria." << endl;
            cout << "4) Doctorado." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opc);
            } while(opc != "1" and opc != "2" and opc != "3" and opc != "4");
            if(opc == "1") {
                tipoGrado = "Licenciatura";
            } else if(opc == "2") {
                tipoGrado = "Especialidad";
            } else if(opc == "3") {
                tipoGrado = "Maestria";
            } else {
                tipoGrado = "Doctorado";
            }
            string nombreGrado;
            cout << endl << "Ingrese el nombre: ";
            getline(cin, nombreGrado);
            //Verifica si existe la formación académica
            if(existeFormacion(tipoGrado, nombreGrado, ac)) {
                Formacion form;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_FORMACION), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&form, sizeof(Formacion));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(form.getTipo()) == tipoGrado and string(form.getNombre()) == nombreGrado
                            and form.getNoReg() == ac.getNoReg()) {
                        //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                        posArchivo = file_out.tellg();
                        posArchivo -= sizeof(Formacion);
                        break;
                    }
                }
                file_out.close();
                //Menu de modificación
                string opc;
                do {
                    system(CLEAR);
                    cout << "*** Modificación de formación " << form.getTipo() << " " << form.getNombre() << " ***" << endl << endl;
                    cout << "1) Tipo." << endl;
                    cout << "2) Nombre" << endl;
                    cout << "3) Fecha de inicio." << endl;
                    cout << "4) Fecha de fin." << endl;
                    cout << "5) Fecha de obtención." << endl;
                    cout << "6) Cedula." << endl;
                    cout << "0) Salir..." << endl << endl;
                    do {
                        cout << ">> ";
                        getline(cin, opc);
                    } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "5" and opc != "6");
                    if(opc == "1") {
                        string tipoGrado, opc;
                        cout << endl << "Elija el tipo de grado." << endl;
                        cout << "1) Licenciatura." << endl;
                        cout << "2) Especialidad." << endl;
                        cout << "3) Maestria." << endl;
                        cout << "4) Doctorado." << endl << endl;
                        do {
                            cout << ">> ";
                            getline(cin, opc);
                        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4");
                        if(opc == "1") {
                            tipoGrado = "Licenciatura";
                        } else if(opc == "2") {
                            tipoGrado = "Especialidad";
                        } else if(opc == "3") {
                            tipoGrado = "Maestria";
                        } else {
                            tipoGrado = "Doctorado";
                        }
                        if(existeFormacion(tipoGrado, form.getNombre(), ac)) {
                            cout << endl << "La formación intenta agregar ya existe. Es imposible registrarla." << endl;
                        } else {
                            form.setTipo(tipoGrado);
                        }
                    } else if (opc == "2") {
                        string nombreGrado;
                        cout << "Ingrese el nombre del grado: ";
                        getline(cin, nombreGrado);
                        if(existeFormacion(form.getTipo(), nombreGrado, ac)) {
                            cout << endl << "La formación intenta agregar ya existe. Es imposible registrarla." << endl;
                        } else {
                            form.setNombre(nombreGrado);
                        }
                    } else if (opc == "3") {
                        Fecha fechaIni;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de inicio de cursos (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaIni = regresaFecha(fecha);
                        form.setFechaInicio(fechaIni);
                    } else if (opc == "4") {
                        Fecha fechaFin;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de fin de cursos (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaFin = regresaFecha(fecha);
                        form.setFechaFinal(fechaFin);
                    } else if (opc == "5") {
                        Fecha fechaOb;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de obtención (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaOb = regresaFecha(fecha);
                        form.setFechaObtencion(fechaOb);
                    } else if (opc == "6") {
                        string cedula;
                        cout << "Ingrese el número de cédula profesional: ";
                        getline(cin, cedula);
                        form.setCedula(cedula);
                    } else {
                        fstream file(string(DIR) + string(ARCH_FORMACION), ios::in|ios::out);
                        file.seekg(posArchivo, ios::beg);
                        file.write((char*)& form, sizeof(Formacion));
                        file.close();
                        cout << endl << "Modificación completa de la formación.";
                    }
                } while(opc != "0");
            } else {
                cout << endl << "No existe la formación.";
            }

        } else if(opc == "4") {
            system(CLEAR);
            string tipoGrado, opc;
            cout << "*** Eliminando formación  de " << ac.getNombre() << " ***" << endl << endl;
            cout << "Elija el tipo y nombred de grado a eliminar." << endl;
            cout << "1) Licenciatura." << endl;
            cout << "2) Especialidad." << endl;
            cout << "3) Maestria." << endl;
            cout << "4) Doctorado." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opc);
            } while(opc != "1" and opc != "2" and opc != "3" and opc != "4");
            if(opc == "1") {
                tipoGrado = "Licenciatura";
            } else if(opc == "2") {
                tipoGrado = "Especialidad";
            } else if(opc == "3") {
                tipoGrado = "Maestria";
            } else {
                tipoGrado = "Doctorado";
            }
            string nombreGrado;
            cout << endl << "Ingrese el nombre: ";
            getline(cin, nombreGrado);
            //Verifica si existe la formación académica
            if(existeFormacion(tipoGrado, nombreGrado, ac)) {
                fstream file_out(string(DIR) + string(ARCH_FORMACION));
                while(!file_out.eof()) {
                    //Lee el objeto
                    Formacion form;
                    file_out.read((char*)&form, sizeof(Formacion));
                    //Verifica que el archivo no se haya terminado
                    if(file_out.eof()) {
                        break;
                    }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(form.getTipo()) == tipoGrado and string(form.getNombre()) == nombreGrado
                            and form.getNoReg() == ac.getNoReg()) {
                        cout << "Eliminando: " << form.getTipo() << " " << form.getNombre() << endl;
                    } else {
                        guardaFormacion(form, string(DIR) + "Temporal.txt");
                    }
                }
                file_out.close();
                //Eliminacion del archivo viejo y sustitucion por el nuevo
                string rem = string(DIR) + string(ARCH_FORMACION);
                string rena = string(DIR) + "Temporal.txt";
                remove(rem.c_str());
                rename(rena.c_str(), rem.c_str());
                cout << "Se elimino la formación exitosamente.";
            } else {
                cout << endl << "No existe la formación.";
            }
        } else {
            cout << endl << "Regresando al menú de administración de información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::docencia(Academico& ac) {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administracion de la docencia - "<< ac.getNombre() <<" ***" << endl << endl;
        cout << "1) Agregar nueva materia." << endl;
        cout << "2) Mostrar materia." << endl;
        cout << "3) Modificar materia." << endl;
        cout << "4) Eliminar materia." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4");
        if(opc == "1") {
            cout << endl;
            Docencia doc;
            string nombre, fecha, horasSemanales;
            Fecha fechaIni, fechaFin;

            cout << "Ingrese el nombre de la materia: ";
            getline(cin, nombre);
            if(existeDocencia(nombre, ac)) {
                cout << "Ya existe la materia. Es imposible registrarla." << endl << endl;
            } else {

                do {
                    cout << "Ingrese la fecha de inicio de cursos (Formato: DD/MM/AAAA): ";
                    getline(cin, fecha);
                    if(!fechaCorrecta(fecha)) {
                        cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                    }
                } while(!fechaCorrecta(fecha));
                fechaIni = regresaFecha(fecha);

                do {
                    cout << "Ingrese la fecha de fin de cursos (Formato: DD/MM/AAAA): ";
                    getline(cin, fecha);
                    if(!fechaCorrecta(fecha)) {
                        cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                    }
                } while(!fechaCorrecta(fecha));
                fechaFin = regresaFecha(fecha);

                do {
                    cout << "Ingrese las horas semanales: ";
                    getline(cin, horasSemanales);
                    if(!formatoNumero(horasSemanales)) {
                        cout << "El formato no es númerico. Intente de nuevo." << endl;
                    }
                } while(!formatoNumero(horasSemanales));

                //Guarda informacion dentro del objeto
                doc.setNoReg(ac.getNoReg());
                doc.setNombre(nombre);
                doc.setFechaInicio(fechaIni);
                doc.setFechaFin(fechaFin);
                doc.setCantidadHoras(horasSemanales);

                //Guarda en el archivo
                guardaDocencia(doc, string(DIR) + string(ARCH_DOCENCIA));
                cout << endl <<"¡Nueva materia agregada exitosamente!";
            }
        } else if(opc == "2") {
            system(CLEAR);
            cout << "*** Docencia académica actual de " << ac.getNombre() << " ***" << endl << endl;
            ifstream file(string(DIR) + string(ARCH_DOCENCIA));
            if(!file.good()) {
                file.close();
                ofstream file_form(string(DIR) + string(ARCH_DOCENCIA));
                file_form.close();
                cout << "ERROR. No existe el archivo. Creando archivo...";
                return;
            }
            bool bandera = false;
            while(!file.eof()) {
                Docencia doc;
                file.read((char*)&doc, sizeof(Docencia));
                if(file.eof()) { break; }
                //Busca si existe el nombre de dependiente por el usuario
                if(doc.getNoReg() == ac.getNoReg()) {
                    bandera = true;
                    cout << "Materia: " << doc.getNombre() << endl;
                    cout << "Fecha de inicio: " << doc.getFechaInicio().toString() << " -> Fecha de fin: " << doc.getFechaFin().toString() << endl;
                    cout << "Horas semanales: " << doc.getCantidadHoras() << endl << endl;
                }
            }
            file.close();
            if(!bandera) {
                cout << "No hay materias registradas para este usuario." << endl;
            }
        } else if(opc == "3") {
            system(CLEAR);
            string nombre;
            cout << "*** Modificar materia de " << ac.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre de la materia a modificar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeDocencia(nombre, ac)) {
                Docencia doc;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_DOCENCIA), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&doc, sizeof(Docencia));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(doc.getNombre()) == nombre and doc.getNoReg() == ac.getNoReg()) {
                        //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                        posArchivo = file_out.tellg();
                        posArchivo -= sizeof(Docencia);
                        break;
                    }
                }
                file_out.close();
                //Menu de modificación
                string opc;
                do {
                    system(CLEAR);
                    cout << "*** Modificación de la materia " << doc.getNombre() << " ***" << endl << endl;
                    cout << "1) Nombre" << endl;
                    cout << "2) Fecha de inicio." << endl;
                    cout << "3) Fecha de fin." << endl;
                    cout << "4) Horas semanales." << endl;
                    cout << "0) Salir..." << endl << endl;
                    do {
                        cout << ">> ";
                        getline(cin, opc);
                    } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4");
                    cout << endl;
                    if(opc == "1") {
                        string nombre;
                        cout << "Ingrese el nombre de la materia: ";
                        getline(cin, nombre);
                        if(existeDocencia(nombre, ac)) {
                            cout << "Ya existe la materia. Es imposible registrarla." << endl << endl;
                        } else {
                            doc.setNombre(nombre);
                        }
                    } else if (opc == "2") {
                        Fecha fechaIni;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de inicio de cursos (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaIni = regresaFecha(fecha);
                        doc.setFechaInicio(fechaIni);
                    } else if (opc == "3") {
                        Fecha fechaFin;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de fin de cursos (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaFin = regresaFecha(fecha);

                        doc.setFechaFin(fechaFin);
                    } else if (opc == "4") {
                        string horasSemanales;
                        do {
                            cout << "Ingrese las horas semanales: ";
                            getline(cin, horasSemanales);
                            if(!formatoNumero(horasSemanales)) {
                                cout << "El formato no es númerico. Intente de nuevo." << endl;
                            }
                        } while(!formatoNumero(horasSemanales));
                        doc.setCantidadHoras(horasSemanales);
                    } else {
                        fstream file(string(DIR) + string(ARCH_DOCENCIA), ios::in|ios::out);
                        file.seekg(posArchivo, ios::beg);
                        file.write((char*)& doc, sizeof(Docencia));
                        file.close();
                        cout << endl << "Modificación completa de la materia.";
                    }
                } while(opc != "0");
            } else {
                cout << endl << "No existe la materia.";
            }
        } else if(opc == "4") {
            system(CLEAR);
            string nombre;
            cout << "*** Eliminando materia de " << ac.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre de la materia a eliminar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeDocencia(nombre, ac)) {
                ifstream file_out(string(DIR) + string(ARCH_DOCENCIA));
                while(!file_out.eof()) {
                    Docencia doc;
                    file_out.read((char*)&doc, sizeof(Docencia));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(doc.getNombre()) == nombre and doc.getNoReg() == ac.getNoReg()) {
                        cout << "Eliminando: " << doc.getNombre() << endl;
                    } else {
                        guardaDocencia(doc, string(DIR) + "Temporal.txt");
                    }
                }
                file_out.close();
                //Eliminacion del archivo viejo y sustitucion por el nuevo
                string rem = string(DIR) + string(ARCH_DOCENCIA);
                string rena = string(DIR) + "Temporal.txt";
                remove(rem.c_str());
                rename(rena.c_str(), rem.c_str());
                cout << "Se elimino la materia exitosamente.";
            } else {
                cout << endl << "No existe la materia.";
            }
        } else {
            cout << endl << "Regresando al menú de administración de información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::tutoria(Academico& ac) {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de la tutoria - "<< ac.getNombre() <<" ***" << endl << endl;
        cout << "1) Agregar nuevo alumno tutorado." << endl;
        cout << "2) Mostrar alumnos tutorados." << endl;
        cout << "3) Modificar alumno tutorado." << endl;
        cout << "4) Eliminar alumno tutorado." << endl;
        cout << "0) Salir..." << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4");
        cout << endl;
        if(opc == "1") {
            cout << endl;
            Tutoria tut;
            string nombre, fecha, horasSemanales;
            Fecha fechaIni, fechaFin;
            cout << "Ingrese el nombre del alumno tutorado: ";
            getline(cin, nombre);
            if(existeTutoria(nombre, ac)) {
                cout << "Ya existe el alumno tutorado. Es imposible registrarlo." << endl << endl;
            } else {
                do {
                    cout << "Ingrese la fecha de inicio de tutoria (Formato: DD/MM/AAAA): ";
                    getline(cin, fecha);
                    if(!fechaCorrecta(fecha)) {
                        cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                    }
                } while(!fechaCorrecta(fecha));
                fechaIni = regresaFecha(fecha);

                do {
                    cout << "Ingrese la fecha de fin de tutorias (Formato: DD/MM/AAAA): ";
                    getline(cin, fecha);
                    if(!fechaCorrecta(fecha)) {
                        cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                    }
                } while(!fechaCorrecta(fecha));
                fechaFin = regresaFecha(fecha);
                do {
                    cout << "Ingrese las horas semanales de tutorias: ";
                    getline(cin, horasSemanales);
                    if(!formatoNumero(horasSemanales)) {
                        cout << "El formato no es númerico. Intente de nuevo." << endl;
                    }
                } while(!formatoNumero(horasSemanales));
                //Guarda informacion dentro del objeto
                tut.setNoReg(ac.getNoReg());
                tut.setNombreTutorado(nombre);
                tut.setFechaInicio(fechaIni);
                tut.setFechaFin(fechaFin);
                tut.setCantidadHoras(horasSemanales);
                //Guarda en el archivo
                guardaTutoria(tut, string(DIR) + string(ARCH_TUTORIA));
                cout << endl <<"¡Nuevo alumno tutorado agregado exitosamente!";
            }
        } else if(opc == "2") {
            system(CLEAR);
            cout << "*** Alumnos tutorados de " << ac.getNombre() << " ***" << endl << endl;
            ifstream file(string(DIR) + string(ARCH_TUTORIA));
            if(!file.good()) {
                file.close();
                ofstream file_tut(string(DIR) + string(ARCH_TUTORIA));
                file_tut.close();
                cout << "ERROR. No existe el archivo. Creando archivo...";
                return;
            }
            bool bandera = false;
            while(!file.eof()) {
                Tutoria tut;
                file.read((char*)&tut, sizeof(Tutoria));
                if(file.eof()) { break; }
                //Busca si existe el nombre de dependiente por el usuario
                if(tut.getNoReg() == ac.getNoReg()) {
                    bandera = true;
                    cout << "Alumno tutorado: " << tut.getNombreTutorado() << endl;
                    cout << "Fecha de inicio: " << tut.getFechaInicio().toString() << " -> Fecha de fin: " << tut.getFechaFin().toString() << endl;
                    cout << "Horas semanales: " << tut.getCantidadHoras() << endl << endl;
                }
            }
            file.close();
            if(!bandera) {
                cout << "No hay alumnos tutorados registrados para este usuario." << endl;
            }
        } else if(opc == "3") {
            system(CLEAR);
            string nombre;
            cout << "*** Modificar alumno tutorado de " << ac.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre del alumno a modificar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeTutoria(nombre, ac)) {
                Tutoria tut;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_TUTORIA), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&tut, sizeof(Tutoria));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(tut.getNombreTutorado()) == nombre and tut.getNoReg() == ac.getNoReg()) {
                        //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                        posArchivo = file_out.tellg();
                        posArchivo -= sizeof(Tutoria);
                        break;
                    }
                }
                file_out.close();
                //Menu de modificación
                string opc;
                do {
                    system(CLEAR);
                    cout << "*** Modificación del alumno " << tut.getNombreTutorado() << " ***" << endl << endl;
                    cout << "1) Nombre" << endl;
                    cout << "2) Fecha de inicio." << endl;
                    cout << "3) Fecha de fin." << endl;
                    cout << "4) Horas semanales." << endl;
                    cout << "0) Salir..." << endl << endl;
                    do {
                        cout << ">> ";
                        getline(cin, opc);
                    } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4");
                    cout << endl;
                    if(opc == "1") {
                        string nombre;
                        cout << "Ingrese el nombre de la materia: ";
                        getline(cin, nombre);
                        if(existeTutoria(nombre, ac)) {
                            cout << "Ya existe el alumno tutorado. Es imposible registrarlo." << endl << endl;
                        } else {
                            tut.setNombreTutorado(nombre);
                        }
                    } else if (opc == "2") {
                        Fecha fechaIni;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de inicio de tutorias (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaIni = regresaFecha(fecha);

                        tut.setFechaInicio(fechaIni);
                    } else if (opc == "3") {
                        Fecha fechaFin;
                        string fecha;
                        do {
                            cout << "Ingrese la fecha de fin de tutorias (Formato: DD/MM/AAAA): ";
                            getline(cin, fecha);
                            if(!fechaCorrecta(fecha)) {
                                cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                            }
                        } while(!fechaCorrecta(fecha));
                        fechaFin = regresaFecha(fecha);

                        tut.setFechaFin(fechaFin);
                    } else if (opc == "4") {
                        string horasSemanales;
                        do {
                            cout << "Ingrese las horas semanales: ";
                            getline(cin, horasSemanales);
                            if(!formatoNumero(horasSemanales)) {
                                cout << "El formato no es númerico. Intente de nuevo." << endl;
                            }
                        } while(!formatoNumero(horasSemanales));
                        tut.setCantidadHoras(horasSemanales);
                    } else {
                        fstream file(string(DIR) + string(ARCH_TUTORIA), ios::in|ios::out);
                        file.seekg(posArchivo, ios::beg);
                        file.write((char*)& tut, sizeof(Tutoria));
                        file.close();
                        cout << endl << "Modificación completa del alumno tutorado.";
                    }
                } while(opc != "0");
            } else {
                cout << endl << "No existe la materia.";
            }
        } else if(opc == "4") {
            system(CLEAR);
            string nombre;
            cout << "*** Eliminando alumno tutorado de " << ac.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre del alumno a eliminar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeTutoria(nombre, ac)) {
                ifstream file_out(string(DIR) + string(ARCH_TUTORIA));
                while(!file_out.eof()) {
                    Tutoria tut;
                    file_out.read((char*)&tut, sizeof(Tutoria));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(tut.getNombreTutorado()) == nombre and tut.getNoReg() == ac.getNoReg()) {
                        cout << "Eliminando: " << tut.getNombreTutorado() << endl;
                    } else {
                        guardaTutoria(tut, string(DIR) + "Temporal.txt");
                    }
                }
                file_out.close();
                //Eliminacion del archivo viejo y sustitucion por el nuevo
                string rem = string(DIR) + string(ARCH_TUTORIA);
                string rena = string(DIR) + "Temporal.txt";
                remove(rem.c_str());
                rename(rena.c_str(), rem.c_str());
                cout << "Se elimino el alumno exitosamente.";
            } else {
                cout << endl << "No existe la el alumno tutorado.";
            }
        } else {
            cout << endl << "Regresando al menú de administración de información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::eliminarAcademico() {
    system(CLEAR);
    string nombre;
    cout << "*** Eliminar Academico ***" << endl << endl;
    cout << "Tome en cuenta que la eliminación de un académico" << endl << "eliminara en cadena toda la información que este haya guardado." << endl;
    cout << "Como: Información personal, dependientes economicos, producciones, docencia y tutorias." << endl;
    cout << endl << "Ingrese el nombre (Completo o parcial) del académico a eliminar: ";
    getline(cin, nombre);
    Lista listaResultado;
    ifstream arch_ac(string(DIR) + string(ARCH_AC));

    if(!arch_ac.good()){
        arch_ac.close();
        cout << "No existen académicos registrados." << endl;
        return;
    }

    while(!arch_ac.eof()) {
        Academico ac;
        arch_ac.read((char*)&ac, sizeof(Academico));
        if(arch_ac.eof()) { break; }
        //Busca las coincidencias con la substring, evitando que sea la cuenta actual o la cuenta primaria de administrador
        if(strstr(ac.getNombre(), nombre.c_str()) and ac.getNoReg() != this->academico.getNoReg() and ac.getNoReg() != 1) {
            listaResultado.insertar(listaResultado.ultimaPos(), ac);
        }
    }
    arch_ac.close();
    if(listaResultado.estaVacia()) {
        cout << "Ningún academico coincidio en la busqueda." << endl;
    } else {
        string opc;
        bool bandera = false;
        cout << listaResultado.toString();
        cout << "0-> No eliminar nada nada..." << endl;
        cout << "Elija un académico para eliminar." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
            if(!formatoNumero(opc)) {
                bandera = false;
            } else {
                if(atoi(opc.c_str()) < 0 or atoi(opc.c_str()) > listaResultado.datosTotales()) {
                    bandera = false;
                } else {
                    bandera = true;
                }
            }
        } while(!bandera);

        if(opc != "0") {
            //Eliminacion en cadena del academico
            Academico academicoDelete;
            academicoDelete = listaResultado[atoi(opc.c_str())];

            //Elimina informacion de Usuario
            ifstream arch_usr(string(DIR) + string(ARCH_USR));
            if(arch_usr.good()) {
                while(!arch_usr.eof()) {
                    Usuario usr;
                    arch_usr.read((char*)&usr, sizeof(Usuario));
                    if(arch_usr.eof()) { break; }
                    if(usr.getNoRegistro() == academicoDelete.getNoReg()) {
                        //cout << endl << "Eliminando al usuario: " << usr.getUsername() << endl;
                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&usr, sizeof(Usuario));
                        escribir.close();
                    }
                }
                arch_usr.close();
                string rm = string(DIR) + string(ARCH_USR);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }
            arch_usr.close();

            //Elimina informacion de academico
            ifstream arch_academico(string(DIR) + string(ARCH_AC));
            if(arch_academico.good()) {
                while(!arch_academico.eof()) {
                    Academico academico;
                    arch_academico.read((char*)&academico, sizeof(Academico));
                    if(arch_academico.eof()) { break; }
                    if(academico.getNoReg() == academicoDelete.getNoReg()) {
                        //cout << endl << "Eliminando al usuario: " << usr.getUsername() << endl;
                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&academico, sizeof(Academico));
                        escribir.close();
                    }
                }
                arch_academico.close();
                string rm = string(DIR) + string(ARCH_AC);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }
            arch_academico.close();

            //Elimina dependientes
            ifstream arch_dep(string(DIR) + string(ARCH_DEPENDIENTE));
            if(arch_dep.good()) {
                while(!arch_dep.eof()) {
                    Dependiente dep;
                    arch_dep.read((char*)&dep, sizeof(Dependiente));
                    if(arch_dep.eof()) { break; }
                    if(dep.getNoReg() == academicoDelete.getNoReg()) {
                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&dep, sizeof(Dependiente));
                        escribir.close();
                    }
                }
                arch_dep.close();
                string rm = string(DIR) + string(ARCH_DEPENDIENTE);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }
            arch_dep.close();

            //Elimina Formacion academica
            ifstream arch_form(string(DIR) + string(ARCH_FORMACION));
            if(arch_form.good()) {
                while(!arch_form.eof()) {
                    Formacion form;
                    arch_form.read((char*)&form, sizeof(Formacion));
                    if(arch_form.eof()) { break; }
                    if(form.getNoReg() == academicoDelete.getNoReg()) {
                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&form, sizeof(Formacion));
                        escribir.close();
                    }
                }
                arch_form.close();
                string rm = string(DIR) + string(ARCH_FORMACION);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }

            //Eliminacion de produccion
            ifstream arch_pro(string(DIR) + string(ARCH_PRODUCCION));
            if(arch_pro.good()) {
                while(!arch_pro.eof()) {
                    Produccion pro;
                    arch_pro.read((char*)&pro, sizeof(Produccion));
                    if(arch_pro.eof()) { break; }
                    if(pro.getNoReg() == academicoDelete.getNoReg()) {
                        //Eliminacion de co-autores
                        ifstream arch_aut(string(DIR) + string(ARCH_AUTOR));
                        if(arch_aut.good()) {
                            while(!arch_aut.eof()) {
                                Autor aut;
                                arch_aut.read((char*)&aut, sizeof(Autor));
                                if(arch_aut.eof()) { break; }
                                if(string(aut.getNoRegistro()) == string(pro.getNoRegistro())) {
                                } else {
                                    ofstream escribir(string(DIR) + "Temp_Autor.txt", ios::app);
                                    escribir.write((char*)&aut, sizeof(Autor));
                                    escribir.close();
                                }
                            }
                            arch_aut.close();
                            string rm = string(DIR) + string(ARCH_AUTOR);
                            string rname = string(DIR) + "Temp_Autor.txt";
                            remove(rm.c_str());
                            rename(rname.c_str(), rm.c_str());
                        }
                        arch_aut.close();

                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&pro, sizeof(Produccion));
                        escribir.close();
                    }
                }
                arch_pro.close();
                string rm = string(DIR) + string(ARCH_PRODUCCION);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }
            arch_pro.close();

            //Eliminacion de docencia
            ifstream arch_doc(string(DIR) + string(ARCH_DOCENCIA));
            if(arch_doc.good()) {
                while(!arch_doc.eof()) {
                    Docencia doc;
                    arch_doc.read((char*)&doc, sizeof(Docencia));
                    if(arch_doc.eof()) { break; }
                    if(doc.getNoReg() == academicoDelete.getNoReg()) {
                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&doc, sizeof(Docencia));
                        escribir.close();
                    }
                }
                arch_doc.close();
                string rm = string(DIR) + string(ARCH_DOCENCIA);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }
            arch_doc.close();

            //Elimina Tutoria
            ifstream arch_tut(string(DIR) + string(ARCH_TUTORIA));
            if(arch_tut.good()) {
                while(!arch_tut.eof()) {
                    Tutoria tut;
                    arch_tut.read((char*)&tut, sizeof(Tutoria));
                    if(arch_tut.eof()) { break; }
                    if(tut.getNoReg() == academicoDelete.getNoReg()) {
                    } else {
                        ofstream escribir(string(DIR) + "Temporal.txt", ios::app);
                        escribir.write((char*)&tut, sizeof(Tutoria));
                        escribir.close();
                    }
                }
                arch_tut.close();
                string rm = string(DIR) + string(ARCH_TUTORIA);
                string rname = string(DIR) + "Temporal.txt";
                remove(rm.c_str());
                rename(rname.c_str(), rm.c_str());
            }
            arch_tut.close();
        } else {
            cout << endl << "Cancelación de eliminación..." << endl;
        }
        listaResultado.eliminarNodos();
    }
}

void MenuAdmin::administrarProduccion() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administracion de producciones ***" << endl << endl;
        cout << "1) Mostrar producción." << endl;
        cout << "2) Modificar producción." << endl;
        cout << "3) Eliminar producción." << endl;
        cout << "0) Salir..." << endl<< endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "0");
        if(opc == "1") {
            system(CLEAR);
            cout << "*** Mostrar todas las publicaciones ***" << endl << endl;
            ifstream file(string(DIR) + string(ARCH_PRODUCCION));
            if(!file.good()) {
                file.close();
                ofstream file_pro(string(DIR) + string(ARCH_PRODUCCION));
                file_pro.close();
                cout << "ERROR. No existe el archivo. Creando archivo...";
                return;
            }
            bool bandera = false;
            while(!file.eof()) {
                Produccion pro;
                file.read((char*)&pro, sizeof(Produccion));
                if(file.eof()) { break; }
                //Busca si existe el nombre de dependiente
                bandera = true;
                ifstream arch_ac(string(DIR) + string(ARCH_AC));
                if(!arch_ac.good()){
                    return;
                }
                Academico ac;
                while(!arch_ac.eof()){
                    arch_ac.read((char*)&ac, sizeof(Academico));
                    if(arch_ac.eof()){ break; }
                    if(ac.getNoReg() == pro.getNoReg()){
                        cout << "Académico: " << ac.getNombre() << endl;
                        break;
                    }
                }
                arch_ac.close();
                cout << "Titulo: " << pro.getTipo() << " " << pro.getNombre() << endl;
                cout << "Fecha de elaboración: " << pro.getFechaElaboracion().toString() << endl;
                cout << "No. Registro: " << pro.getNoRegistro() << " -> Status: " << pro.getStatus() << endl;
                cout << "-----Co-Autores-----" << endl;

                ifstream file_aut(string(DIR) + string(ARCH_AUTOR));
                if(!file_aut.good()) {
                    file_aut.close();
                    ofstream file_pro(string(DIR) + string(ARCH_PRODUCCION));
                    file_pro.close();
                    cout << "ERROR. No existe el archivo. Creando archivo...";
                } else {
                    bool existe = false;
                    while(!file_aut.eof()) {
                        Autor aut;
                        file_aut.read((char*)&aut, sizeof(Autor));
                        if(file_aut.eof()) {
                            break;
                        }
                        if(string(aut.getNoRegistro()) == string(pro.getNoRegistro())) {
                            cout << "Nombre: " << aut.getNombre() << endl;
                            existe = true;
                        }
                    }
                    if(!existe) {
                        cout << "La produccion no tiene coperación de otros autores." << endl;
                    }
                    file_aut.close();
                }
                cout << endl;
            }
            file.close();
            if(!bandera) {
                cout << "No hay producciones registradas." << endl;
            }
        } else if(opc == "2") {
            system(CLEAR);
            string nombre;
            cout << "*** Modificar producción académica ***" << endl << endl;
            cout << "Ingrese el nombre (Completo o parcial) la producción: ";
            getline(cin, nombre);
            ListaProduccion listaResultado;
            ifstream arch_pro(string(DIR) + string(ARCH_PRODUCCION));
            if(!arch_pro.good()){
                arch_pro.close();
                cout << "No existen producciones registrados." << endl;
                return;
            }
            while(!arch_pro.eof()) {
                Produccion pro;
                arch_pro.read((char*)&pro, sizeof(Produccion));
                if(arch_pro.eof()) { break; }
                if(strstr(pro.getNombre(), nombre.c_str()))  {
                    listaResultado.insertar(listaResultado.ultimaPos(), pro);
                }
            }
            arch_pro.close();

            if(listaResultado.estaVacia()){
                cout << "No hubieron coincidencias con las producciones." << endl;
            }
            else{
                for(int i = 1; i < listaResultado.datosTotales(); i++){
                    Produccion pro;
                    pro = listaResultado[i];
                    cout << i << " -> " << pro.getTipo() << " " << pro.getNombre() << endl;
                    //Busqueda del autor
                    ifstream arch_ac(string(DIR) + string(ARCH_AC));
                    if(!arch_ac.good()){return;}
                    while(!arch_ac.eof()){
                        Academico ac;
                        arch_ac.read((char*)&ac, sizeof(Academico));
                        if(arch_ac.eof()){ break; }
                        if(ac.getNoReg() == pro.getNoReg()){
                            cout << "Académico: " << ac.getNombre() << endl;
                            break;
                        }
                    }
                    cout << endl;
                }
                bool bandera = false;
                cout << "0-> No modificar nada..." << endl;
                cout << "Elija una producción para modificar." << endl << endl;
                do {
                    cout << ">> ";
                    getline(cin, opc);
                    if(!formatoNumero(opc)) {
                        bandera = false;
                    } else {
                        if(atoi(opc.c_str()) < 0 or atoi(opc.c_str()) > listaResultado.datosTotales()) {
                            bandera = false;
                        } else {
                            bandera = true;
                        }
                    }
                } while(!bandera);
                if(opc != "0") {
                    system(CLEAR);
                    Produccion aux;
                    aux = listaResultado[atoi(opc.c_str())];
                    Produccion pro;
                    long int posArchivo = 0;
                    //Busca al dependiente dentro del archivo
                    fstream file_out(string(DIR) + string(ARCH_PRODUCCION), ios::in|ios::out);
                    while(!file_out.eof()) {
                        file_out.read((char*)&pro, sizeof(Produccion));
                        if(file_out.eof()) { break; }
                        //Rompe el ciclo cuando encuentra la formacion para modificarla
                        if(string(pro.getTipo()) == string(aux.getTipo()) and string(pro.getNombre()) == string(aux.getNombre())
                                and pro.getNoReg() == aux.getNoReg()) {
                            //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                            posArchivo = file_out.tellg();
                            posArchivo -= sizeof(Produccion);
                            break;
                        }
                    }
                    file_out.close();

                    //Obtiene el academico del archivo
                    Academico ac;
                    ifstream arch_ac(string(DIR) + string(ARCH_AC));
                    if(!arch_ac.good()) { return; }
                    while(!arch_ac.eof()){
                        arch_ac.read((char*)&ac, sizeof(Academico));
                        if(ac.getNoReg() == pro.getNoReg()){
                            break;
                        }
                    }
                    arch_ac.close();

                    string opc;
                    do {
                        system(CLEAR);
                        cout << "*** Modificación de la producción -> " << pro.getTipo() << " " << pro.getNombre() << " ***" << endl << endl;
                        cout << "1) Tipo." << endl;
                        cout << "2) Nombre" << endl;
                        cout << "3) Fecha de elaboración." << endl;
                        cout << "4) Número de registro." << endl;
                        cout << "5) Status." << endl;
                        cout << "6) Colaboradores." << endl;
                        cout << "0) Salir..." << endl << endl;
                        do {
                            cout << ">> ";
                            getline(cin, opc);
                        } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "5" and opc != "6");
                        if(opc == "1") {
                            string opcion, tipo;
                            cout << "Elija el tipo de producción." << endl;
                            cout << "1) Capitulo de libro." << endl;
                            cout << "2) Libro." << endl;
                            cout << "3) Informe." << endl;
                            cout << "4) Artículo." << endl;
                            cout << "5) Desarrollo de software." << endl << endl;
                            do {
                                cout << ">> ";
                                getline(cin, opcion);
                            } while(opcion != "1" and opcion != "2" and opcion != "3" and opcion != "4" and opcion != "5");
                            if(opcion == "1") {
                                tipo = "Capitulo de libro";
                            } else if(opcion == "2") {
                                tipo = "Libro";
                            } else if(opcion == "3") {
                                tipo = "Informe";
                            } else if(opcion == "4") {
                                tipo = "Artículo";
                            } else {
                                tipo = "Desarrollo de software";
                            }

                            if(existeProduccion(tipo, pro.getNombre(), ac)) {
                                cout << endl << "La producción que intenta agregar ya existe. Es imposible registrarla." << endl;
                            } else {
                                pro.setTipo(tipo);
                            }
                        } else if (opc == "2") {
                            string nombre;
                            cout << "Ingrese el nombre de la producción: ";
                            getline(cin, nombre);
                            if(existeProduccion(pro.getTipo(), nombre, ac)) {
                                cout << endl << "La producción que intenta agregar ya existe. Es imposible registrarla." << endl;
                            } else {
                                pro.setNombre(nombre);
                            }
                        } else if (opc == "3") {
                            string fecha;
                            Fecha fechaElab;
                            do {
                                cout << "Ingrese la fecha de elaboracion (Formato DD/MM/AAAA): ";
                                getline(cin, fecha);
                                if(!fechaCorrecta(fecha)) {
                                    cout << "El formato de fecha es incorrecto. Intente de nuevo." << endl << endl;
                                }
                            } while(!fechaCorrecta(fecha));
                            fechaElab = regresaFecha(fecha);
                            pro.setFechaElaboracion(fechaElab);
                        } else if (opc == "4") {
                            string noRegistro;
                            bool existe = false;
                            do {
                                cout << "Ingrese el número de registro de la producción: ";
                                getline(cin, noRegistro);
                                if(existeNoRegProduccion(noRegistro, ac)) {
                                    cout << "El número de registro que intenta ingresar ya existe. Intente de nuevo." << endl << endl;
                                    existe = true;
                                } else {
                                    existe = false;
                                }
                            } while(existe);
                            //Modifica la relación con los autores para que no se pierda concordancia de datos
                            Autor aut;
                            fstream file_out(string(DIR) + string(ARCH_AUTOR), ios::in|ios::out);
                            while(!file_out.eof()) {
                                file_out.read((char*)&aut, sizeof(Autor));
                                if(file_out.eof()) { break; }
                                //Rompe el ciclo cuando encuentra la formacion para modificarla
                                if(string(pro.getNoRegistro()) == string(aut.getNoRegistro()) and string(aut.getNombre()) == nombre) {
                                    //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                                    aut.setNoRegistro(noRegistro);
                                    guardaAutor(aut, string(DIR) + "Temporal_autor.txt");
                                } else {
                                    guardaAutor(aut, string(DIR) + "Temporal_autor.txt");
                                }
                            }
                            file_out.close();
                            string rem = string(DIR) + string(ARCH_AUTOR);
                            string rena = string(DIR) + "Temporal_autor.txt";
                            remove(rem.c_str());
                            rename(rena.c_str(), rem.c_str());
                            //Finalmente asigna el dato al objeto
                            pro.setNoRegistro(noRegistro);
                        } else if (opc == "5") {
                            string status, opc;
                            cout << endl << "Elija el status actual de la producción." << endl;
                            cout << "1) Aceptado." << endl;
                            cout << "2) En proceso." << endl;
                            cout << "3) Publicado." << endl << endl;
                            do {
                                cout << ">> ";
                                getline(cin, opc);
                            } while(opc != "1" and opc != "2" and opc != "3");
                            if(opc == "1") {
                                status = "Aceptado";
                            } else if(opc == "2") {
                                status = "En proceso";
                            } else {
                                status = "Publicado";
                            }
                            pro.setStatus(status);
                        } else if (opc == "6") {
                            string opc;
                            do {
                                system(CLEAR);
                                cout << "*** Administración de colaboradores, producción " << pro.getTipo() << " " << pro.getNombre() << " ***" << endl << endl;
                                cout << "1) Agregar autor." << endl;
                                cout << "2) Modificar autor." << endl;
                                cout << "3) Eliminar autor." << endl;
                                cout << "0) Salir..." << endl << endl;
                                do {
                                    cout << ">> ";
                                    getline(cin, opc);
                                } while(opc != "0" and opc != "1" and opc != "2" and opc != "3");
                                if(opc == "1") {
                                    string nombre;
                                    cout << "Ingrese el nombre del autor a ingresar: ";
                                    getline(cin, nombre);
                                    if(existeAutor(nombre, string(pro.getNoRegistro()))) {
                                        cout << "Autor existente. Imposible de registrar";
                                    } else {
                                        Autor aut;
                                        aut.setNombre(nombre);
                                        aut.setNoRegistro(string(pro.getNoRegistro()));
                                        guardaAutor(aut, string(DIR) + string(ARCH_AUTOR));
                                    }
                                } else if(opc == "2") {
                                    string nombre;
                                    cout << "Ingrese el nombre del autor a modificar: ";
                                    getline(cin, nombre);
                                    if(existeAutor(nombre, string(pro.getNoRegistro()))) {
                                        Autor aut;
                                        long int posArchivo = 0;
                                        //Busca al dependiente dentro del archivo
                                        fstream file_out(string(DIR) + string(ARCH_AUTOR), ios::in|ios::out);
                                        while(!file_out.eof()) {
                                            file_out.read((char*)&aut, sizeof(Autor));
                                            if(file_out.eof()) { break; }
                                            //Rompe el ciclo cuando encuentra la formacion para modificarla
                                            if(string(pro.getNoRegistro()) == string(aut.getNoRegistro()) and string(aut.getNombre()) == nombre) {
                                                //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                                                posArchivo = file_out.tellg();
                                                posArchivo -= sizeof(Autor);
                                                break;
                                            }
                                        }
                                        file_out.close();
                                        string opc;
                                        do {
                                            system(CLEAR);
                                            cout << "*** Administración del autor " << aut.getNombre() << " ***" << endl << endl;
                                            cout << "1) Cambiar nombre." << endl;
                                            cout << "0) Salir..." << endl << endl;
                                            do {
                                                cout << ">> ";
                                                getline(cin, opc);
                                            } while(opc != "0" and opc != "1");
                                            if(opc == "1") {
                                                string nombre;
                                                cout << "Ingrese el nombre del autor: ";
                                                getline(cin, nombre);
                                                if(existeAutor(nombre, string(pro.getNoRegistro()))) {
                                                    cout << endl <<"El autor ya existe. Es imposible registrar el nuevo nombre.";
                                                } else {
                                                    aut.setNombre(nombre);
                                                }
                                            } else {
                                                fstream file(string(DIR) + string(ARCH_AUTOR), ios::in|ios::out);
                                                file.seekg(posArchivo, ios::beg);
                                                file.write((char*)& aut, sizeof(Autor));
                                                file.close();
                                                cout << endl << "Modificación terminada para el autor...";
                                            }
                                        } while(opc != "0");
                                    } else {
                                        cout << endl << "No existe el autor";
                                    }
                                } else if(opc == "3") {
                                    string nombre;
                                    cout << "Ingrese el nombre del autor a eliminar: ";
                                    getline(cin, nombre);
                                    if(existeAutor(nombre, string(pro.getNoRegistro()))) {
                                        Autor aut;
                                        //Busca al dependiente dentro del archivo
                                        ifstream file_out(string(DIR) + string(ARCH_AUTOR));
                                        while(!file_out.eof()) {
                                            file_out.read((char*)&aut, sizeof(Autor));
                                            if(file_out.eof()) { break; }
                                            //Rompe el ciclo cuando encuentra la formacion para modificarla
                                            if(string(pro.getNoRegistro()) == string(aut.getNoRegistro()) and string(aut.getNombre()) == nombre) {
                                                //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                                                cout << endl << "Eliminando: " << aut.getNombre() << endl;
                                            } else {
                                                guardaAutor(aut, string(DIR) + "Temporal_autor.txt");
                                            }
                                        }
                                        file_out.close();
                                        string rem = string(DIR) + string(ARCH_AUTOR);
                                        string rena = string(DIR) + "Temporal_autor.txt";
                                        remove(rem.c_str());
                                        rename(rena.c_str(), rem.c_str());
                                    } else {
                                        cout << endl << "No existe el autor";
                                    }
                                } else {
                                    cout << endl << "Administración de autores terminada.";
                                }
                                if(opc != "0"){
                                    pausa();
                                }
                            } while(opc != "0");
                        } else {
                            //Sobreescribe la produccion
                            fstream file(string(DIR) + string(ARCH_PRODUCCION), ios::in|ios::out);
                            file.seekg(posArchivo, ios::beg);
                            file.write((char*)& pro, sizeof(Produccion));
                            file.close();
                            cout << endl << "Modificación completa de la producción.";
                        }
                        if(opc != "0"){
                            pausa();
                        }
                    } while(opc != "0");
                }
                else{
                    cout << "Cancelación de modificación...." << endl;
                }
                listaResultado.eliminarNodos();

            }
        } else if(opc == "3") {
            system(CLEAR);
            string nombre;
            cout << "*** Eliminar producción académica ***" << endl << endl;
            cout << "Ingrese el nombre (Completo o parcial) la producción: ";
            getline(cin, nombre);

            ListaProduccion listaResultado;
            ifstream arch_pro(string(DIR) + string(ARCH_PRODUCCION));
            if(!arch_pro.good()){
                arch_pro.close();
                cout << "No existen producciones registrados." << endl;
                return;
            }

            while(!arch_pro.eof()) {
                Produccion pro;
                arch_pro.read((char*)&pro, sizeof(Produccion));
                if(arch_pro.eof()) { break; }
                if(strstr(pro.getNombre(), nombre.c_str()))  {
                    listaResultado.insertar(listaResultado.ultimaPos(), pro);
                }
            }
            arch_pro.close();

            if(listaResultado.estaVacia()){
                cout << "No hubieron coincidencias con las producciones." << endl;
            }
            else{
                for(int i = 1; i < listaResultado.datosTotales(); i++){
                    Produccion pro;
                    pro = listaResultado[i];
                    cout << i << " -> " << pro.getTipo() << " " << pro.getNombre() << endl;
                    //Busqueda del autor
                    ifstream arch_ac(string(DIR) + string(ARCH_AC));
                    if(!arch_ac.good()){return;}
                    while(!arch_ac.eof()){
                        Academico ac;
                        arch_ac.read((char*)&ac, sizeof(Academico));
                        if(arch_ac.eof()){ break; }
                        if(ac.getNoReg() == pro.getNoReg()){
                            cout << "Académico: " << ac.getNombre() << endl;
                            break;
                        }
                    }
                    cout << endl;
                }
                bool bandera = false;
                cout << "0-> No eliminar nada..." << endl;
                cout << "Elija una producción para eliminar." << endl << endl;
                do {
                    cout << ">> ";
                    getline(cin, opc);
                    if(!formatoNumero(opc)) {
                        bandera = false;
                    } else {
                        if(atoi(opc.c_str()) < 0 or atoi(opc.c_str()) > listaResultado.datosTotales()) {
                            bandera = false;
                        } else {
                            bandera = true;
                        }
                    }
                } while(!bandera);
                if(opc != "0") {
                    //Proceso de eliminación del archivo
                    Produccion prodDelete;
                    prodDelete = listaResultado[atoi(opc.c_str())];

                    string noRegistro;
                    ifstream file_out(string(DIR) + string(ARCH_PRODUCCION));
                    while(!file_out.eof()) {
                        Produccion pro;
                        file_out.read((char*)&pro, sizeof(Produccion));
                        if(file_out.eof()) { break; }
                        //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                        if(string(pro.getTipo()) == string(prodDelete.getTipo()) and string(pro.getNombre()) == string(prodDelete.getNombre())
                            and pro.getNoReg() == prodDelete.getNoReg()) {
                            cout << "Eliminando: " << pro.getTipo() << " " << pro.getNombre() << endl;
                            noRegistro = pro.getNoRegistro();
                        } else {
                            guardaProduccion(pro, string(DIR) + "Temporal.txt");
                        }
                    }
                    file_out.close();

                    //Eliminacion del archivo viejo y sustitucion por el nuevo
                    string rem = string(DIR) + string(ARCH_PRODUCCION);
                    string rena = string(DIR) + "Temporal.txt";
                    remove(rem.c_str());
                    rename(rena.c_str(), rem.c_str());
                    cout << "Se elimino la producción exitosamente.";

                    //Eliminacion de los autores de la produccion
                    fstream file_aut(string(DIR) + string(ARCH_AUTOR));
                    if(!file_aut.good()) {
                        cout << "No se abrio el archivo";
                    }
                    while(!file_aut.eof()) {
                        Autor aut;
                        file_aut.read((char*)&aut, sizeof(Autor));
                        if(file_aut.eof()) {
                            break;
                        }
                        if(noRegistro != string(aut.getNoRegistro())) {
                            guardaAutor(aut, string(DIR) +  "Temporal_autor.txt");
                        }
                    }
                    file_aut.close();
                    rem = string(DIR) + string(ARCH_AUTOR);
                    rena = string(DIR) + "Temporal_autor.txt";
                    remove(rem.c_str());
                    rename(rena.c_str(), rem.c_str());

                    cout << endl << "Producción eliminada." << endl;
                } else {
                    cout << endl << "Cancelación de eliminación..." << endl;
                }
                listaResultado.eliminarNodos();
            }

        } else {
            cout << endl << endl << "Gracias por usar el administrador de producciones...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuAdmin::pausa() {
    cout << endl << endl << "Presione [enter] para continuar...." << endl;
    cin.ignore();
}

bool MenuAdmin::existeUsername(const std::string& username) {
    ifstream file(string(DIR) + string(ARCH_USR));
    if(!file.good()) {
        file.close();
        ofstream file_usr(string(DIR) + string(ARCH_USR));
        file_usr.close();
        return false;
    }
    bool resultado = false;
    while(!file.eof()) {
        Usuario usr;
        file.read((char*)&usr, sizeof(Usuario));
        if(file.eof()) {
            break;
        }

        if(usr.getUsername() == username) {
            resultado = true;
            break;
        }
    }
    file.close();
    return resultado;
}

void MenuAdmin::insertarUsuario(Usuario& usuario) {
    //Crea el registro dentro del archivo de academicos
    Academico academico;
    academico.setNoReg(this->noReg);
    academico.setNombre(std::string(usuario.getUsername()));
    ofstream arch_ac(string(DIR) + string(ARCH_AC), ios::app);
    long int direccionFisica = arch_ac.tellp();
    arch_ac.write((char*)&academico, sizeof(Academico));
    arch_ac.close();

    //Toma el valor de la posicion física del academico y la asigna al usuario
    usuario.setDireccionFisica(direccionFisica);
    ofstream arch_usr(string(DIR) + string(ARCH_USR), ios::app);
    arch_usr.write((char*)&usuario, sizeof(Usuario));
    arch_usr.close();

    //Sobreescribe el valor del no de registros
    ofstream file_reg(string(DIR) + string(ARCH_NO_REG));
    file_reg.write((char*)&this->noReg, sizeof(int));
    file_reg.close();
}

bool MenuAdmin::formatoNumero(const std::string& numero) {
    regex rx("[0-9]+");
    if(regex_match(numero, rx)) {
        return true;
    }
    return false;
}

bool MenuAdmin::formatoEmail(const std::string& email) {
    regex rx("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(regex_match(email, rx)) {
        return true;
    }
    return false;
}

void MenuAdmin::guardaDependiente(Dependiente& dep, const std::string& archivo) {
    //Guarda dentro del archivo el objeto
    ofstream file(archivo, ios::app);
    file.write((char*) &dep, sizeof(Dependiente));
    file.close();
}

bool MenuAdmin::existeDependiente(const std::string& nombre, Academico &ac) {
    ifstream file(string(DIR) + string(ARCH_DEPENDIENTE));
    if(!file.good()) {
        file.close();
        ofstream file_dep(string(DIR) + string(ARCH_DEPENDIENTE));
        file_dep.close();
        return false;
    }
    while(!file.eof()) {
        Dependiente dep;
        file.read((char*)&dep, sizeof(Dependiente));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de dependiente por el usuario
        if(string(dep.getNombre()) == nombre and dep.getNoReg() == ac.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool MenuAdmin::fechaCorrecta(const std::string& fecha) {
    regex rx("[0-9]{2}/[0-9]{2}/[0-9]{4}");
    if(regex_match(fecha, rx)) {
        return true;
    }
    return false;
}

Fecha MenuAdmin::regresaFecha(std::string& fecha) {
    Fecha auxFecha;
    string auxString;
    unsigned int i;
    auxString = "";
    for(i = 0; fecha[i] != '/'; i++) {
        auxString += fecha[i];
    }
    auxFecha.setDia(atoi(auxString.c_str()));
    auxString = "";
    for(i = i + 1; fecha[i] != '/'; i++) {
        auxString += fecha[i];
    }
    auxFecha.setMes(atoi(auxString.c_str()));
    auxString = "";
    for(i = i + 1; i < fecha.length(); i++) {
        auxString += fecha[i];
    }
    auxFecha.setAnio(atoi(auxString.c_str()));
    return auxFecha;
}

void MenuAdmin::guardaFormacion(Formacion& form, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &form, sizeof(Formacion));
    file.close();
}

bool MenuAdmin::existeFormacion(const std::string& tipo, const std::string& nombre, Academico &ac) {
    ifstream file(string(DIR) + string(ARCH_FORMACION));
    if(!file.good()) {
        file.close();
        ofstream file_form(string(DIR) + string(ARCH_FORMACION));
        file_form.close();
        return false;
    }
    while(!file.eof()) {
        Formacion form;
        file.read((char*)&form, sizeof(Formacion));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de formación
        if(string(form.getTipo()) == tipo and string(form.getNombre()) == nombre and form.getNoReg() == ac.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuAdmin::guardaDocencia(Docencia& doc, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &doc, sizeof(Docencia));
    file.close();
}

bool MenuAdmin::existeDocencia(const std::string& nombre, Academico &ac) {
    ifstream file(string(DIR) + string(ARCH_DOCENCIA));
    if(!file.good()) {
        file.close();
        ofstream file_doc(string(DIR) + string(ARCH_DOCENCIA));
        file_doc.close();
        return false;
    }
    while(!file.eof()) {
        Docencia doc;
        file.read((char*)&doc, sizeof(Docencia));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de formación
        if(string(doc.getNombre()) == nombre and doc.getNoReg() == ac.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuAdmin::guardaTutoria(Tutoria& tut, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &tut, sizeof(Tutoria));
    file.close();
}

bool MenuAdmin::existeTutoria(const std::string& nombreTutorado, Academico &ac) {
    ifstream file(string(DIR) + string(ARCH_TUTORIA));
    if(!file.good()) {
        file.close();
        ofstream file_tut(string(DIR) + string(ARCH_TUTORIA));
        file_tut.close();
        return false;
    }
    while(!file.eof()) {
        Tutoria tut;
        file.read((char*)&tut, sizeof(Tutoria));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de formación
        if(string(tut.getNombreTutorado()) == nombreTutorado and tut.getNoReg() == ac.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuAdmin::guardaProduccion(Produccion& pro, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &pro, sizeof(Produccion));
    file.close();
}

bool MenuAdmin::existeProduccion(const std::string& tipo, const std::string& nombre, Academico &ac) {
    ifstream file(string(DIR) + string(ARCH_PRODUCCION));
    if(!file.good()) {
        file.close();
        ofstream file_prod(string(DIR) + string(ARCH_PRODUCCION));
        file_prod.close();
        return false;
    }
    while(!file.eof()) {
        Produccion pro;
        file.read((char*)&pro, sizeof(Produccion));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de formación
        if(string(pro.getTipo()) == tipo and string(pro.getNombre()) == nombre and pro.getNoReg() == ac.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool MenuAdmin::existeNoRegProduccion(const std::string& noRegistro, Academico &ac) {
    ifstream file(string(DIR) + string(ARCH_PRODUCCION));
    if(!file.good()) {
        file.close();
        ofstream file_prod(string(DIR) + string(ARCH_PRODUCCION));
        file_prod.close();
        return false;
    }
    while(!file.eof()) {
        Produccion pro;
        file.read((char*)&pro, sizeof(Produccion));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de formación
        if(string(pro.getNoRegistro()) == noRegistro and pro.getNoReg() == ac.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuAdmin::guardaAutor(Autor& aut, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &aut, sizeof(Autor));
    file.close();
}

bool MenuAdmin::existeAutor(const std::string& nombre, const std::string& noRegistro) {
    ifstream file(string(DIR) + string(ARCH_AUTOR));
    if(!file.good()) {
        file.close();
        ofstream file_aut(string(DIR) + string(ARCH_AUTOR));
        file_aut.close();
        return false;
    }
    while(!file.eof()) {
        Autor aut;
        file.read((char*)&aut, sizeof(Autor));
        if(file.eof()) {
            break;
        }
        //Busca si existe el nombre de formación
        if(string(aut.getNombre()) == nombre and aut.getNoRegistro() == noRegistro) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
