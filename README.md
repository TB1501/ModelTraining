# ModelTraining

This is an ML model for recognizing handwritten digits.

The selected library for building the model is OpenCV.

---

INSTALLING OpenCV IN VISUAL STUDIO

OpenCV (Open Source Computer Vision Library) is a library of programming functions mainly for real-time computer vision.
Originally developed by Intel, it was later supported by Willow Garage, then Itseez (which was later acquired by Intel).
The library is cross-platform and licensed as free and open-source software under Apache License 2

In order to get started with OpenCV go to the official website: [OpenCV](https://opencv.org/).
On the website go to Library and install the requiered version (in this code i used OpenCv version 4.10.0).
Click on tha appropriate device you are downloading for (I'm using windows).
OpenCV willcdownload as an exe file. You only need to click on the file and file will autoconfigure.
When setting the path it is best to set a path that is at the begginig of your disk.

In order for OpneCV to work Visual Studio we need to configure the project. Create a new Visual Studio project and go to project properties.
In properties go to VC++ Directories -> Include Directories -> edit the static path to the .\opencv\build\include folder. Don't forget
to click on the box "Inherit from parent or project defaults". Next got to VC++ Directories -> Library Directories -> edit the static path lib folder
.\opencv\build\x64\vc16(or some other compiled binary)\lib. Also, click on "Inherit from parent or project defaults". Next go to
Linker -> Input -> Additional Dependencies -> edit the lib data. Here you have to add the lib files in the vc16\lib folder.
I added the opencv_world4100.lib and opencv_world4100d.lib files. It is important that the file without d at the end (debug) goes second becaus
when building there could be issues. Again, click on "Inherit from parent or project defaults".

In the last step you have to edit the system variables. Type in searc Edit the system environment variables. Go to page Advanced and clik on
Environmet Variables.... Next go to System variables -> Path and click Edit. Add the paths to .\opencv\build\x64\vc16\lib and
.\opencv\build\x64\vc16\bin.

It is useful to restart the VS project so the setup gets properly loaded.

---

MODEL DESCRIPTION

The model is trained on the MNIST dataset. The MNIST dataset is a set of 60000 images of handwritten digits from 0-9 and coresponding labels.

The adopted architecture was the Multi-Layer Perceptron (MLP) and for data training the backpropagation algorithm was selected.

The build of the model followed these steps:
1st step:

- in the 1st step the images were loaded

2nd step:

- in the 2nd step the layers for the neural network were defined

3rd step:

- in the 3rd step the data was processed for training
- image data was reshaped to to 1D array
- label data was one hot encoded and reshaped to 1D array

4th step:

- in the 4th step the model was created
- the layers of the model, the activation function and the training methode were defined
- the trained model was saved as an xml file for further use
