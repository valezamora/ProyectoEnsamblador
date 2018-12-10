#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#define LOWEST_BYTE(NUMBER) ((unsigned char)(NUMBER & 255))

typedef unsigned char byte;

int help(bool detailed)
{
    if (detailed)
    {
        std::cout << "  Modo básico: (Invocación sin argumentos).\n"
                     "  Creador de imágenes escalares sitvg a partir de texto ingresado en la\n"
                     "  entrada  estándar con  el siguiente  formato:  (Las barras verticales\n"
                     "  representan espacios, tabulaciones o fines de linea. Entre paréntesis\n"
                     "  se representan los tipos de datos que serán usados para maniplar cada\n"
                     "  cantidad.)\n"
                     "\n"
                     "()======================================================================()\n"
                     "||                                                                      ||\n"
                     "||    Nombre del archivo por crear, sin espacios |                      ||\n"
                     "||    Cantidad de figuras (32-uint) |                                   ||\n"
                     "||    Largo de la imagen (32-float) | Alto de la imagen (32-float) |    ||\n"
                     "||    Color figura 1 (3x 8-uint) | Grosor figura 1 (16-uint) |          ||\n"
                     "||    Cantidad de vértices figura 1 (16-int) |                          ||\n"
                     "||    X1 figura 1 (32-float) | Y1 figura 1 (32-float) |                 ||\n"
                     "||    X2 figura 1 (32-float) | Y2 figura 1 (32-float) |                 ||\n"
                     "||    ...                                                               ||\n"
                     "||    Xn figura 1 (32-float) | Yn figura 1 (32-float) |                 ||\n"
                     "||    Color figura 2 (3x 8-uint) | Grosor figura 2 (16-uint) |          ||\n"
                     "||    Cantidad de vértices figura 2 (16-int) |                          ||\n"
                     "||    X1 figura 2 (32-float) | Y1 figura 2 (32-float) |                 ||\n"
                     "||    X2 figura 2 (32-float) | Y2 figura 2 (32-float) |                 ||\n"
                     "||    ...                                                               ||\n"
                     "||    Xn figura 2 (32-float) | Yn figura 2 (32-float) |                 ||\n"
                     "||    ...                                                               ||\n"
                     "||    Color figura m (3x 8-uint) | Grosor figura m (16-uint) |          ||\n"
                     "||    Cantidad de vértices figura m (16-int) |                          ||\n"
                     "||    X1 figura m (32-float) | Y1 figura m (32-float) |                 ||\n"
                     "||    X2 figura m (32-float) | Y2 figura m (32-float) |                 ||\n"
                     "||    ...                                                               ||\n"
                     "||    Xn figura m (32-float) | Yn figura m (32-float) |                 ||\n"
                     "||                                                                      ||\n"
                     "()======================================================================()\n\n"
                     ""
                     "  Modo avanzado: (Invocación con argumento \"-a\")\n"
                     "  Automatiza la creación de imágenes SITVG al definir aleatoriamente sus\n"
                     "  elementos, utilizando como límites los ingresados por el usuario. Para\n"
                     "  esto, solicita al usuario la cantidad de imágenes deseadas y un nombre\n"
                     "  base para ellas. Además, pide un rango para la cantidad de figuras por\n"
                     "  imagen y una cantidad máxima de vértices por figura. A partir de estos\n"
                     "  datos se genera la cantidad de imágenes solicitada con los atributos y\n"
                     "  características ingresados.\n\n";
    }
    else
    {
        std::cout << "  Por favor, ejecute el programa sin argumentos para utilizar el modo\n"
                     "  básico, con el argumento \"-a\" para correr el modo avanzado, o con\n"
                     "  el  argumento  \"-h\"  para obtener más información.\n"
                     "  Atención:  Cualquier parámetro será solicitado hasta que se ingrese\n"
                     "  de acuerdo con los límites establecidos.\n\n";
    }
    return 0;
}

/**
 * @brief Manual constructor of personalized sitvg images.
 */
int basicMode()
{
    std::string fileName = "";
    unsigned figureQuantity = 0;
    short vertexAmount = 0;
    float x = 0;
    float y = 0;
    int colors [3] = {0, 0, 0};
    byte colorBytes [3] = {0, 0, 0};
    unsigned short thickness;

    std::cout << "Nombre del archivo: ";

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

    std::cout << "Cantidad de figuras: ";
    // Read and store figures quantity
    std::cin >> figureQuantity;

    // Write figures quantity to sitvg file
    newFile.write((char*) &figureQuantity, sizeof(unsigned));


    std::cout << "Tamaño de la imagen (X y Y): ";
    // Read and write length and height
    std::cin >> x >> y;
    newFile.write((char*) &x, sizeof(float));
    newFile.write((char*) &y, sizeof(float));

    // For every figure:
    for (unsigned fig = 0; fig < figureQuantity; ++fig)
    {
        std::cout << "\nFigura número " << fig+1 << ":\n";

        std::cout << "\tColor: ";
        // Read and write figure's color and figure's line thickness
        std::cin >> colors[0] >> colors[1] >> colors[2];
        colorBytes[0] = (byte) colors[0]; colorBytes[1] = (byte) colors[1]; colorBytes[2] = (byte) colors[2];
        newFile.write((char*) colorBytes, 3 * sizeof(byte));

        std::cout << "\tGrosor de linea: ";
        // Read and write figure's color and figure's line thickness
        std::cin >> thickness;
        newFile.write((char*) &thickness, sizeof(unsigned short));

        std::cout << "\tCantidad de vertices (negativa para figuras cerradas): ";
        // Read and store the figure's vertex amount
        std::cin >> vertexAmount;

        // Write the figure's vertex amount
        newFile.write((char*) &vertexAmount, sizeof (short));

        if (vertexAmount < 0) vertexAmount *= -1;

        // For every vertex in the figure:
        for (short vert = 0; vert < vertexAmount; ++vert)
        {
            std::cout << "\tCoordinadas vértice " << vert+1 << ": ";
            // Read and write the vertex's coordinates
            std::cin >> x >> y;
            newFile.write((char*) &x, sizeof(float));
            newFile.write((char*) &y, sizeof(float));
        }
    }

    std::cout << "\nCreación de " << fileName << "finalizada.\n\n" ;

    // Close created file.
    newFile.close();

    return 0;
}

