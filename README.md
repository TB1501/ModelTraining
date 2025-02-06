# ModelTraining

This is an ML model for recognizing handwritten digits.

The selected library for building the model is OpenCV.

---

INSTALLING OpenCV IN VISUAL STUDIO

OpenCV (Open Source Computer Vision Library) is a library of programming functions mainly for real-time computer vision.
Originally developed by Intel, it was later supported by Willow Garage, then Itseez (which was later acquired by Intel).
The library is cross-platform and licensed as free and open-source software under Apache License 2

In order to get started with OpenCV go to the official website: [OpenCV](https://opencv.org/).
On the website go to the Library page and download the required version (I used OpenCV version 4.10.0).
Download the appropriate .exe file for the device and run it.

In order for OpenCV to work the project needs to be configured. In project properties configure the VC++ Directories, the Include Directories and Library Directories.
In the Include Directories the path to the include folder in OpenCV folder needs to be specified (.\opencv\build\include). In the Library Directories the path to the
lib files needs to be specified (.\opencv\build\x64\vc16\lib). After configuring the VC++ Directories the Linker also needs to be configured.
In Input add the required opencv.lib files. For running the release version the opencv_world4100.lib needs to be added and for the debug version the opencv_world4100d.lib.

Before running the release or debug .exe file copy the opencv_world4100.dll to the location of the release .exe or the opencv_world4100d.dll to the location of the
debug .exe

---

MODEL DESCRIPTION

The model is trained on the MNIST dataset. The MNIST dataset is a set of 60000 images of handwritten digits from 0-9 and corresponding labels.

The adopted architecture was the Multi-Layer Perceptron (MLP) and for data training the backpropagation algorithm was selected.

The build of the model followed these steps:
1st step:

- in the 1st step the images were loaded

2nd step:

- in the 2nd step the layers for the neural network were defined

3rd step:

- in the 3rd step the data was processed for training
- image data was reshaped to 1D array
- label data was one hot encoded and reshaped to 1D array

4th step:

- in the 4th step the model was created
- the layers of the model, the activation function and the training method were defined
- the trained model was saved as an xml file for further use
