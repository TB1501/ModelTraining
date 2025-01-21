#include <opencv2/ml/ml.hpp>
#include<iostream>
#include<fstream>
#include <vector>


int convertBigEndianToInt(const char* bytes) {
    return (static_cast<unsigned char>(bytes[0]) << 24) |
        (static_cast<unsigned char>(bytes[1]) << 16) |
        (static_cast<unsigned char>(bytes[2]) << 8) |
        static_cast<unsigned char>(bytes[3]);
}

std::vector<std::vector<unsigned char>> readLabels(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

    // Read the magic number, number of labels
    char magicBytes[4], numLabelBytes[4];
    file.read(magicBytes, 4);
    file.read(numLabelBytes, 4);


    int numLabels = convertBigEndianToInt(numLabelBytes);

    std::cout << "Labels: " << numLabels << std::endl;

    // Allocate a vector to hold all labels
    std::vector<std::vector<unsigned char>> results;

    for (int i = 0; i < numLabels; i++) {

        // Allocate a vector to hold the current label
        std::vector<unsigned char> label(1);

        // Read the current label
        file.read((char*)(label.data()), 1);

        // Add the current label to the results
        results.push_back(label);

    }

    file.close();
    return results;
}

std::vector<std::vector<unsigned char>> readImages(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

    // Read the magic number, number of images, rows, and columns
    char magicBytes[4], numImagesBytes[4], numRowsBytes[4], numColumnsBytes[4];
    file.read(magicBytes, 4);
    file.read(numImagesBytes, 4);
    file.read(numRowsBytes, 4);
    file.read(numColumnsBytes, 4);

    // Convert the images from big-endian to integers
    int numImages = convertBigEndianToInt(numImagesBytes);
    int numRows = convertBigEndianToInt(numRowsBytes);
    int numColumns = convertBigEndianToInt(numColumnsBytes);

    //Print the number of images, rows, and columns - CHECK IF THE CONVERSION IS CORRECT
    std::cout << "Images: " << numImages << ", Rows: " << numRows << ", Columns: " << numColumns << std::endl;

    // Allocate a vector to hold all images
    std::vector<std::vector<unsigned char>> results;

    for (int i = 0; i < numImages; i++) {

        // Allocate a vector to hold the current image
        std::vector<unsigned char> image(numRows * numColumns);

        // Read the current image
        file.read((char*)(image.data()), numRows * numColumns);

        // Add the current image to the results
        results.push_back(image);

    }

    file.close();
    return results;
}

int main(){

    //READING THE DATA

    std::string fileNameImages = "C:\\Users\\Tin\\Desktop\\archive (1)\\train-images-idx3-ubyte\\train-images-idx3-ubyte";
    std::string fileNameLabels = "C:\\Users\\Tin\\Desktop\\archive (1)\\train-labels-idx1-ubyte\\train-labels-idx1-ubyte";

    std::vector<std::vector<unsigned char>> images = readImages(fileNameImages);
    std::vector<std::vector<unsigned char>> labels = readLabels(fileNameLabels);

    //Checking if the images and labels are read correctly
    /*std::cout << "Raw image data:" << std::endl;
    for (size_t i = 0; i < images[0].size(); ++i) {
        std::cout << static_cast<int>(images[0][i]) << " ";
    }
    std::cout << std::endl;*/


    std::vector<cv::Mat> imagesData;
    std::vector<int> labelsData;



    //std::cout << "Image data: \n";


    for (auto i = 0u; i < images.size(); ++i)
    {
        //Initializing the cv::Mat object with the size of 28x28 and setting the pixel values to 0
        cv::Mat m(28, 28, CV_8UC1, cv::Scalar(0));
        for (int row = 0; row < m.rows; ++row)
            for (int col = 0; col < m.cols; ++col)
                m.at<uchar>(row, col) = images[i][row * m.cols + col];

        imagesData.push_back(std::move(m));
        labelsData.push_back(labels[i].front());

        //Checking if the images and labels are read correctly
        /*std::cout << "Label: " << (labelsData[i]) << std::endl;
        for (int j = 0; j < 28; j++) {
            for (int k = 0; k < 28; k++) {
				std::cout << ((imagesData[i].at<uchar>(j,k))==0?' ': 'x') << " ";
			}
			std::cout << std::endl;
		}*/

    }

    /*_____________________________________________________________________________________________________________________________________*/

    //PREPARING THE TRAINING DATA

    cv::Mat_<int> layerSizes(1, 3);
    /*std::cout << "Number of images: " << imagesData[0].total();*/
    layerSizes(0, 0) = imagesData[0].total();
    layerSizes(0, 1) = 100;
    layerSizes(0, 2) = 10;

    int numSamples = imagesData.size();

    cv::Mat trainingData(numSamples, imagesData[0].total(), CV_32F);
    cv::Mat labelData(numSamples, layerSizes(0,2), CV_32F);

    for (int i = 0; i < numSamples; i++) {
        cv::Mat image = imagesData[i].reshape(1, 1);
        image.convertTo(trainingData.row(i), CV_32F);

        cv::Mat label = cv::Mat::zeros(1, layerSizes(0,2), CV_32F);
        label.at<float>(0, labelsData[i]) = 1.0;
        label.copyTo(labelData.row(i));
    }

 /*   std::cout << "Training Data:" << std::endl;
    for (int i = 0; i < trainingData.rows; i++) {
        std::cout << "Image " << i << ":" << std::endl;
        for (int j = 0; j < trainingData.cols; j++) {
            std::cout << trainingData.at<float>(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Label Data:" << std::endl;
    for (int i = 0; i < labelData.rows; i++) {
        std::cout << "Label " << i << ":" << std::endl;
        for (int j = 0; j < labelData.cols; j++) {
            std::cout << labelData.at<float>(i, j) << " ";
        }
        std::cout << std::endl;
    }*/

    /*_____________________________________________________________________________________________________________________________________*/

    //TRAINING THE NETWORK

    cv::Ptr<cv::ml::ANN_MLP> network = cv::ml::ANN_MLP::create();
    network->setLayerSizes(layerSizes);
    network->setActivationFunction(cv::ml::ANN_MLP::SIGMOID_SYM, 0.1, 0.1);
    network->setTrainMethod(cv::ml::ANN_MLP::BACKPROP, 0.01, 0.1);
    cv::Ptr<cv::ml::TrainData> trainData = cv::ml::TrainData::create(trainingData, cv::ml::ROW_SAMPLE, labelData);

    network->train(trainData);
    network->save("C:\\Users\\Tin\\Desktop\\newtrainData\\trData2.xml");

        




	return 0;



}