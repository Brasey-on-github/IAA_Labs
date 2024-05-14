# Report IAA Lab 4

## 4

###  Explain which range you used for your quantization. Does range have an impact on model performance in this case ? Explain your answer.

TODO

### Do you observe a drop in the general accuracy ? If you did everything right, it should be negligible. Explain your findings.

TODO

### Compare the memory footprint of the original model and the quantized one. Did the memory footprint change ? Explain your findings. You can use torchinfo or torch-summary to get the memory footprint.

TODO

## 5

### Develop a formula for the quantized output of conv1 : O1q, as a function of sW1, sO1, sI , Iq, W1q.

TODO verify if this is correct

The formula for the quantized output of conv1, O1q, can be expressed as follows:

O1q = (sW1 * sI * W1q * Iq) / sO1

Where:
- sW1 is the scaling factor for the weights of conv1
- sI is the scaling factor for the input activations
- W1q is the quantized weights of conv1
- Iq is the quantized input activations
- sO1 is the scaling factor for the output activations of conv1

This formula represents the multiplication of the scaled quantized weights (W1q * sW1) with the scaled quantized input activations (Iq * sI), divided by the scaling factor for the output activations (sO1). This ensures that the quantized output activations are obtained within the desired range.

### Develop a general formula for the quantized output of convi : Oiq, as a function of sW i, sOi, sI , Iq, Wiq, and the scaling factors of the previous layers. Try to do it recursively by starting with conv2q to extract the formula.

TODO verify if this is correct

The formula for the quantized output of convi, Oiq, can be expressed recursively as follows:

Oiq = (sWi * sI * Wiq * Iq) / sOi

Where:

sWi is the scaling factor for the weights of convi
sI is the scaling factor for the input activations
Wiq is the quantized weights of convi
Iq is the quantized input activations
sOi is the scaling factor for the output activations of convi
If we consider the output of the previous layer as the input to the current layer, the formula becomes:

Oiq = (sWi * sOi-1 * Wiq * Oi-1q) / sOi

Where:

Oi-1q is the quantized output activations of convi-1
This formula represents the multiplication of the scaled quantized weights (Wiq * sWi) with the scaled quantized output activations of the previous layer (Oi-1q * sOi-1), divided by the scaling factor for the output activations (sOi). This ensures that the quantized output activations are obtained within the desired range.

## 6

### What’s the objective of the adjust command ?

adjust will convert all the HxWxC tensors into CxHxW and insert the proper transposes operations when needed. The adjust process also attempts to remove any unnecessary transposes in the graph so even with ONNX graphs which are in CxHxW format it should be run.

### With the help of the nnTool documentation 1, provide the right command for layer fusions.

fusions --scale8

### Which layers have been fused ?

_conv1_Conv,_pool_MaxPool,_Relu into _conv1_Conv_fusion

_conv2_Conv,_pool_1_MaxPool,_Relu_1 into _conv2_Conv_fusion

_fc1_MatMul,_Relu_2 into _fc1_MatMul_fusion

_fc2_MatMul,_Relu_3 into _fc2_MatMul_fusion


### Based on the first parts of this lab, explain why we need a set of images for our quantization.

TODO

### What should be the properties of this set of images ? Think in terms of diversity of images.

TODO

### In your generated file model.h, find the quantization constants (OUT_SCALE) and explain why they may be different than the ones you had to compute in stages 1 and 2.

TODO
