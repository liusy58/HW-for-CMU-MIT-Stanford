import util as u
import numpy as np


def convert_text_2_matrix(cipher_text):
    """
    Input:
    text

    Return:
    matrix
    """
    symbol_2_index = {
        "A": 0,
        "B": 1,
        "C": 2,
        "D": 3,
        "E": 4,
        "F": 5,
        "G": 6,
        "H": 7,
        "I": 8,
        "J": 9,
        "K": 10,
        "L": 11,
        "M": 12,
        "N": 13,
        "O": 14,
        "P": 15,
        "Q": 16,
        "R": 17,
        "S": 18,
        "T": 19,
        "U": 20,
        "V": 21,
        "W": 22,
        "X": 23,
        "Y": 24,
        "Z": 25,
        "_": 26,
        ".": 27,
        ",": 28,
        "?": 29,
        "!": 30
    }
    matrix = []
    for m in cipher_text:
        matrix.append(symbol_2_index[m])
    matrix = np.array(matrix).reshape(3, -1)
    return matrix


def convert_matrix_2_text(res_matrix):
    index_2_symbol = {
        0: "A",
        1: "B",
        2: "C",
        3: "D",
        4: "E",
        5: "F",
        6: "G",
        7: "H",
        8: "I",
        9: "J",
        10: "K",
        11: "L",
        12: "M",
        13: "N",
        14: "O",
        15: "P",
        16: "Q",
        17: "R",
        18: "S",
        19: "T",
        20: "U",
        21: "V",
        22: "W",
        23: "X",
        24: "Y",
        25: "Z",
        26: "_",
        27: ".",
        28: ",",
        29: "?",
        30: "!"
    }
    res = ""
    for index in res_matrix.flatten():
        res += index_2_symbol[index]
    return res


def decode(cipher_text, decode_matrix):
    cipher_matrix = convert_text_2_matrix(cipher_text)

    res_matrix = np.dot(decode_matrix, cipher_matrix)
    res_matrix = np.mod(res_matrix, 31)

    res = convert_matrix_2_text(res_matrix)
    return res


if __name__ == "__main__":
    cipher_text = "WPK_FJEIIXZ.OQFPM_"
    key = "4 9 -2 3 5 7 1 -6 11"

    encode_matrix = np.fromstring(key, dtype=int, sep=" ").reshape(3, 3)
    decode_matrix = u.inv_key(encode_matrix)

    plain_text = decode(cipher_text, decode_matrix)

    print(plain_text)