/**
 * @brief Random integer generator.
 * @param first Smallest value possible.
 * @param last Largest value possible.
 * @return
 */
inline int randBetween(int first, int last)
{
    return first + (random () % (last - first + 1));
}

/**
 * @brief Automatic generator of random sitvg images.
 */
int advancedMode()
{
    std::string baseFileName = "";
    int noOfImages = -1;
    unsigned minNoOfFigs = -1, maxNoOfFigs = -1;
    short vertexMax = -1;

    unsigned noOfFigures = 0;
    short noOfVertices = 0;
    float xSize = 0;
    float ySize = 0;
    byte colorBytes [3] = {0, 0, 0};
    unsigned short thickness;
    float x = 0;
    float y = 0;

    // Reads base file name
    std::cout << "  Nombre base de los archivos: ";
    std::cin >> baseFileName;
    baseFileName = "Imagenes_generadas/" + baseFileName;

    // Deletes the file extension if needed
    unsigned long pos = baseFileName.find(".sitvg", baseFileName.length() - 6 - 1);
    if (pos != std::string::npos)
    {
        baseFileName[pos] = '\0';
    }

    // Reads amount of images to generate
    while (noOfImages < 0 || noOfImages > 50)
    {
        std::cout << "  Cantidad de imágenes por crear (hasta 50): ";
        std::cin >> noOfImages;
    }

    // Reads range for amount of figures per image.
    while (minNoOfFigs > maxNoOfFigs /*|| minNoOfFigs < 0*/ || maxNoOfFigs > 100)
    {
        std::cout << "  Cantidad mínima y máxima de figuras por imagen (de 0 a 100): ";
        std::cin >> minNoOfFigs >> maxNoOfFigs;
    }

    // Reads the maximun amount of vertices per figure.
    while (vertexMax < 0 || vertexMax > 50)
    {
        std::cout << "  Cantidad máxima de vértices por figura (hasta 50): ";
        std::cin >> vertexMax;
    }

    // For every image:
    for (int img = 1; img <= noOfImages; ++img)
    {
        std::cout << "  Imagen #" << img << ":...";

        // Creates new file
        std::ofstream newFile (baseFileName + std::to_string(img) + ".sitvg", std::ofstream::out | std::ofstream::binary);

        // Comptes and writes figures quantity to sitvg file
        noOfFigures = randBetween(minNoOfFigs, maxNoOfFigs);
        newFile.write((char*) &noOfFigures, sizeof(unsigned));

        // Computes and writes length and height
        xSize = randBetween(100, 1000);
        ySize = randBetween(100, 1000);
        newFile.write((char*) &xSize, sizeof(float));
        newFile.write((char*) &ySize, sizeof(float));

        // For every figure:
        for (unsigned fig = 0; fig < noOfFigures; ++fig)
        {
            // Computes number of vertices.
            noOfVertices = randBetween(-vertexMax, vertexMax);

            // Computes and writes figure's color and figure's line thickness
            for (int c = 0; c < 3; ++c)
                colorBytes[c] = LOWEST_BYTE(randBetween(0, 255));
            newFile.write((char*) colorBytes, 3 * sizeof(byte));
            thickness = randBetween(1, 30);
            newFile.write((char*) &thickness, sizeof(unsigned short));

            // Writes the figure's number of vertices
            newFile.write((char*) &noOfVertices, sizeof (short));

            if (noOfVertices < 0) noOfVertices *= -1;

            // For every vertex in the figure:
            for (short vert = 0; vert < noOfVertices; ++vert)
            {
                // Computes and writes the vertex's coordinates
                x = randBetween(0, xSize);
                y = randBetween(0, ySize);
                newFile.write((char*) &x, sizeof(float));
                newFile.write((char*) &y, sizeof(float));
            }
        }

        std::cout << " ¡Creada!\n";

        // Close created file.
        newFile.close();
    }

    std::cout << "\n  Terminado\n\n";
    return 0;
}

int main (int argc, char * argv [])
{
    std::cout << "  ============================ TextToSitvg ============================\n\n";
    if (argc == 1)
        return basicMode();

    if (argc > 2)
        return help(false);

    // Else, if there are 2 arguments:

    if (argv[1][0] == '-' && argv[1][1] == 'a' && argv[1][2] == '\0')
        return advancedMode();

    if (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0')
        return help(true);

    return help(false);
}
