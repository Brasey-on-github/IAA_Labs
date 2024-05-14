#ifndef MODEL_LAB4_GRAPHINFO_H
#define MODEL_LAB4_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8
// Input_1
#define model_lab4_Input_1_OUT_SCALE	1.0
#define model_lab4_Input_1_OUT_QSCALE	64
#define model_lab4_Input_1_OUT_QNORM	6
#define model_lab4_Input_1_OUT_ZERO_POINT	0
// S1_Op_input_1_formatter
#define model_lab4_S1_Op_input_1_formatter_OUT_SCALE	0.00392156862745098
#define model_lab4_S1_Op_input_1_formatter_OUT_QSCALE	64
#define model_lab4_S1_Op_input_1_formatter_OUT_QNORM	14
#define model_lab4_S1_Op_input_1_formatter_OUT_ZERO_POINT	-128
// S2_Op__conv1_Conv_weights
#define model_lab4_S2_Op__conv1_Conv_weights_OUT_SCALE	0.004638697486370802
#define model_lab4_S2_Op__conv1_Conv_weights_OUT_QSCALE	76
#define model_lab4_S2_Op__conv1_Conv_weights_OUT_QNORM	14
#define model_lab4_S2_Op__conv1_Conv_weights_OUT_ZERO_POINT	0
// S3_Op__conv1_Conv_biases
#define model_lab4_S3_Op__conv1_Conv_biases_OUT_SCALE	1.819097053478746e-05
#define model_lab4_S3_Op__conv1_Conv_biases_OUT_QSCALE	76
#define model_lab4_S3_Op__conv1_Conv_biases_OUT_QNORM	22
#define model_lab4_S3_Op__conv1_Conv_biases_OUT_ZERO_POINT	0
// S4_Conv2d_6x3x5x5_MaxPool_2x2_Relu
#define model_lab4_S4_Conv2d_6x3x5x5_MaxPool_2x2_Relu_OUT_SCALE	0.016609564014509613
#define model_lab4_S4_Conv2d_6x3x5x5_MaxPool_2x2_Relu_OUT_QSCALE	68
#define model_lab4_S4_Conv2d_6x3x5x5_MaxPool_2x2_Relu_OUT_QNORM	12
#define model_lab4_S4_Conv2d_6x3x5x5_MaxPool_2x2_Relu_OUT_ZERO_POINT	-128
// S5_Op__conv2_Conv_weights
#define model_lab4_S5_Op__conv2_Conv_weights_OUT_SCALE	0.0028283847495913506
#define model_lab4_S5_Op__conv2_Conv_weights_OUT_QSCALE	93
#define model_lab4_S5_Op__conv2_Conv_weights_OUT_QNORM	15
#define model_lab4_S5_Op__conv2_Conv_weights_OUT_ZERO_POINT	0
// S6_Op__conv2_Conv_biases
#define model_lab4_S6_Op__conv2_Conv_biases_OUT_SCALE	4.697823755600028e-05
#define model_lab4_S6_Op__conv2_Conv_biases_OUT_QSCALE	99
#define model_lab4_S6_Op__conv2_Conv_biases_OUT_QNORM	21
#define model_lab4_S6_Op__conv2_Conv_biases_OUT_ZERO_POINT	0
// S7_Conv2d_16x6x5x5_MaxPool_2x2_Relu
#define model_lab4_S7_Conv2d_16x6x5x5_MaxPool_2x2_Relu_OUT_SCALE	0.02187510097728056
#define model_lab4_S7_Conv2d_16x6x5x5_MaxPool_2x2_Relu_OUT_QSCALE	90
#define model_lab4_S7_Conv2d_16x6x5x5_MaxPool_2x2_Relu_OUT_QNORM	12
#define model_lab4_S7_Conv2d_16x6x5x5_MaxPool_2x2_Relu_OUT_ZERO_POINT	-128
// S8_Op__fc1_MatMul_weights
#define model_lab4_S8_Op__fc1_MatMul_weights_OUT_SCALE	0.0011765985982492566
#define model_lab4_S8_Op__fc1_MatMul_weights_OUT_QSCALE	77
#define model_lab4_S8_Op__fc1_MatMul_weights_OUT_QNORM	16
#define model_lab4_S8_Op__fc1_MatMul_weights_OUT_ZERO_POINT	0
// S9_Op__fc1_MatMul_biases
#define model_lab4_S9_Op__fc1_MatMul_biases_OUT_SCALE	2.573821314642925e-05
#define model_lab4_S9_Op__fc1_MatMul_biases_OUT_QSCALE	108
#define model_lab4_S9_Op__fc1_MatMul_biases_OUT_QNORM	22
#define model_lab4_S9_Op__fc1_MatMul_biases_OUT_ZERO_POINT	0
// S10_Op__fc1_MatMul_fusion
#define model_lab4_S10_Op__fc1_MatMul_fusion_OUT_SCALE	0.026181325725480622
#define model_lab4_S10_Op__fc1_MatMul_fusion_OUT_QSCALE	107
#define model_lab4_S10_Op__fc1_MatMul_fusion_OUT_QNORM	12
#define model_lab4_S10_Op__fc1_MatMul_fusion_OUT_ZERO_POINT	-128
// S11_Op__fc2_MatMul_weights
#define model_lab4_S11_Op__fc2_MatMul_weights_OUT_SCALE	0.0017775038722902536
#define model_lab4_S11_Op__fc2_MatMul_weights_OUT_QSCALE	116
#define model_lab4_S11_Op__fc2_MatMul_weights_OUT_QNORM	16
#define model_lab4_S11_Op__fc2_MatMul_weights_OUT_ZERO_POINT	0
// S12_Op__fc2_MatMul_biases
#define model_lab4_S12_Op__fc2_MatMul_biases_OUT_SCALE	4.653740785873424e-05
#define model_lab4_S12_Op__fc2_MatMul_biases_OUT_QSCALE	98
#define model_lab4_S12_Op__fc2_MatMul_biases_OUT_QNORM	21
#define model_lab4_S12_Op__fc2_MatMul_biases_OUT_ZERO_POINT	0
// S13_Op__fc2_MatMul_fusion
#define model_lab4_S13_Op__fc2_MatMul_fusion_OUT_SCALE	0.012839769849590227
#define model_lab4_S13_Op__fc2_MatMul_fusion_OUT_QSCALE	105
#define model_lab4_S13_Op__fc2_MatMul_fusion_OUT_QNORM	13
#define model_lab4_S13_Op__fc2_MatMul_fusion_OUT_ZERO_POINT	-128
// S14_Op__fc3_MatMul_weights
#define model_lab4_S14_Op__fc3_MatMul_weights_OUT_SCALE	0.002588416449725628
#define model_lab4_S14_Op__fc3_MatMul_weights_OUT_QSCALE	85
#define model_lab4_S14_Op__fc3_MatMul_weights_OUT_QNORM	15
#define model_lab4_S14_Op__fc3_MatMul_weights_OUT_ZERO_POINT	0
// S15_Op__fc3_MatMul_biases
#define model_lab4_S15_Op__fc3_MatMul_biases_OUT_SCALE	3.3234671489370496e-05
#define model_lab4_S15_Op__fc3_MatMul_biases_OUT_QSCALE	70
#define model_lab4_S15_Op__fc3_MatMul_biases_OUT_QNORM	21
#define model_lab4_S15_Op__fc3_MatMul_biases_OUT_ZERO_POINT	0
// S16_Linear_10x84
#define model_lab4_S16_Linear_10x84_OUT_SCALE	0.03497572771207554
#define model_lab4_S16_Linear_10x84_OUT_QSCALE	72
#define model_lab4_S16_Linear_10x84_OUT_QNORM	11
#define model_lab4_S16_Linear_10x84_OUT_ZERO_POINT	0
// Output_1
#define model_lab4_Output_1_OUT_SCALE	0.03497572771207554
#define model_lab4_Output_1_OUT_QSCALE	72
#define model_lab4_Output_1_OUT_QNORM	11
#define model_lab4_Output_1_OUT_ZERO_POINT	0
#endif //MODEL_LAB4_GRAPHINFO_H