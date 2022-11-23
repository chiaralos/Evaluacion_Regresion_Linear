**Tabla de contenidos**

- [Descripción del repositorio](https://github.com/chiaralos/Evaluacion_Regresion_Linear/main/Readme.md#descripci%C3%B3n-del-repositorio)
- [Python](https://github.com/chiaralos/Evaluacion_Regresion_Linear/main/Readme.md#python)
- [C++](https://github.com/chiaralos/Evaluacion_Regresion_Linear/main/Readme.md#c)
  - [Ejecución](https://github.com/chiaralos/Evaluacion_Regresion_Linear/main/Readme.md#ejecuci%C3%B3n)
  - [Recomendaciones](https://github.com/chiaralos/Evaluacion_Regresion_Linear/main/Readme.md#recomendaciones)

## Descripción del repositorio
En este repositorio encontrará la regresión linear y métrica $R^2$ del dataset [Cubic zirconia](https://raw.githubusercontent.com/chiaralos/Evaluacion_Regresion_Linear/main/Dataset/cubic_zirconia.csv), en dos lenguajes de programación: Python y C++. 

## Python
Si desea usar la implementación en Python, por favor haga clic [aquí](https://colab.research.google.com/drive/1Q70C2xwAQDBE_o5tGOJH0SnXrZYYn4VZ?usp=sharing), o dirijase a la carpeta Implementación_Python y de clic en Examen_Final-Chiara_Valenzuela.ipynb.

En el código encontrará:

- Análisis exploratorio de datos (EDA).
- Preprocesado de datos.
- Modelo LR con Scikit-Learn.
- Métrica de rendimiento.
- Comparativas con capturas entre SK-L/C++.
- Conclusiones.
- Referencias.

## C++
Si desea usar la implementación hecha en C++,siga las instrucciones:

1. Haga click en "Code".
2. Luego en "Download Zip”con eso comenzará la descarga.
3. Descomprima el archivo.
4. Entre en la carpeta llamada "Implementación_C++".
5. Allí encontrará todos los .cpp, .h, .csv y Makefile, que podrá ejecutar y modificar.

#### Ejecución
-----
Si desea ejecutar el código: 
1. Una vez esté en la carpeta "Implementación_C++".
2. Clic derecho, seleccione "abrir en terminal".
3. Escriba el siguiente comando: `$make`.
4. Listo, el programa se estará ejecutando en su dispositivo.

Si desea eliminar los ejecutables solo escriba en la consola `$make clean`.

#### Recomendaciones
-----
- Se recomienda trabajar en Linux
- Es necesario tener descargado Eigen y Boost.

<details><summary>Instalación de EIGEN y BOOST</summary>
<p>
  
#### Instalación de EIGEN
  
`$sudo apt install libeigen3-dev`

`$sudo apt update`

Se crea el enlace simbolico de la biblioteca EIGEN:

`$ln -sf  /usr/include/eigen3/Eigen Eigen`

`$ln -sf  /usr/include/eigen3/unsupported unsupported`

`$sudo apt update`

#### Instalación de BOOST
  
`$sudo apt-get install libboost-all-dev`

`$sudo apt update`

Se crea el enlace simbolico de la biblioteca BOOST

`$ln -sf /usr/include/boost boost`

`$sudo apt update`
