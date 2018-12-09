/** ========================= TextToSitvg =========================
 Creador de imágenes escalares sitvg a partir de texto ingresado en la
 entrada estándar con el siguiente formato:
 (Las barras verticales representan espacios, tabulaciones
 o fines de linea.)
 (Entre paréntesis se representan los tipos de datos que serán
 usados para maniplar cada cantidad.)

()==========================================================================()
||																			||
|| 		Nombre del archivo por crear, sin espacios |						||
|| 		Cantidad de figuras (32-uint) |                                 	||
|| 		Largo de la imagen (32-float) | Alto de la imagen (32-float) |		||
|| 		Color figura 1 (3x 8-uint) | Grosor figura 1 (16-uint) |			||
|| 		Cantidad de vértices figura 1 (16-int) |							||
||		X1 figura 1 (32-float) | Y1 figura 1 (32-float) |					||
||		X2 figura 1 (32-float) | Y2 figura 1 (32-float) |					||
||		...																	||
||		Xn figura 1 (32-float) | Yn figura 1 (32-float) |					||
|| 		Color figura 2 (3x 8-uint) | Grosor figura 2 (16-uint) |			||
|| 		Cantidad de vértices figura 2 (16-int) |							||
||		X1 figura 2 (32-float) | Y1 figura 2 (32-float) |					||
||		X2 figura 2 (32-float) | Y2 figura 2 (32-float) |					||
||		...																	||
||		Xn figura 2 (32-float) | Yn figura 2 (32-float) |					||
||		...																	||
|| 		Color figura m (3x 8-uint) | Grosor figura m (16-uint) |			||
|| 		Cantidad de vértices figura m (16-int) |							||
||		X1 figura m (32-float) | Y1 figura m (32-float) |					||
||		X2 figura m (32-float) | Y2 figura m (32-float) |					||
||		...																	||
||		Xn figura m (32-float) | Yn figura m (32-float) |					||
||																			||
()==========================================================================()

*/


#include <fstream>
#include <iostream>
#include <string>

typedef unsigned char byte;

int main ()
{
	std::string fileName = "";
	unsigned figureQuantity = 0;
	short vertexAmount = 0;
	float x = 0;
	float y = 0;
	int colors [3] = {0, 0, 0};
	byte colorBytes [3] = {0, 0, 0};
	unsigned short thickness;

    std::cout << "Filename: ";

	// Read sitvg file name
	std::cin >> fileName;

	// Appends the file extension if needed
    if (fileName.find(".sitvg", fileName.length() - 6 - 1) == std::string::npos)
	{
		fileName += ".sitvg";
        std::cout << "[.sitvg]\n\n";
    }

	// Create new file
	std::ofstream newFile (fileName, std::ofstream::out | std::ofstream::binary);

    std::cout << "Figure quantity: ";
	// Read and store figures quantity
    std::cin >> figureQuantity;

	// Write figures quantity to sitvg file
	newFile.write((char*) &figureQuantity, sizeof(unsigned));


    std::cout << "Img size (x and y): ";
	// Read and write length and height
	std::cin >> x >> y;
	newFile.write((char*) &x, sizeof(float));
	newFile.write((char*) &y, sizeof(float));

	// For every figure:
	for (unsigned fig = 0; fig < figureQuantity; ++fig)
	{
        std::cout << "\nFigure number " << fig+1 << ":\n";

        std::cout << "\tColor: ";
		// Read and write figure's color and figure's line thickness
        std::cin >> colors[0] >> colors[1] >> colors[2];
        colorBytes[0] = (byte) colors[0]; colorBytes[1] = (byte) colors[1]; colorBytes[2] = (byte) colors[2];
		newFile.write((char*) colorBytes, 3 * sizeof(byte));

        std::cout << "\tLine thickness: ";
        // Read and write figure's color and figure's line thickness
        std::cin >> thickness;
		newFile.write((char*) &thickness, sizeof(unsigned short));

        std::cout << "\tAmount of vertices: ";
		// Read and store the figure's vertex amount
		std::cin >> vertexAmount;

		// Write the figure's vertex amount
		newFile.write((char*) &vertexAmount, sizeof (short));

        if (vertexAmount < 0) vertexAmount *= -1;

		// For every vertex in the figure:
		for (short vert = 0; vert < vertexAmount; ++vert)
		{
            std::cout << "\tVertex " << vert+1 << " coordinates: ";
			// Read and write the vertex's coordinates
			std::cin >> x >> y;
			newFile.write((char*) &x, sizeof(float));
			newFile.write((char*) &y, sizeof(float));
		}
	}

    std::cout << "\nFinished creating " << fileName << "\n\n" ;

	// Close created file.
	newFile.close();
}
