#include <opencv2/ml/ml.hpp>
#include<iostream>
#include<fstream>
#include <vector>
#include "LabelReader.h"
#include "ImageReader.h"



int main(int argc, char* argv[]) {

    //READING THE DATA

    if (argc < 4) {
		std::cout << "Usage: " << argv[0] << " <path to images> <path to labels>" << std::endl;
		return 1;
	}

    std::string fileNameImages = argv[1];
    std::string fileNameLabels = argv[2];
    std::string savePath = argv[3];

    std::vector<std::vector<unsigned char>> images = readImages(fileNameImages);
    std::vector<std::vector<unsigned char>> labels = readLabels(fileNameLabels);



    std::vector<cv::Mat> imagesData;
    std::vector<int> labelsData;




    for (auto i = 0u; i < images.size(); ++i)
    {
        //Initializing the cv::Mat object with the size of 28x28 and setting the pixel values to 0
        cv::Mat m(28, 28, CV_8UC1, cv::Scalar(0));
        for (int row = 0; row < m.rows; ++row)
            for (int col = 0; col < m.cols; ++col)
                m.at<uchar>(row, col) = images[i][row * m.cols + col];

        imagesData.push_back(std::move(m));
        labelsData.push_back(labels[i].front());


    }

    /*_____________________________________________________________________________________________________________________________________*/

    //DEFINING THE NETWORK

    cv::Mat_<int> layerSizes(1, 3);
    /*std::cout << "Number of images: " << imagesData[0].total();*/
    layerSizes(0, 0) = imagesData[0].total();
    layerSizes(0, 1) = 100;
    layerSizes(0, 2) = 10;

    /*_____________________________________________________________________________________________________________________________________*/
    
    //PREPARING THE TRAINING DATA

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


    /*_____________________________________________________________________________________________________________________________________*/

    //TRAINING THE NETWORK

    cv::Ptr<cv::ml::ANN_MLP> network = cv::ml::ANN_MLP::create();
    network->setLayerSizes(layerSizes);
    network->setActivationFunction(cv::ml::ANN_MLP::SIGMOID_SYM, 0.1, 0.1);
    network->setTrainMethod(cv::ml::ANN_MLP::BACKPROP, 0.001, 0.1);
    cv::Ptr<cv::ml::TrainData> trainData = cv::ml::TrainData::create(trainingData, cv::ml::ROW_SAMPLE, labelData);

    network->train(trainData);
    network->save(savePath);
    std::cout << "Model saved to: " << savePath << std::endl;


	return 0;



}