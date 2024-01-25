import math
import matplotlib.pyplot as plt 
import numpy as np
from scipy.signal import correlate
from scipy import signal



filename_crc = 'RGR/CRC-generator/crc.txt'
filename_gold = 'RGR/GOLD-sequence/gold.txt'
filename = 'RGR/GOLD-sequence/output.txt'