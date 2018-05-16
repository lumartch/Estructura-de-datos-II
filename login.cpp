#include "login.h"

Login::Login() {
    //Crea el directorio de los archivos por defecto
    system(string(MKDIR).c_str());
    system("mkdir Reportes");
    crearArchivosDefecto();
    menuLogin();
}

void Login::menuLogin() {
    string opc;
    do {
        system(CLEAR);
        cout << "*** Login de Academicos ***" << endl << endl;
        cout << "1) Iniciar sesion." << endl;
        cout << "0) Salir..." << endl << endl;
        do {
            cout << ">> ";
            getline(cin, opc);
        } while(opc != "1" and opc != "0");
        if(opc == "1") {
            Usuario auxUsuario;
            string username, password;
            cout << endl << "Ingrese el username: ";
            getline(cin, username);
            cout << "Ingrese la contraseña: ";
            getline(cin, password);
            buscarUsuario(username, password);
        } else {
            cout << endl << "Gracias por usar el administrador de academicos..." << endl << endl;
        }
        pausa();
    } while(opc != "0");
}

void Login::buscarUsuario(const std::string& username, const std::string& password) {
    ifstream file(string(DIR) + string(ARCH_USR));
    if(!file.good()){
        return;
    }
    //Posible implementacion del arbol paginado, para busquedas de usuarios
    Usuario usuario;
    bool existe = false;
    while(!file.eof()){
        Usuario usr;
        file.read((char*)&usr, sizeof(Usuario));
        if(file.eof()){break;}

        //Si el usuario y la contraseña leidos del archivo, son iguales
        if(string(usr.getUsername()) == username and string(usr.getPassword()) == password){
            usuario = usr;
            existe = true;
        }
    }
    file.close();

    if(existe){
        //Login de usuario existente
        Academico academico;
        ifstream file_academico(string(DIR) + string(ARCH_AC));
        if(!file_academico){
            cout << "No existe el archivo.";
            file_academico.close();
            return;
        }
        else{
            file_academico.seekg(usuario.getDireccionFisica(), ios::beg);
            file_academico.read((char*)&academico, sizeof(Academico));
        }
        file_academico.close();
        if(std::string(usuario.getTipo()) == "Admin"){
            //Inicia menu de administrador
            new MenuAdmin(academico, usuario);
        }
        else{
            //Inicia menu de usuario normal
            new MenuUsr(academico, usuario);
        }
    }
    //Evita Login de usuario inexistente
    else{
        cout << "No existe el usuario. Intente de nuevo." << endl;
    }
}

void Login::crearArchivosDefecto() {
    //Si no existe el archivo crea nuevos archivos
    ifstream archivo_academicos(string(DIR) + string(ARCH_AC));
    ifstream archivo_usuarios(string(DIR) + string(ARCH_USR));
    if(archivo_academicos.good() and archivo_usuarios.good()){
       archivo_academicos.close();
       archivo_usuarios.close();
       return;
    }
    archivo_academicos.close();

    //Crea nuevo academico Administrador en caso de no existir el documento
    ofstream arch_academicos_nuevo(string(DIR) + string(ARCH_AC));
    int noReg = 1;
    Academico ac_admin;
    ac_admin.setNombre("Administrador");
    ac_admin.setNoReg(noReg);
    arch_academicos_nuevo.write((char*)&ac_admin, sizeof(Academico));
    //Toma la direccion física de donde se escribio y lo pasa a la cuenta usuario para que sepa de donde leer
    long int direccionFisica = arch_academicos_nuevo.tellp();
    direccionFisica -= sizeof(Academico);
    arch_academicos_nuevo.close();

    //Crea nuevo usuario Administrador
    Usuario usuario(noReg, "admin", "admin", "Admin", direccionFisica);
    ofstream file_usuario(string(DIR) + string(ARCH_USR));
    file_usuario.write((char*)&usuario, sizeof(Usuario));
    file_usuario.close();

    //Crea el archivo de contador Por si no existia
    ofstream file_reg(string(DIR) + string(ARCH_NO_REG));
    file_reg.write((char*)&noReg, sizeof(int));
    file_reg.close();

    //Crea archivo de dependientes economicos
    ofstream file_dep(string(DIR) + string(ARCH_DEPENDIENTE));
    file_dep.close();

    //Crea archivo de formacion academica
    ofstream file_form(string(DIR) + string(ARCH_FORMACION));
    file_form.close();

    //Crea archivo de docencia academica
    ofstream file_doc(string(DIR) + string(ARCH_DOCENCIA));
    file_doc.close();

    //Crea archivo de tutorias
    ofstream file_tut(string(DIR) + string(ARCH_TUTORIA));
    file_tut.close();

    //Crea archivo de produccion
    ofstream file_prod(string(DIR) + string(ARCH_PRODUCCION));
    file_prod.close();

    //Crea archivo de autores de produccion
    ofstream file_aut(string(DIR) + string(ARCH_AUTOR));
    file_aut.close();
}

void Login::pausa() {
    cout << endl << "Presione [enter] para continuar... " << endl << endl;
    cin.ignore();
}

Login::~Login() {
    //dtor
}
