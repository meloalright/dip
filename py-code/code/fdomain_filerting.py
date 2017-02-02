from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import f as f

img = np.array(Image.open('../img/lady.bmp').convert('L'))

#f:FFT变换后的
#fshift:中心化后的
f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)

#取绝对值：将复数变化成实数
#取对数的目的为了将数据变化到较小的范围（比如0-255）
s1 = np.log(np.abs(f))
s2 = np.log(np.abs(fshift))




#filter
rows = len(img)
cols = len(img[0])
mask = np.zeros(img.shape,np.uint8)
limit = 98*98

for i in range(rows):
    for j in range(cols):
        if ((0.5*rows-i)**2+(0.5*cols-j)**2) < limit:
            mask[i][j] = 1


#
# @ 2维FFT后的频域图
#
plt.subplot(221)
plt.imshow(s2,'gray')
plt.title('frequecy domain')


#
# @ 频域加低通处理
#
s2 = s2 * mask
fshift = fshift * mask
plt.subplot(222)
plt.imshow(s2,'gray')
plt.title('frequecy domain with low pass')


# 逆变换
img_back = np.fft.ifft2(fshift)
img_back = np.abs(img_back)

#
# @ 原图
#
plt.subplot(223)
plt.imshow(img,'gray')
plt.title('original')
plt.subplot(224)

#
# @ FFT去噪声处理后的图片
#
plt.imshow(img_back,'gray')
plt.title('after process')
plt.show()

dist = Image.fromarray(img_back).convert('L')
dist.save('../img/dist.bmp')