import torch.nn.functional as F
import numpy as np
import argparse
import torch
from PIL import Image
import cv2
from torch.nn import Module
from torch.nn import Conv2d
from torch.nn import Linear
from torch.nn import MaxPool2d
from torch.nn import ReLU


class CNN(Module):
    def __init__(self):
          # call the parent constructor
        super(CNN, self).__init__()

        # initialize first set of CONV => RELU => POOL layers
        self.conv1 = Conv2d(in_channels=1, out_channels=20,
            kernel_size=(5, 5))
        self.relu1 = ReLU()
        self.maxpool1 = MaxPool2d(kernel_size=(2, 2), stride=(2, 2))
        # initialize second set of CONV => RELU => POOL layers
        self.conv2 = Conv2d(in_channels=20, out_channels=50,
            kernel_size=(5, 5))
        self.relu2 = ReLU()
        self.maxpool2 = MaxPool2d(kernel_size=(2, 2), stride=(2, 2))
        # initialize first (and only) set of FC => RELU layers
        self.fc1 = Linear(in_features=50*47*47, out_features=500)
        self.relu3 = ReLU()
        # initialize our softmax classifier
        self.fc2 = Linear(in_features=500, out_features=4)


    def forward(self, x):
        # pass the input through our first set of CONV => RELU =>
        # POOL layers
        # normalize pixel value
        x /= 256.
        x = self.conv1(x)
        x = self.relu1(x)
        x = self.maxpool1(x)
        # pass the output from the previous layer through the second
        # set of CONV => RELU => POOL layers
        x = self.conv2(x)
        x = self.relu2(x)
        x = self.maxpool2(x)
        # flatten the output from the previous layer and pass it
        # through our only set of FC => RELU layers
        x = torch.flatten(x,start_dim=-3)     # flatten the tensor
        x = self.fc1(x)
        x = self.relu3(x)
        # pass the output to get our output
        # predictions
        output = F.sigmoid(self.fc2(x))
        return output 
    
    def detect_line(self,image) :

        image = np.transpose(image,(1,2,0))
        image = image.squeeze()
        
        processed_image = cv2.Canny(image,55,200)
        # put a opacity of the original image back in
        processed_image = np.where(processed_image == 0, image, processed_image)
        processed_image[:150] = 0
        processed_image = np.expand_dims(processed_image, axis=2)

        self.eval()
        with torch.no_grad():
                img = torch.from_numpy(np.transpose(processed_image,(2,0,1))).float()
                output = self(img)
                output = (output.numpy() * 200).astype(int)
                # Reversing y axis
                output[1] = 200 - output[1]
                output[3] = 200 - output[3]

        return output

def init():
    module = CNN()
    module.load_state_dict(torch.load("./model.pt"))
    return module


if __name__ == "__main__":
     parser = argparse.ArgumentParser(prog='test_main')
     parser.add_argument('filename')
     args = parser.parse_args()
     m = init()
     with Image.open(args.filename) as image:
        image = np.expand_dims(image,axis=2)
        image = np.transpose(image,(2,0,1))
        ouput = m.detect_line(image)
        print(ouput)