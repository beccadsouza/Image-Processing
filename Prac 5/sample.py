import numpy as np
import matplotlib.pyplot as plt
from skimage import data, color
from skimage.transform import hough_circle, hough_circle_peaks
from skimage.feature import canny
from skimage.draw import circle_perimeter
from skimage.util import img_as_ubyte
from skimage import io
from cv2 import imread

# Load picture and detect edges
# image = img_as_ubyte(data.coins()[160:230, 70:270])
# image = io.imread('Prac 5/input.png')
image = imread('Prac 5/input.png', 0)
plt.imshow(image, cmap=plt.cm.gray)
plt.show()

edges = canny(image, sigma=3, low_threshold=10, high_threshold=50)
plt.imshow(edges, cmap=plt.cm.gray)
plt.show()

# Detect two radii
hough_radii = np.arange(20, 35, 2)
hough_res = hough_circle(edges, hough_radii)

# Select the most prominent 3 circles
accums, cx, cy, radii = hough_circle_peaks(hough_res, hough_radii,total_num_peaks=3)

# Draw them
image = color.gray2rgb(image)
for center_y, center_x, radius in zip(cy, cx, radii):
    circy, circx = circle_perimeter(center_y, center_x, radius, shape=image.shape)
    image[circy, circx] = (220, 20, 20)

plt.imshow(image, cmap=plt.cm.gray)
plt.show()
