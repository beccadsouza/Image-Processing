import cv2

img = cv2.imread('image.png')

red_sum = 0
blue_sum = 0
green_sum = 0

no_pixels = len(img)*len(img[0])

for i in range(len(img)):
    for j in range(len(img[0])):
        red_sum += img[i][j][0]
        blue_sum += img[i][j][1]
        green_sum += img[i][j][2]

red_mean = red_sum/no_pixels
green_mean = green_sum/no_pixels
blue_mean = blue_sum/no_pixels

print('Mean of the Red Channel : {0}'.format(red_mean))
print('Mean of the Green Channel : {0}'.format(green_mean))
print('Mean of the Blue Channel : {0}'.format(blue_mean))

red_sum = 0
blue_sum = 0
green_sum = 0

for i in range(len(img)):
    for j in range(len(img[0])):
        red_sum += (img[i][j][0] - red_mean)**2
        green_sum += (img[i][j][1] - green_mean)**2
        blue_sum += (img[i][j][2] - blue_mean)**2

red_sd = red_sum/no_pixels
green_sd = green_sum/no_pixels
blue_sd = blue_sum/no_pixels

print('SD of the Red Channel : {0}'.format(red_sd**0.5))
print('SD of the Green Channel : {0}'.format(green_sd**0.5))
print('SD of the Blue Channel : {0}'.format(blue_sd**0.5))
