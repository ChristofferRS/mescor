project('cmsis','c')

src=files([
    'CMSIS/NN/Source/ActivationFunctions/arm_relu6_s8.c',
    'CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.c',
    'CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.c',
    'CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.c',
    'CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.c',
    'CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.c',
    'CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_1_x_n_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_1x1_s8_fast.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_wrapper_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_3x3_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_s8_opt.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_wrapper_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_nn_depthwise_conv_s8_core.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_kernel_s8_s16.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_s8.c',
    'CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_depthwise_conv_nt_t_padded_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_depthwise_conv_nt_t_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mul_core_1x_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mul_core_4x_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mult_nt_t_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_vec_mat_mult_t_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_vec_mat_mult_t_svdf_s8.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_q7_to_q15_with_offset.c',
    'CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.c',
    'CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.c',
    'CMSIS/NN/Source/ReshapeFunctions/arm_reshape_s8.c',
    'CMSIS/NN/Source/SVDFunctions/arm_svdf_s8.c',
    'CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.c',
    'CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_fast_s16.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_s16.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_wrapper_s16.c',
    'CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_s16.c',
    'CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mul_kernel_s16.c',
    'CMSIS/NN/Source/NNSupportFunctions/arm_nn_vec_mat_mult_t_s16.c',
    'CMSIS/NN/Source/SVDFunctions/arm_svdf_state_s16_s8.c',
    'CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.c',
    'CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.c',
    ])

inc = include_directories(
  '.',
  'CMSIS/Core/Include',
  'CMSIS/DSP/Include',
  'CMSIS/NN/Include'
)


cmsis_lib = static_library('cmsis',
  include_directories : inc,
  sources : src,
  c_args : [],
  dependencies : [],
  )

cmsis_dep = declare_dependency(
  include_directories : inc,
  link_with : cmsis_lib,
  compile_args : []
  )
