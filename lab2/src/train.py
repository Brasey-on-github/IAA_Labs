# set the matplotlib backend so figures can be saved in the background
import matplotlib

# import the necessary packages
from IAA_Labs.lab2.src.Network.leboss import NN
from sklearn.model_selection import train_test_split
from torch.utils.data import DataLoader
from torchvision.transforms import ToTensor
from torchvision.datasets import KMNIST
from torch.optim import Adam
from torch import nn
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import argparse
import torch
import time
import PIL

def open_images(self,paths):
        images = []
        for path in paths:
                with PIL.Image.open(path) as image:
                        images.append(np.asarray(image))
                
        return np.array(images)

if __name__ == "__main__":
        # construct the argument parser and parse the arguments
        ap = argparse.ArgumentParser()
        ap.add_argument("-m", "--model", type=str, required=True,
                help="path to output trained model")
        ap.add_argument("-p", "--plot", type=str, required=True,
                help="path to output loss/accuracy plot")
        ap.add_argument("-d", "--dataset", type=str, required=True,
                help="path to dataset csv file")
        args = vars(ap.parse_args())

        # define training hyperparameters
        INIT_LR = 1e-3
        BATCH_SIZE = 64
        EPOCHS = 10
        # define the train and val splits
        TRAIN_SPLIT = 0.75
        VAL_SPLIT = 1 - TRAIN_SPLIT
        # set the device we will be using to train the model
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        # load the KMNIST dataset
        print("[INFO] loading the dataset...")
        
        # Instanciate and split dataset 80/20
        train, test = train_test_split(pd.read_csv(args["dataset"]),test_size=0.2)


        


        


                
        