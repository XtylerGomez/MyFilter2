// MyFilter2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
int process(VideoCapture& capture) {
    string window_name = "Wachando";
    
    namedWindow(window_name, WINDOW_KEEPRATIO);
    Mat frame;
    Mat BG_Img;
    for (;;) {
        capture >> frame;
        if (frame.empty())
            break;
        imshow(window_name, frame);
        char key = (char)waitKey(30);

        switch (key) {
        case 'q':
        case 'Q':
        case 27:
            return 0;
        default:
            break;
        }
    }
    return 0;
}

int main()
{
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        cerr << "hijoles no jalo :(";
        return 1;
    }
    process(capture);
    cout << "Hello World!\n";
    
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
