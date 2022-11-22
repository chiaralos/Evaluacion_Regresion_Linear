#include "linearregression.h"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>

/*Primera función: función de costo para la regresión
 * lineal basado en los mínimos cuadrados ordinarios
 * demostrado en clase*/

float LinearRegression:: F_OLS_Costo(Eigen::MatrixXd X, Eigen::MatrixXd y, Eigen::MatrixXd thetha)
{
    Eigen::MatrixXd m_interior = (pow((X*thetha -y ).array(),2));
    return (m_interior / (2*X.rows())).sum();

}

/*Función de gradiente descendiente
 * en función de un ratio de aprendizaje se avanza hasta
 * encontrar el punto mínimo que representa el valor optimo
 * para la función*/

std::tuple<Eigen::VectorXd, std::vector<float>> LinearRegression:: gradientDescent (Eigen::MatrixXd X,
                                                                                    Eigen::MatrixXd y,
                                                                                    Eigen::VectorXd thetha,
                                                                                    float alpha,
                                                                                    int num_iter){
    Eigen::MatrixXd temporal = thetha;
    int parametros = thetha.rows();
    std::vector<float> costo;
    /*En costo ingresaremos los valores de la función de costo*/
    costo.push_back(F_OLS_Costo(X,y,thetha));
    /*SE itera según el número de iteraciones y el ratio de aprendizaje
     * para encontrar los valores optimos*/
    for(int i =0; i<num_iter;i++){
        Eigen::MatrixXd error = X*thetha-y;
        for(int j =0; j<parametros; ++j){
            Eigen::MatrixXd X_i = X.col(j);
            Eigen::MatrixXd termino = error.cwiseProduct(X_i);
            temporal(j,0) = thetha(j,0) - (alpha/ X.rows())*termino.sum();
        }
        thetha = temporal;
        /*En costo ingresaremos los valores de la función de costo*/
        costo.push_back(F_OLS_Costo(X,y,thetha));
    }
    //ME FALTA EL RETURN DE UNA TUPLA
    return std::make_tuple(thetha,costo);
}

/* A continuación se presenta la función para revisar que tan bueno es nuestro modelo:
 * Se procede a crear la métrica de rendimiento:
 *  - R² score: Coeficiente de determinación, en donde el mejor valor posible es 1*/
float LinearRegression::R2score(Eigen::MatrixXd y, Eigen::MatrixXd y_hat){
    auto numerador = (pow((y - y_hat).array(),2)).sum();
    auto denominador = (pow((y.array() - y.mean()),2)).sum();
    return (1 - (numerador/denominador));
}
