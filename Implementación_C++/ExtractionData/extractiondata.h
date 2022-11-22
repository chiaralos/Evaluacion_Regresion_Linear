#ifndef EXTRACTIONDATA_H
#define EXTRACTIONDATA_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <list>
#include <vector>
#include <fstream>

/* Clase Extracción de Datos:
* - Leer un fichero csv
* - Entrar con argumentos a la clase:
*       - Lugar del dataset (csv)
*       - Separador
*       - Si tiene cabecera o no
* - Pasar a un vector de vectores del tipo string
* - Pasar el vector de vectores string a Eigen
* - Promedio
* - Desviación
* - Normalización
* - Métricas*/

class ExtractionData
{
    /*Argumentos de entrada a la clase*/
    std::string dataset;        //Ruta del dataset
    std::string delimitador;    //Separador entre datos
    bool header;                //Cabecera o no

public:
    /* Se crea el constructor con los argumentos de entrada*/
    //Vector de vectores del tipo string
    ExtractionData(std::string data,
                   std::string separador,
                   bool cabecera):
        dataset(data), delimitador(separador), header(cabecera){}
    /*Prototipo de Métodos/funciones*/
    std::vector<std::vector<std::string>> LeerCSV();
    Eigen::MatrixXd CSVtoEigen(
            std::vector<std::vector<std::string>> dataSet,
            int filas,
            int columnas);
    auto Promedio (Eigen::MatrixXd datos) -> decltype(datos.colwise().mean());
    auto DevStand (Eigen::MatrixXd datos) -> decltype(((datos.array().square().colwise().sum())/ (datos.rows()-1)).sqrt());
    Eigen::MatrixXd Normalizacion (Eigen::MatrixXd datos);
    std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> TrainTestSplit(Eigen::MatrixXd datos, float sizeTrain);
    void vectorToFile(std::vector<float>,std::string filename );
    void EigenToFile (Eigen::MatrixXd matriz, std::string filename );
};

#endif // EXTRACTIONDATA_H
