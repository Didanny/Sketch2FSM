# Importing the required packages
from keras.models import Sequential
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.preprocessing.image import ImageDataGenerator
import numpy as np
from keras.preprocessing import image

# Initializing the sequential classifier
classifier = Sequential()

# Add the first convolutional layer
classifier.add(Conv2D(32, (3,3), input_shape = (64,64,3), activation='relu'))
# Add maxpooling layer
classifier.add(MaxPooling2D(pool_size=(2,2)))
# Convert pooled layer into continuous vector
classifier.add(Flatten())
# Fully connected layer
classifier.add(Dense(units = 128, activation = 'relu'))
# Output layer, 5 units for up,down,left,right,self
classifier.add(Dense(units = 5, activation = 'sigmoid'))

# Compiling the model
classifier.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

print('Testing the packages')