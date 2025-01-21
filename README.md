# ModelTraining

This is an ML model for recognizing handwritten digits.

The selected library for building the model is OpenCV.

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
