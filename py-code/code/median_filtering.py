#rmnoise.py
from PIL import Image
from numpy import *
import matplotlib.pyplot as plt
import f as f

im = array(Image.open('../img/ori.bmp').convert('L'))

#中值滤波
rmnoise_im = f.centre_value_filter(im)
#保存
dist = Image.fromarray(rmnoise_im).convert('L')
dist.save('../img/dist.bmp')
#plot
plt.subplot(121)
plt.imshow(im,'gray')
plt.title('original')
plt.subplot(122)
plt.imshow(dist,'gray')
plt.title('after process')
plt.show()