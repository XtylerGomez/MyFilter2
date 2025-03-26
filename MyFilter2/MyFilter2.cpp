// MyFilter2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

struct ColorCluster {
	int B;
	int G;
	int R;
	int mB;
    int mG;
	int mR;
    float t;
};

int N = 7;
ColorCluster Cl[7];

Mat BackG;
bool removeBG = false;


void Segmentation(Mat& frame, Mat& frameOut) {
    
	frameOut = frame.clone();

    for (int k = 0; k < N;k++) {
        Cl[k].mB = 0;
		Cl[k].mG = 0;
		Cl[k].mR = 0;
		Cl[k].t = 0;
    }
	//cvtColor(frame, frame, cv::COLOR_BGR2HSV);

	unsigned char* ptr = (unsigned char*)frame.ptr();
    unsigned char* ptrOut = (unsigned char*)frameOut.ptr();
    unsigned char* ptrBG = nullptr;
	if (removeBG) {
		ptrBG = (unsigned char*)BackG.ptr();
	}

    for (int j = 0;j < frame.rows;j++) {
        for (int i = 0; i < frame.cols;i++) {

            int pix=(j*frame.cols*3)+3*i;
			unsigned char B = ptr[pix];
			unsigned char G = ptr[pix + 1];
			unsigned char R = ptr[pix + 2];
            if (removeBG) {
				unsigned char B_bg = ptrBG[pix];
				unsigned char G2_bg = ptrBG[pix + 1];
				unsigned char R2_bg = ptrBG[pix + 2];

				float dB = abs(B - B_bg);
				float dG = abs(G - G2_bg);
				float dR = abs(R - R2_bg);

                if ((dB > 50) || (dG > 50) || (dR > 50)) {
                
                }
                else {
					B = 0;
					G = 0;
					R = 0;
                }
            }
			
            float Max = 10000; int sel = -1;
            for (int k = 0; k < N;k++) {
                float d = abs(Cl[k].B - B)+abs(Cl[k].G-G)+abs(Cl[k]. R - R);
                if (d < Max) {
                    Max = d;
                    sel = k;
                }
            }
            if (sel >= 0) {
                Cl[sel].mB += B;
				Cl[sel].mG += G;
				Cl[sel].mR += R;
				Cl[sel].t++;

                ptrOut[pix] = Cl[sel].B; //Blue
                ptrOut[pix + 1] = Cl[sel].G;//Green
                ptrOut[pix + 2] = Cl[sel].R; //Red
			}
            /*
            int I = (B + G + R) / 3;
            if ((R > 110) && (G < 180) && (B<120)) {
                ptrOut[pix] = 255; //Blue
                ptrOut[pix + 1] = 0; //Green
                ptrOut[pix + 2] = 0; //Red
            }
            else {
                ptrOut[pix] = I; //Blue
                ptrOut[pix + 1] = I; //Green
                ptrOut[pix + 2] = I; //Red
            }*/
            
        }
    
    }
    for (int k = 0; k < N;k++) {
        if (Cl[k].t > 0) {
            Cl[k].B = Cl[k].mB / Cl[k].t;
            Cl[k].G = Cl[k].mG / Cl[k].t;
            Cl[k].R = Cl[k].mR / Cl[k].t;
        }
		
    }
    return;
}

int process(VideoCapture& capture) {
    for (int k = 0; k < N;k++) {
        Cl[k].B = ((float)255 * rand()) / RAND_MAX;
		Cl[k].G = ((float)255 * rand()) / RAND_MAX;
		Cl[k].R = ((float)255 * rand()) / RAND_MAX;
		Cl[k].t = 0;
    }
    string window_name = "Wachando";
    
    namedWindow(window_name, WINDOW_KEEPRATIO);
    Mat frame, result;
    Mat BG_Img;
    for (;;) {
        capture >> frame;
        if (frame.empty())
            break;

		Segmentation(frame, result);
        imshow(window_name, result);
        char key = (char)waitKey(30);

        switch (key) {
        case '1':
        case 'q':
        case 'Q':
        case 27:
            return 0;
			break;
        case 'b':
		case 'B':
            BackG = frame.clone();
            removeBG = true;
            break;
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
