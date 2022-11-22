/*
* Fecha: 21 sept 2022
* Autor: Chiara Valenzuela
* Materia: HPC
* Tópico: Implementación de la regresión linear como
* modelo en C++
* Requerimientos:
* - Construir una clase Extraction, que permita
* manipular, extraer y cargar los datos
* - Construir una clase LinearRegression, que permita
* los cálculos de la función de costo, gradiente descendiente
* entre otras.*/

#include <iostream>
#include "ExtractionData/extractiondata.h"
#include "LinearRegression/linearregression.h"
#include <eigen3/Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <list>
#include <vector>
#include <fstream>
#define NOMBRE_ARCHIVO "cubic_zirconia_final.csv"

int main()
{
    /* Se crea un objeto del tiop ClasExtraction*/
    ExtractionData ExData(NOMBRE_ARCHIVO,",",false);
    
    // Se instancia la clase de regresión linear en un objeto
    LinearRegression modeloLR;

    /*Se crea un vector de vectores del tipo string para cargar objeto ExData*/
    std::vector<std::vector<std::string>> dataframe = ExData.LeerCSV();

    /*Cantidad de filas y columnas*/
    int filas = dataframe.size();
    int columnas = dataframe[0].size();

    Eigen::MatrixXd matData = ExData.CSVtoEigen(dataframe,filas,columnas);
    
    /*Se normaliza la matriz de datos*/
    Eigen::MatrixXd matNormalizada = ExData.Normalizacion(matData);

    /*Se divide en datos de entrenamiento y en datos de prueba*/
    Eigen::MatrixXd X_Train, y_Train, X_Test,y_Test;
    std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> div_datos = ExData.TrainTestSplit(matNormalizada,0.8);

    /*Se descomprime la tupla en 4 conjuntos */
    std:: tie (X_Train, y_Train, X_Test,y_Test)= div_datos;
    /*Se crean vectores auxiliares para prueba y entrenamiento inicializados en 1 */
    Eigen::VectorXd V_train = Eigen::VectorXd::Ones(X_Train.rows());
    Eigen::VectorXd V_test = Eigen::VectorXd::Ones(X_Test.rows());

    /*Se redimensiona matriz de entrenamiento y de prueba para ser ajustada a los 
    vectores auxiliares anteriores*/

    X_Train.conservativeResize(X_Train.rows(),X_Train.cols()+1);
    X_Train.col(X_Train.cols()-1) = V_train;

    X_Test.conservativeResize(X_Test.rows(),X_Test.cols()+1);
    X_Test.col(X_Test.cols()-1) = V_test;

    /*Se crea el vector de coeficientes thetha*/
    Eigen::VectorXd thetha = Eigen::VectorXd::Zero(X_Train.cols());
    
    /*Se establece el alpha como ratio de aprendizaje de tipo flotante */
    float alpha = 0.01;
    int iteraciones = 1000;

    //Se crea un vector para almacenar las thethas de salida
    Eigen::VectorXd thethasOut;
    
    //Se crea un vector sencillo de flotantes para almacenar los valores del costo
    std::vector<float> costo;
    
    //Se calcula el gradiente descendiente
    std::tuple<Eigen::VectorXd, std::vector<float>> g_decendiente = modeloLR.gradientDescent(X_Train,
                                                                             y_Train,
                                                                             thetha,
                                                                             alpha,
                                                                             iteraciones);

    //Se desempaqueta el gradiente
    std::tie(thethasOut,costo) = g_decendiente;
    /* Se almacena los valores de thethas y costos en un fichero para posteriormente ser visualizado
    ExData.vectorToFile(costo,"costos.txt");*/
    
    /*Se extrae el promedio de la matriz de entrada*/
    auto prom_data = ExData.Promedio(matData);

    /*Se extraen los valores de la variable independiente*/
    auto var_prom_independientes = prom_data(0,13);
    
    /*SE escalan los datos */
    auto datos_escalados = matData.rowwise()-matData.colwise().mean();
    /*Se extrae la desviación estandar de los datos escalados*/
    auto desv_stand = ExData.DevStand(datos_escalados);

    /*Se extraen los valores de la variable independiente*/    
    auto var_desv_independientes = desv_stand(0,13);
    
    /*Se crean una matrices para almacenar los valores estimados de entrenamiento y prueba*/
    Eigen::MatrixXd y_train_hat = (X_Train * thethasOut * var_desv_independientes).array() + var_prom_independientes;
    Eigen::MatrixXd y_test_hat = (X_Test * thethasOut * var_desv_independientes).array() + var_prom_independientes;

    /*Matrices para los valores reales de y de entrenamiento y prueba*/
    Eigen::MatrixXd yT = matData.col(13).bottomRows(X_Test.rows());
    Eigen::MatrixXd y = matData.col(13).topRows(X_Train.rows());

    /*Se revisa que tan bueno fue el modelo a traves de la metrica de rendimiento*/
    float metrica_R2 = modeloLR.R2score(y,y_train_hat);
    float metrica_R2Test = modeloLR.R2score(yT,y_test_hat);

    std::cout << "Métrica R2 Train: "<< metrica_R2<<std::endl;
    std::cout << "Métrica R2 Test: "<< metrica_R2Test<<std::endl;
     return EXIT_SUCCESS;
}
