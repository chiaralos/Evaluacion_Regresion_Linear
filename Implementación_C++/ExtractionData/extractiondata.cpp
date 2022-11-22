#include "extractiondata.h"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <list>
#include <vector>
#include <fstream>


/*Primera función miembro:
 * Lectura del fichero csv.
 * Se almacena en un vector de vectores del tipo string*/
std::vector<std::vector<std::string>> ExtractionData::LeerCSV()
{
    /* En primer lugar se abre y almacena el ficehero en un buffer temporal "archivo" */
    std::fstream archivo(dataset);
    /* Se crea un vector de vectores del tipo string*/
    std::vector<std::vector<std::string>> datosString;

    /* Idea: Recorrer cada linea del fichero y enviarla como vector al vector de vectores del tipo string*/
    std::string linea = "";
    while(getline(archivo,linea)){
        std::vector<std::string> vector;
        /*Se identifica cada elemento que compone el vector*/
        //Se divide o segmenta cada elemento con boost
        boost::algorithm::split(vector,linea,boost::is_any_of(delimitador));
        /*Finalmente se ingresa al buffer temporal*/
        datosString.push_back(vector);
    }
    /* Se cierra el fichero csv */
    archivo.close();
    /* Se retorna el vector de vectores*/
    return datosString;
}

/* Segunda función miembro:
 * Pasar el vector de vectores del tipo string a un objeto del tipo Eigen: para las correspondientes operaciones*/
Eigen::MatrixXd ExtractionData::CSVtoEigen(
        std::vector<std::vector<std::string>> dataSet,
        int filas,
        int columnas){
    /* Se revisa si tiene o no cabecera*/
    if(header==true){
        filas = filas - 1;
    }
    Eigen::MatrixXd matriz(columnas,filas);
    //Se llena la matriz con los datos del dataSet
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
           //Se pasa a flotante el tipo string
            matriz(j,i) = atof(dataSet[i][j].c_str());
        }
    }
    //Se retorna la matriz traspuesta
    return matriz.transpose();
}

/*Función para extraer el promedio:
 * Cuando el programador no
 * esta seguro cuál es el tipo de dato
 * a retornar, se coloca auto "nombre de la función"
 * decltxypr */

auto ExtractionData::Promedio(Eigen::MatrixXd datos) -> decltype(datos.colwise().mean()){

    return datos.colwise().mean();
}

/*Función para extraer la desviación estandar*/

auto ExtractionData::DevStand (Eigen::MatrixXd datos) -> decltype(((datos.array().square().colwise().sum())/ (datos.rows()-1)).sqrt()){

    return ((datos.array().square().colwise().sum())/ (datos.rows()-1)).sqrt();
}

/*Función para normalizar los datos
 * SE retorna la matriz de datos normalizadas
 * y la función recibe como argumentos, la matriz
 * de datos*/

Eigen::MatrixXd  ExtractionData::Normalizacion (Eigen::MatrixXd datos){
    /*Se calcula el promedio de los datos*/
    /*Se escalan los datos: Xi -mean*/
    //std::cout<<"Prom \n: "<<Promedio(datos)<<"\n"<<std::endl;
    Eigen::MatrixXd matEscalados = datos.rowwise() - Promedio(datos);
    /*SE calcula la desviación estandar de los datos */
    //Se calcula la normalización
    //std::cout<<"Desviación \n: "<<DevStand(matEscalados)<<"\n"<<std::endl;
    Eigen::MatrixXd matNormal = matEscalados.array().rowwise()/DevStand(matEscalados);

    return  matNormal;
}

/*Función para dividir de 4 grandes grupos:
 * X_train
 * y_train
 * X_test
 * y_test
 */
//Tupla: estructura de datos que permite tener diferentes elementos

std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> ExtractionData::TrainTestSplit(Eigen::MatrixXd datos, float sizeTrain){
    //Filas totales
    int filas_totales= datos.rows();
    //Cantidad de filas de entrenamiento
    int filas_train = round(filas_totales * sizeTrain);
    //Cantidad de filas para pruebas
    int filas_test = filas_totales - filas_train;

    Eigen::MatrixXd Train= datos.topRows(filas_train);
    /*SE desprende para dependientes e independientes*/
    Eigen::MatrixXd X_Train= Train.leftCols(datos.cols()-1);
    Eigen::MatrixXd y_Train= Train.rightCols(1);

    Eigen::MatrixXd Test= datos.bottomRows(filas_test);
    /*SE desprende para dependientes e independientes*/
    Eigen::MatrixXd X_Test= Test.leftCols(datos.cols()-1);
    Eigen::MatrixXd y_Test= Test.rightCols(1);

    /*SE compacta la tupla y se retorna*/
    return std::make_tuple(X_Train,y_Train,X_Test,y_Test);

}

/* se creará una función de vector a ficheros*/

void ExtractionData::vectorToFile(std::vector<float> vector,std::string filename){
    std::ofstream fileSalida (filename);
    /*SE crea un iterador para almacenar  la salida del vector*/
    std::ostream_iterator<float> salida_iterador(fileSalida,"\n");
    /*SE copia cada valor desde el inicio hasta el fin del iterador
     * en el fichero*/
    std::copy(vector.begin(),vector.end(),salida_iterador);

}
/*Para efectos de manipulación y visualización se crea la función
 * matriz Eigen A Fichero*/

void ExtractionData::EigenToFile (Eigen::MatrixXd matriz, std::string filename ){
    std::ofstream file_salida (filename);
    if(file_salida.is_open()){
        file_salida << matriz << "\n";
    }
}
