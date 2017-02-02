from numpy import *
#filter and sobel

#x方向的sobel运算子求导运算
def sobel_x(im):
    width = len(im)
    height = len(im[0])
    imx = zeros(im.shape)
    for i in range(1,width-1):
        for j in range(1,height-1):
            imx[i][j] = -im[i-1][j-1] + (-2*im[i-1][j]) + (-im[i-1][j+1]) + im[i+1][j-1] + 2*im[i+1][j] + im[i+1][j+1]
    return imx

#y方向的sobel运算子求导运算
def sobel_y(im):
    width = len(im)
    height = len(im[0])
    imy = zeros(im.shape)
    for i in range(1,width-1):
        for j in range(1,height-1):
            imy[i][j] = -im[i-1][j-1] + (im[i-1][j+1]) + (-2*im[i][j-1]) + 2*im[i][j+1] + (-im[i+1][j-1]) + im[i+1][j+1]
    return imy

#陡峭的低通滤波
def binary_low_pass(im):
    width = len(im)
    height = len(im[0])
    for i in range(width):
        for j in range(height):
            if im[i][j] >= 198:
                im[i][j] = 255
    return im

#quick sort
def quickSort(arr):
    less = []
    pivotList = []
    more = []
    if len(arr) <= 1:
        return arr
    else:
        pivot = arr[0]      #将第一个值做为基准
        for i in arr:
            if i < pivot:
                less.append(i)
            elif i > pivot:
                more.append(i)
            else:
                pivotList.append(i)
        less = quickSort(less)      #得到第一轮分组之后，继续将分组进行下去。
        more = quickSort(more)
        return less + pivotList + more


#中值滤波器
def centre_value_filter(im):
    width = len(im)
    height = len(im[0])
    for i in range(1,width-1):
        for j in range(1,height-1):
            arr = [im[i-1][j-1],im[i][j-1],im[i+1][j-1],im[i-1][j],im[i][j],im[i+1][j],im[i-1][j+1],im[i][j+1],im[i+1][j+1],]
            im[i][j] = quickSort(arr)[4]
    return im