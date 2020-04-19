import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


def svd(img, k):
    width, height, channels = img.shape
    res_img = np.zeros(shape=(width, height, channels))
    for channel in range(channels):
        img_channel = img[:, :, channel]
        u, s, v_T = np.linalg.svd(img_channel)

        s[k:] = 0
        s_matrix = np.zeros(shape=(width, height), dtype=float)
        for j in range(len(s)):
            s_matrix[j, j] = s[j]
        img_channel_compress = np.dot(np.dot(u, s_matrix), v_T)
        img_channel_compress -= img_channel_compress.min()
        img_channel_compress /= img_channel_compress.max()
        img_channel_compress *= 225
        res_img[:, :, channel] = img_channel_compress
    return res_img


def cal_error(img, img_compress):
    original = img.ravel().astype(float)
    compress = img_compress.ravel().astype(float)
    error = np.linalg.norm(original - compress) / len(original)
    return error


if __name__ == '__main__':
    img = Image.open("man.png")

    img = np.array(img)
    k_list = [1, 5, 50, 150, 400, 1050, 1289]
    errors = []

    for k in k_list:
        img_compress = svd(img, k)
