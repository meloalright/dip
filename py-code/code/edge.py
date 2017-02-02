from PIL import Image
from numpy import *
import matplotlib.pyplot as plt
import f as f

im = array(Image.open('../img/ori.bmp').convert('L'))

#X方向的求导运算
'''
  -1 0 1
[ -2 0 2 ]  is equal this sobel
  -1 0 1
'''
imx = f.sobel_x(im)

#Y方向的求导运算
'''
  -1 -2 -1
[  0  0  0 ]  is equal this sobel
   1  2  1
'''
imy = f.sobel_y(im)

magnitude = zeros(im.shape)
parameter = 0.3#参数
#取一下xy二维方向导数
magnitude = parameter * sqrt(imx**2 + imy**2)

#二分的低通滤波器处理一下
magnitude = f.binary_low_pass(magnitude)

#保存
dist = Image.fromarray(magnitude).convert('L')
dist.save('../img/dist.bmp')




