#include "menuusr.h"

MenuUsr::MenuUsr() {
    //ctor
}

MenuUsr::~MenuUsr() {
    //dtor
}

MenuUsr::MenuUsr(const Academico& academico, const Usuario& usuario) {
    //Inicializa con los datos de dos objetos, Usuario contiene la direccion de archivo del Academico
    //para cuando se terminen las modificaciones
    this->academico = academico;
    this->usuario = usuario;
    menuPrincipal();
}

void MenuUsr::menuPrincipal() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Menu del usuario " << this->academico.getNombre() <<" ***" << endl << endl;
        cout << "1) Administrar información personal." << endl;
        cout << "2) Administrar formación académica." << endl;
        cout << "3) Administrar producción académica." << endl;
        cout << "4) Administrar docencia." << endl;
        cout << "5) Administrar tutoria." << endl;
        cout << "6) Configuración." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and opc != "5" and opc != "6" and opc != "0");
        if(opc == "1") {
            infoPersonal();
        } else if(opc == "2") {
            formacion();
        } else if(opc == "3") {
            produccion();
        } else if(opc == "4") {
            docencia();
        } else if(opc == "5") {
            tutoria();
        } else if(opc == "6") {
            configuracion();
        } else {
            cout << endl << "Gracias por usar el administrador de usuario....";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuUsr::infoPersonal() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de información personal - "<< this->academico.getNombre() <<" ***" << endl << endl;
        cout << "1) Actualizar nombre." << endl;
        cout << "2) Actualizar domicilio." << endl;
        cout << "3) Actualizar ciudad." << endl;
        cout << "4) Actualizar telefono." << endl;
        cout << "5) Actualizar email." << endl;
        cout << "6) Actualizar estado civil." << endl;
        cout << "7) Actualizar contraseña." << endl;
        cout << "8) Administrar dependientes economicos." << endl;
        cout << "9) Mostrar información de cuenta." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "2" and opc != "3" and opc != "4" and
                opc != "5" and opc != "6" and opc != "7"  and opc != "8" and
                opc != "9" and opc != "0");
        //Edicion del perfil de usuario
        if(opc == "1") {
            string nombre;
            cout << endl << "Ingrese el nuevo nombre del académico: ";
            getline(cin, nombre);
            this->academico.setNombre(nombre);
            cout << endl << "¡Nombre actualizado!";
        } else if(opc == "2") {
            string domicilio;
            cout << endl << "Ingrese el nuevo domicilio del académico: ";
            getline(cin, domicilio);
            this->academico.setDomicilio(domicilio);
            cout << endl << "¡Domicilio actualizado!";
        } else if(opc == "3") {
            string ciudad;
            cout << endl << "Ingrese la nueva ciudad del académico: ";
            getline(cin, ciudad);
            this->academico.setCiudad(ciudad);
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
            this->academico.setTelefono(telefono);
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
            this->academico.setEmail(email);
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
                this->academico.setEstadoCivil("Soltero");
            } else {
                this->academico.setEstadoCivil("Casado");
            }
            cout << endl << "¡Estado civil actualizado!";
        } else if(opc == "7") {
            string password;
            cout << endl << "Ingrese la nueva contraseña: ";
            getline(cin, password);
            this->usuario.setPassword(password);
        } else if(opc == "8") {
            dependientesEconomicos();
        } else if(opc == "9") {
            system(CLEAR);
            cout << "---------------------------------------------------------------" << endl;
            cout << "Username: " << this->usuario.getUsername() <<  "  ->  Contraseña: " << this->usuario.getPassword()<< endl;
            cout << "Academico: " << this->academico.getNombre() << "    | Email: " << this->academico.getEmail() << endl;
            cout << "Domicilio: " << this->academico.getDomicilio() << " ->  Ciudad: " << this->academico.getCiudad() << endl;
            cout << "Telefono: " << this->academico.getTelefono() << "       | Estado civil: " << this->academico.getEstadoCivil() << endl;
            cout << "---------------------------------------------------------------" << endl;
        } else {
            //Abre el archivo y coloca el puntero en la posicion de escritura para sobreescribir el academico
            fstream file_academico(string(DIR) + string(ARCH_AC), ios::in|ios::out);
            file_academico.seekp(usuario.getDireccionFisica(), ios::beg);
            file_academico.write((char*)&this->academico, sizeof(Academico));
            file_academico.close();

            //Sobre información sobre la cuenta de usuario
            fstream file_usuario(string(DIR) + string(ARCH_USR), ios::in| ios::out);
            long int pos;
            while(!file_usuario.eof()){
                Usuario usr;
                file_usuario.read((char*)& usr, sizeof(Usuario));
                if(file_usuario.eof()){ break; }
                if(string(usr.getUsername()) == string(this->usuario.getUsername())) {
                    pos = file_usuario.tellg();
                    pos -= sizeof(Usuario);
                    file_usuario.seekp(pos, ios::beg);
                    file_usuario.write((char*)& this->usuario, sizeof(Usuario));
                    break;
                }
            }
            file_usuario.close();
            cout << endl << "Terminando de modificar información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuUsr::dependientesEconomicos() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Dependientes económicos de " << this->academico.getNombre() << " ***" << endl << endl;
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
                if(existeDependiente(nombre)) {
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
            dep.setNoReg(this->academico.getNoReg());
            dep.setNombre(nombre);
            dep.setEdad(atoi(edad.c_str()));

            //Guarda dentro del archivo el objeto
            guardaDependiente(dep, string(DIR) + string(ARCH_DEPENDIENTE));

            cout << endl <<"¡Nuevo dependiente agregado exitosamente!";
        } else if(opc == "2") {
            system(CLEAR);
            cout << "*** Mostrando dependientes económicos del academico " << this->academico.getNombre() << " ***" << endl << endl;
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
                if(dep.getNoReg() == this->academico.getNoReg()) {
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
            if(existeDependiente(nombre)) {
                Dependiente dep;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_DEPENDIENTE), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&dep, sizeof(Dependiente));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra al Dependiente para modificarlo
                    if(string(dep.getNombre()) == nombre and dep.getNoReg() == this->academico.getNoReg()) {
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
                            if(existeDependiente(nombre)) {
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
            if(existeDependiente(nombre)) {
                ifstream file_out(string(DIR) + string(ARCH_DEPENDIENTE));
                while(!file_out.eof()) {
                    Dependiente dep;
                    file_out.read((char*)&dep, sizeof(Dependiente));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(dep.getNombre()) == nombre and dep.getNoReg() == this->academico.getNoReg()) {
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

void MenuUsr::formacion() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de la formación académica de - "<< this->academico.getNombre() <<" ***" << endl << endl;
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
            cout << "*** Ingresando formación del académico " << this->academico.getNombre() << " ***" << endl << endl;
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
            if(existeFormacion(tipoGrado, nombreGrado)) {
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
            form.setNoReg(this->academico.getNoReg());
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
            cout << "*** Formación académica actual de " << this->academico.getNombre() << " ***" << endl << endl;
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
                if(form.getNoReg() == this->academico.getNoReg()) {
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
            cout << "*** Modificar formación académica de " << this->academico.getNombre() << " ***" << endl << endl;
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
            if(existeFormacion(tipoGrado, nombreGrado)) {
                Formacion form;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_FORMACION), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&form, sizeof(Formacion));
                    if(file_out.eof()) {
                        break;
                    }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(form.getTipo()) == tipoGrado and string(form.getNombre()) == nombreGrado
                            and form.getNoReg() == this->academico.getNoReg()) {
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
                        if(existeFormacion(tipoGrado, form.getNombre())) {
                            cout << endl << "La formación intenta agregar ya existe. Es imposible registrarla." << endl;
                        } else {
                            form.setTipo(tipoGrado);
                        }
                    } else if (opc == "2") {
                        string nombreGrado;
                        cout << "Ingrese el nombre del grado: ";
                        getline(cin, nombreGrado);
                        if(existeFormacion(form.getTipo(), nombreGrado)) {
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
            cout << "*** Eliminando formación  de " << this->academico.getNombre() << " ***" << endl << endl;
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
            if(existeFormacion(tipoGrado, nombreGrado)) {
                fstream file_out(string(DIR) + string(ARCH_FORMACION));
                while(!file_out.eof()) {
                    //Lee el objeto
                    Formacion form;
                    file_out.read((char*)&form, sizeof(Formacion));
                    //Verifica que el archivo no se haya terminado
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(form.getTipo()) == tipoGrado and string(form.getNombre()) == nombreGrado
                            and form.getNoReg() == this->academico.getNoReg()) {
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

void MenuUsr::produccion() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de la producción académica - "<< this->academico.getNombre() <<" ***" << endl << endl;
        cout << "1) Agregar nueva producción." << endl;
        cout << "2) Mostrar producciones." << endl;
        cout << "3) Modificar producción." << endl;
        cout << "4) Eliminar producción." << endl;
        cout << "0) Salir..." << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "0" and opc != "1" and opc != "2" and opc != "3" and opc != "4");
        if(opc == "1") {

            system(CLEAR);
            string opcion;
            cout << "*** Ingresando producción del académico " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Elija el tipo de producción a crear." << endl;
            cout << "1) Capitulo de libro." << endl;
            cout << "2) Libro." << endl;
            cout << "3) Informe." << endl;
            cout << "4) Artículo." << endl;
            cout << "5) Desarrollo de software." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opcion);
            } while(opcion != "1" and opcion != "2" and opcion != "3" and opcion != "4" and opcion != "5");

            string tipo;
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
            string nombre;
            cout << "Ingrese el nombre de la producción: ";
            getline(cin, nombre);

            if(existeProduccion(tipo, nombre)) {
                cout << "Producción ya existente. Imposible de registrar" << endl;
            } else {

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

                string noRegistro;
                bool existe = false;
                do {
                    cout << "Ingrese el número de registro de la producción: ";
                    getline(cin, noRegistro);
                    if(existeNoRegProduccion(noRegistro)) {
                        cout << "El número de registro que intenta ingresar ya existe. Intente de nuevo." << endl << endl;
                        existe = true;
                    } else {
                        existe = false;
                    }
                } while(existe);

                string status;
                cout << "Elija el status actual de la producción." << endl;
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

                Produccion pro;
                pro.setNoReg(this->academico.getNoReg());
                pro.setTipo(tipo);
                pro.setFechaElaboracion(fechaElab);
                pro.setNombre(nombre);
                pro.setNoRegistro(noRegistro);
                pro.setStatus(status);

                guardaProduccion(pro, string(DIR) + string(ARCH_PRODUCCION));

                cout << endl;
                do {
                    cout << "¿Desea agregar autores a la produccion? (S/N): ";
                    getline(cin, opc);
                } while(opc != "s" and opc != "S" and opc != "n" and opc != "N");
                if(opc == "S" or opc == "s") {
                    do {
                        Autor aut;
                        string nombre;
                        bool existe = false;
                        do {
                            cout << "Ingrese el nombre del autor: ";
                            getline(cin, nombre);
                            if(existeAutor(nombre, string(pro.getNoRegistro()))) {
                                cout << "El autor que intenta ingresar ya existe. Intente de nuevo.";
                                existe = true;
                            } else {
                                existe = false;
                            }
                        } while(existe);
                        aut.setNombre(nombre);
                        aut.setNoRegistro(string(pro.getNoRegistro()));
                        guardaAutor(aut, string(DIR) + string(ARCH_AUTOR));
                        cout << endl <<"¡Nuevo autor agregado exitosamente!" << endl;
                        do {
                            cout << "¿Desea agregar otro autor? (S/N): ";
                            getline(cin, opc);
                        } while(opc != "s" and opc != "S" and opc != "n" and opc != "N");

                    } while(opc == "s" or opc == "S");
                }

                cout << endl <<"¡Nueva producción agregada exitosamente!" << endl;
            }

        } else if(opc == "2") {
            system(CLEAR);
            cout << "*** Producción académica actual de " << this->academico.getNombre() << " ***" << endl << endl;
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
                //Busca si existe el nombre de dependiente por el usuario
                if(pro.getNoReg() == this->academico.getNoReg()) {
                    bandera = true;
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
            }
            file.close();
            if(!bandera) {
                cout << "No hay producción académica para este usuario." << endl;
            }
        } else if(opc == "3") {
            system(CLEAR);
            string opcion;
            cout << "*** Modificar producción del académico " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Elija el tipo de producción y el nombre para modificar." << endl;
            cout << "1) Capitulo de libro." << endl;
            cout << "2) Libro." << endl;
            cout << "3) Informe." << endl;
            cout << "4) Artículo." << endl;
            cout << "5) Desarrollo de software." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opcion);
            } while(opcion != "1" and opcion != "2" and opcion != "3" and opcion != "4" and opcion != "5");

            string tipo;
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
            string nombre;
            cout << "Ingrese el nombre de la producción: ";
            getline(cin, nombre);

            if(existeProduccion(tipo, nombre)) {
                Produccion pro;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_PRODUCCION), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&pro, sizeof(Produccion));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(pro.getTipo()) == tipo and string(pro.getNombre()) == nombre
                            and pro.getNoReg() == this->academico.getNoReg()) {
                        //Toma la posicion en el archivo y la guarda para despues sobreescribir para la modificación
                        posArchivo = file_out.tellg();
                        posArchivo -= sizeof(Produccion);
                        break;
                    }
                }
                file_out.close();
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

                        if(existeProduccion(tipo, pro.getNombre())) {
                            cout << endl << "La producción que intenta agregar ya existe. Es imposible registrarla." << endl;
                        } else {
                            pro.setTipo(tipo);
                        }
                    } else if (opc == "2") {
                        string nombre;
                        cout << "Ingrese el nombre de la producción: ";
                        getline(cin, nombre);
                        if(existeProduccion(pro.getTipo(), nombre)) {
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
                            if(existeNoRegProduccion(noRegistro)) {
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
            } else {
                cout << "Producción inexistente. Es imposible modificar." << endl;
            }
        } else if(opc == "4") {
            system(CLEAR);
            string opcion;
            cout << "*** Eliminar producción del académico " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Elija el tipo de producción y el nombre para eliminar." << endl;
            cout << "1) Capitulo de libro." << endl;
            cout << "2) Libro." << endl;
            cout << "3) Informe." << endl;
            cout << "4) Artículo." << endl;
            cout << "5) Desarrollo de software." << endl << endl;
            do {
                cout << ">> ";
                getline(cin, opcion);
            } while(opcion != "1" and opcion != "2" and opcion != "3" and opcion != "4" and opcion != "5");

            string tipo;
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
            string nombre;
            cout << "Ingrese el nombre de la producción: ";
            getline(cin, nombre);

            if(existeProduccion(tipo, nombre)) {
                string noRegistro;
                ifstream file_out(string(DIR) + string(ARCH_PRODUCCION));
                while(!file_out.eof()) {
                    Produccion pro;
                    file_out.read((char*)&pro, sizeof(Produccion));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(pro.getTipo()) == tipo and string(pro.getNombre()) == nombre and pro.getNoReg() == this->academico.getNoReg()) {
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
            } else {
                cout << "Producción inexistente. Es imposible eliminar." << endl;
            }
        } else {
            cout << endl << "Regresando al menú de administración de información personal...";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuUsr::docencia() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administracion de la docencia - "<< this->academico.getNombre() <<" ***" << endl << endl;
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
            if(existeDocencia(nombre)) {
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
                doc.setNoReg(this->academico.getNoReg());
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
            cout << "*** Docencia académica actual de " << this->academico.getNombre() << " ***" << endl << endl;
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
                if(doc.getNoReg() == this->academico.getNoReg()) {
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
            cout << "*** Modificar materia de " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre de la materia a modificar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeDocencia(nombre)) {
                Docencia doc;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_DOCENCIA), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&doc, sizeof(Docencia));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(doc.getNombre()) == nombre and doc.getNoReg() == this->academico.getNoReg()) {
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
                        if(existeDocencia(nombre)) {
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
            cout << "*** Eliminando materia de " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre de la materia a eliminar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeDocencia(nombre)) {
                ifstream file_out(string(DIR) + string(ARCH_DOCENCIA));
                while(!file_out.eof()) {
                    Docencia doc;
                    file_out.read((char*)&doc, sizeof(Docencia));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(doc.getNombre()) == nombre and doc.getNoReg() == this->academico.getNoReg()) {
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

void MenuUsr::tutoria() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Administración de la tutoria - "<< this->academico.getNombre() <<" ***" << endl << endl;
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
            if(existeTutoria(nombre)) {
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
                tut.setNoReg(this->academico.getNoReg());
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
            cout << "*** Alumnos tutorados de " << this->academico.getNombre() << " ***" << endl << endl;
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
                if(tut.getNoReg() == this->academico.getNoReg()) {
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
            cout << "*** Modificar alumno tutorado de " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre del alumno a modificar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeTutoria(nombre)) {
                Tutoria tut;
                long int posArchivo = 0;
                //Busca al dependiente dentro del archivo
                fstream file_out(string(DIR) + string(ARCH_TUTORIA), ios::in|ios::out);
                while(!file_out.eof()) {
                    file_out.read((char*)&tut, sizeof(Tutoria));
                    if(file_out.eof()) { break; }
                    //Rompe el ciclo cuando encuentra la formacion para modificarla
                    if(string(tut.getNombreTutorado()) == nombre and tut.getNoReg() == this->academico.getNoReg()) {
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
                        if(existeTutoria(nombre)) {
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
            cout << "*** Eliminando alumno tutorado de " << this->academico.getNombre() << " ***" << endl << endl;
            cout << "Ingrese el nombre del alumno a eliminar: ";
            getline(cin, nombre);
            //Verifica si existe la formación académica
            if(existeTutoria(nombre)) {
                ifstream file_out(string(DIR) + string(ARCH_TUTORIA));
                while(!file_out.eof()) {
                    Tutoria tut;
                    file_out.read((char*)&tut, sizeof(Tutoria));
                    if(file_out.eof()) { break; }
                    //Crea el archivo temporal para guardar los registros, menos el que se quiere eliminar
                    if(string(tut.getNombreTutorado()) == nombre and tut.getNoReg() == this->academico.getNoReg()) {
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

void MenuUsr::pausa() {
    cout << endl << "Presione [enter] para continuar..." << endl;
    cin.ignore();
}

void MenuUsr::guardaDependiente(Dependiente& dep, const std::string& archivo) {
    //Guarda dentro del archivo el objeto
    ofstream file(archivo, ios::app);
    file.write((char*) &dep, sizeof(Dependiente));
    file.close();
}

bool MenuUsr::existeDependiente(const std::string& nombre) {
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
        if(string(dep.getNombre()) == nombre and dep.getNoReg() == this->academico.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuUsr::guardaFormacion(Formacion& form, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &form, sizeof(Formacion));
    file.close();
}

bool MenuUsr::existeFormacion(const std::string& tipo, const std::string& nombre) {
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
        if(string(form.getTipo()) == tipo and string(form.getNombre()) == nombre and form.getNoReg() == this->academico.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuUsr::guardaDocencia(Docencia& doc, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &doc, sizeof(Docencia));
    file.close();
}

bool MenuUsr::existeDocencia(const std::string& nombre) {
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
        if(string(doc.getNombre()) == nombre and doc.getNoReg() == this->academico.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuUsr::guardaTutoria(Tutoria& tut, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &tut, sizeof(Tutoria));
    file.close();
}

bool MenuUsr::existeTutoria(const std::string& nombreTutorado) {
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
        if(string(tut.getNombreTutorado()) == nombreTutorado and tut.getNoReg() == this->academico.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuUsr::guardaProduccion(Produccion& pro, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &pro, sizeof(Produccion));
    file.close();
}

bool MenuUsr::existeProduccion(const std::string& tipo, const std::string& nombre) {
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
        if(string(pro.getTipo()) == tipo and string(pro.getNombre()) == nombre and pro.getNoReg() == this->academico.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool MenuUsr::existeNoRegProduccion(const std::string& noRegistro) {
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
        if(string(pro.getNoRegistro()) == noRegistro and pro.getNoReg() == this->academico.getNoReg()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void MenuUsr::guardaAutor(Autor& aut, const std::string& archivo) {
    //Guarda el objeto dentro del archivo
    ofstream file(archivo, ios::app);
    file.write((char*) &aut, sizeof(Autor));
    file.close();
}

bool MenuUsr::existeAutor(const std::string& nombre, const std::string& noRegistro) {
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

void MenuUsr::configuracion() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Configuración del academico " << this->academico.getNombre() << " ***" << endl << endl;
        cout << "1) Exportar información personal." << endl;
        cout << "2) Exportar información de otro academico." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "0" and opc != "1" and opc != "2");
        if(opc == "1") {
            cout << endl << "Exportando información académica..." << endl;
            creaReporte(this->academico);
            cout << endl << "¡Exportación exitosa!" << endl;
        } else if(opc == "2") {
            string nombre;
            cout << endl << "Ingrese el nombre (Completo o parcial) del academico a buscar: ";
            getline(cin, nombre);

            Lista listaResultado;
            ifstream arch_ac(string(DIR) + string(ARCH_AC));
            while(!arch_ac.eof()) {
                Academico ac;
                arch_ac.read((char*)&ac, sizeof(Academico));
                if(arch_ac.eof()) {
                    break;
                }
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
                cout << "0-> No exportar nada..." << endl;
                cout << "Elija un académico para exportar su información." << endl << endl;
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
                    cout << endl << "Exportando información académica..." << endl;
                    creaReporte(listaResultado[atoi(opc.c_str())]);
                    cout << endl << "¡Exportación exitosa!" << endl;
                } else {
                    cout << endl << "Cancelación de reporte..." << endl;
                }
                listaResultado.eliminarNodos();
            }
        } else {
            cout << endl << "Configuración terminada.";
        }
        if(opc != "0") {
            pausa();
        }
    } while(opc != "0");
}

void MenuUsr::creaReporte(Academico& ac) {
    //Creación del archivo a exportar
    ofstream exportacion(string(DIRREP) + string(ac.getNombre()) + ".txt");
    exportacion << "---------------------------------------------------------------" << endl;
    exportacion << "Academico: " << ac.getNombre() << "    | Email: " << ac.getEmail() << endl;
    exportacion << "Domicilio: " << ac.getDomicilio() << " ->  Ciudad: " << ac.getCiudad() << endl;
    exportacion << "Telefono: " << ac.getTelefono() << "       | Estado civil: " << ac.getEstadoCivil() << endl;
    exportacion << "---------------------------------------------------------------" << endl;
    exportacion << "*****************Dependientes economicos***********************" << endl;
    bool existe = false;
    ifstream arch_dep(string(DIR) + string(ARCH_DEPENDIENTE));
    while(!arch_dep.eof()) {
        Dependiente dep;
        arch_dep.read((char*)&dep, sizeof(Dependiente));
        if(arch_dep.eof()) { break; }
        if(dep.getNoReg() == ac.getNoReg()) {
            exportacion << "Nombre: " << dep.getNombre() << " - > Edad: " << dep.getEdad() << endl;
            existe = true;
        }
    }
    arch_dep.close();
    if(!existe) {
        exportacion << "El academico no tiene ningun dependiente economico registrada." << endl;
    }
    exportacion << "---------------------------------------------------------------" << endl;
    exportacion << "*********************Formación académica***********************" << endl;
    existe = false;
    ifstream arch_form(string(DIR) + string(ARCH_FORMACION));
    if(arch_form.good()){
        while(!arch_form.eof()) {
            Formacion form;
            arch_form.read((char*)&form, sizeof(Formacion));
            if(arch_form.eof()) { break; }
            if(form.getNoReg() == ac.getNoReg()) {
                exportacion << form.getTipo() << " " << form.getNombre() << endl;
                exportacion << "Fecha de inicio: " << form.getFechaInicio().toString() << " - > Fecha de fin: " << form.getFechaFinal().toString() << endl;
                exportacion << "Institución de procedencia: " <<form.getInstitucion() << "   | Fecha de obtención: " << form.getFechaObtencion().toString() << endl;
                exportacion << "Número de cedula profesional: " << form.getCedula() << endl << endl;
                existe = true;
            }
        }
        arch_form.close();
        if(!existe) {
            exportacion << "El académico no tiene ninguna formación académica registrada." << endl;
        }
    }
    else{
        exportacion << "El académico no tiene ninguna formación académica registrada." << endl;
    }
    exportacion << "---------------------------------------------------------------" << endl;
    //Exportación de produccion académica
    exportacion << "********************Producción académica***********************" << endl;
    existe = false;
    ifstream arch_pro(string(DIR) + string(ARCH_PRODUCCION));
    if(arch_pro.good()){
        while(!arch_pro.eof()) {
            Produccion pro;
            arch_pro.read((char*)&pro, sizeof(Produccion));
            if(arch_pro.eof()) {
                break;
            }
            if(pro.getNoReg() == ac.getNoReg()) {
                exportacion << pro.getTipo() << " " << pro.getNombre() << endl;
                exportacion << "Fecha de elaboración: " << pro.getFechaElaboracion().toString() << endl;
                exportacion << "No.Registro: " << pro.getNoRegistro() << " -> Status: " << pro.getStatus() << endl;
                exportacion << "--------------------------Co-Autores---------------------------" << endl;
                bool ex = false;
                ifstream arch_aut(string(DIR) + string(ARCH_AUTOR));
                if(arch_aut.good()){
                    while(!arch_aut.eof()) {
                        Autor aut;
                        arch_aut.read((char*)&aut, sizeof(Autor));
                        if(arch_aut.eof()) { break; }
                        if(string(aut.getNoRegistro()) == string(pro.getNoRegistro())) {
                            exportacion << "Nombre: " << aut.getNombre() << endl;
                            ex = true;
                        }
                    }
                    arch_aut.close();
                    if(!ex) {
                        exportacion << "La producción no tiene mas autores." << endl;
                    }
                }
                else{
                    exportacion << "La producción no tiene mas autores." << endl;
                }
                arch_aut.close();

                existe = true;
            }
        }
        arch_pro.close();
        if(!existe) {
            exportacion << "El académico no tiene ninguna producción académica registrada." << endl;
        }
    }
    else{
        exportacion << "El académico no tiene ninguna producción académica registrada." << endl;
    }
    arch_pro.close();

    exportacion << "***************************Docencia****************************" << endl;
    existe = false;
    ifstream arch_doc(string(DIR) + string(ARCH_DOCENCIA));
    if(arch_doc.good()){
        while(!arch_doc.eof()) {
            Docencia doc;
            arch_doc.read((char*)&doc, sizeof(Docencia));
            if(arch_doc.eof()) {
                break;
            }
            if(doc.getNoReg() == ac.getNoReg()) {
                exportacion << "Materia: " << doc.getNombre() << " -> Horas semanales: " << doc.getCantidadHoras() << endl;
                exportacion << "Fecha de inicio: " << doc.getFechaInicio().toString() << " -> Fecha de fin: " << doc.getFechaFin().toString() << endl << endl;
                existe = true;
            }
        }
        arch_doc.close();
        if(!existe) {
            exportacion << "El academico no tiene ninguna docencia registrada." << endl;
        }
    }
    else{
        exportacion << "El academico no tiene ninguna docencia registrada." << endl;
    }
    arch_doc.close();
    exportacion << "---------------------------------------------------------------" << endl;

    exportacion << "***************************Tutorias****************************" << endl;
    existe = false;
    ifstream arch_tut(string(DIR) + string(ARCH_TUTORIA));
    if(arch_tut.good()){
        while(!arch_tut.eof()) {
            Tutoria tut;
            arch_tut.read((char*)&tut, sizeof(Tutoria));
            if(arch_tut.eof()) {
                break;
            }
            if(tut.getNoReg() == ac.getNoReg()) {
                exportacion << "Nombre del alumno tutorado: " << tut.getNombreTutorado() << " -> Horas semanales: " << tut.getCantidadHoras() << endl;
                exportacion << "Fecha de inicio: " << tut.getFechaInicio().toString() << " -> Fecha de fin: " << tut.getFechaFin().toString() << endl << endl;
                existe = true;
            }
        }
        arch_tut.close();
        if(!existe) {
            exportacion << "El académico no tiene ningun alumno tutorado registrado." << endl;
        }
    }
    else{
        exportacion << "El académico no tiene ningun alumno tutorado registrado." << endl;
    }
    arch_tut.close();
    exportacion << "---------------------------------------------------------------" << endl;
    exportacion.close();
}

bool MenuUsr::fechaCorrecta(const std::string& fecha) {
    regex rx("[0-9]{2}/[0-9]{2}/[0-9]{4}");
    if(regex_match(fecha, rx)) {
        return true;
    }
    return false;
}

Fecha MenuUsr::regresaFecha(std::string& fecha) {
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

bool MenuUsr::formatoNumero(const std::string& numero) {
    regex rx("[0-9]+");
    if(regex_match(numero, rx)) {
        return true;
    }
    return false;
}

bool MenuUsr::formatoEmail(const std::string& email) {
    regex rx("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(regex_match(email, rx)) {
        return true;
    }
    return false;
}
