import math
import matplotlib.pyplot as plt 
import numpy as np
from scipy.signal import correlate
from scipy import signal

filename_crc = 'RGR/CRC-generator/crc.txt'
filename_gold = 'RGR/GOLD-sequence/gold.txt'
filename = 'RGR/GOLD-sequence/output.txt'
Sample_rate = 1


def read_sequence_from_file(filename):
    with open(filename, 'r') as file:
        sequence = file.read().strip()
        array = np.array([int(x) for x in sequence])
    return array

crc = read_sequence_from_file(filename_crc)
data = read_sequence_from_file(filename)
gold = read_sequence_from_file(filename_gold)
data_wth_samples = np.array

data_wth_samples = np.repeat(data,Sample_rate)



print(data_wth_samples.size)
zero_arr = np.zeros(data.size*Sample_rate*2,dtype=int)
print(zero_arr.size)


print("Введите число от 0 до ", data_wth_samples.size," :" )
input_a = int(input())


for i in range(data_wth_samples.size):
    np.put(zero_arr,input_a,data_wth_samples[i])
    input_a = input_a + 1

signal = zero_arr


# Ввод значения стандартного отклонения шума с клавиатуры
s = float(input("Введите отклонение шума: "))
# Генерация шума с помощью нормального распределения
noise = np.random.normal(0, s, len(zero_arr))

noisy_signal = zero_arr + noise



gold = np.repeat(gold,Sample_rate)


result = noisy_signal[::10] 


def compute_correlat(gold, signal): 
    correlation_result = np.correlate(signal, gold, mode='full') 
    max_corr = np.max(correlation_result) 
    # поделим результат корреляции на максимальное значение в этом результате 
    normalized_corr = correlation_result / max_corr 
    return normalized_corr

def cross_correlation(signal, sync_signal):
    corr = np.correlate(signal, sync_signal, mode='full')
 
    start_idx = np.argmax(corr)  # Индекс, с которого начинается синхросигнал
    corr = corr[:int((corr.size)/2)]
    start_idx2 = np.argmax(corr)
    synced_signal = signal[start_idx:]
    synced_signal = signal[:start_idx2]
    return start_idx, synced_signal

com_col = compute_correlat(gold,noisy_signal)

plt.figure(1)
plt.plot(com_col)
plt.xlabel('Отсчеты')
plt.ylabel('Значения корреляции')
plt.title('Функция корреляции')

start_idx, synced_signal = cross_correlation(noisy_signal, gold)
print(f"Синхросигнал начинается с позиции {start_idx}, обрезанный сигнал: {synced_signal}")


print(data_wth_samples.size)

buf = data_wth_samples.size

arr = synced_signal[:buf]










plt.figure(figsize=(16,12))

plt.subplot(221)
plt.plot(data)
plt.title('начальные данные')


plt.subplot(222)
plt.plot(data_wth_samples)
plt.title('данные с сэмплами')


plt.subplot(223)
plt.plot(signal)
plt.title('новый массив')

plt.subplot(224)
plt.plot(noisy_signal)
plt.title('шум')




def demodulation_symbol(signal_arr):
    for i in range(len(signal_arr)):
        if signal_arr[i]>0.5:
            signal_arr[i]=int(1)
        else:
            signal_arr[i]=int(0)
        #print(signal[i])
    return signal_arr




de_signal = demodulation_symbol(arr)
print(de_signal)


def crc_decod(arr, M):
    arr_b = arr.copy()
    for i in range(len(arr) - len(M) + 1):
        if arr[i] == 1:
            for j in range(len(M)):
                arr[i+j] ^= M[j]
    if arr.all() == 0:
        print("\nОшибок передачи не обнаружено")
    return arr_b[1:-7]

de_signal = signal.astype(int)
decod = crc_decod(de_signal, crc)
decod = decod[9:195]

print("\nСигнал без синхронзаций и CRC: ",np.array2string(decod,separator=''), "[{}]".format(len(decod)))




def bits_to_ascii(bit_array):
    # Преобразование массива бит в строку
    bit_string = ''.join(str(bit) for bit in bit_array)
    
    # Разделение строки на 8-битные блоки
    bit_blocks = [bit_string[i:i+8] for i in range(0, len(bit_string), 8)]
    
    # Преобразование каждого 8-битного блока в целое число
    ascii_list = [int(block, 2) for block in bit_blocks]
    
    # Преобразование целых чисел в символы ASCII
    ascii_string = ''.join(chr(ascii) for ascii in ascii_list)
    
    return ascii_string

# Вывод результата
ascii_result = bits_to_ascii(decod)
print("\nПолучившийся текст: ",ascii_result)


plt.figure(figsize=(16,12))

plt.subplot(221)
plt.plot(synced_signal)
plt.title('синхросигнал')


plt.subplot(222)
plt.plot(arr)
plt.title('arr ')


plt.subplot(223)
plt.plot(de_signal)
plt.title('Приведенный массив')

plt.subplot(224)
plt.plot(decod)
plt.title('decode')
plt.show()
