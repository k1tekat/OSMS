import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, ifft

f = 16  # Частота сигнала
duration = 1  # Длительность сигнала в секундах
desired_fs = 64  # Желаемая частота дискретизации

t = np.linspace(0, duration, 1000)

#y = np.cos(6 * np.pi * f * t) + np.sin(4 * np.pi * f * t) + np.sin(10 * t)

y = 7 * np.cos(2 * np.pi *f *t + np.pi/13)
fft_result = np.fft.fft(y) # Применяем 


freq = np.fft.fftfreq(len(t)) # Вычисляем частоты

# Находим индекс компоненты с максимальной амплитудой в спектре
max_ampl_index = np.argmax(np.abs(fft_result))
max_freq = np.abs(freq[max_ampl_index])

# Определяем минимальную частоту дискретизации по теореме Котельникова-Шеннона
fs = 2 * max_freq

# Вычисляем количество отсчётов для оцифровки
num_samples = int(desired_fs * duration)

# Убедимся, что не оцифровываем больше, чем имеем
if num_samples > len(t):
    num_samples = len(t)

# Создаем массив времени и оцифрованный сигнал
digitized_t = np.linspace(0, duration, num_samples)
digitized_y = np.interp(digitized_t, t, y)

# Применяем FFT к оцифрованному сигналу
dft_result = np.fft.fft(digitized_y)

# Вычисляем частоты для оцифрованного сигнала
freq = np.fft.fftfreq(num_samples, 1.0 / desired_fs)

# Вычисляем амплитуду
magnitude = np.abs(dft_result)

# Выбираем половину спектра
half_magnitude = magnitude[:num_samples // 2]

# Находим индекс компоненты с максимальной амплитудой
max_freq_index = np.argmax(half_magnitude)
max_freq = freq[max_freq_index]

# Вычисляем объем памяти для хранения оцифрованного сигнала
memory_usage_bytes = digitized_y.nbytes

# Создаем массив времени для восстановленного сигнала
original_t = np.linspace(0, duration, 1000)

# Восстанавливаем оригинальный сигнал
reconstructed_y = np.interp(original_t, digitized_t, digitized_y)


plt.figure(figsize=(10, 6))
plt.plot(freq[:num_samples // 2], half_magnitude) # Визуализация спектра
#plt.plot(digitized_t, digitized_y, marker='o', markersize=5, linestyle='-')  # Визуализация оцифрованного сигнала
plt.title("Оцифрованный сигнал")
plt.xlabel("Время (сек)")
plt.ylabel("y(t)")
plt.grid(True)
plt.show()

print(f'Максимальная частота в спектре: {max_freq} Гц')
print(f'Минимальная частота дискретизации (согласно теореме Котельникова-Шеннона): {fs} Гц')
print(f'Частота дискретизации для оцифрованного сигнала: {desired_fs} Гц')
print(f'Количество оцифрованных отсчетов: {num_samples}')
print(f'Объем памяти для хранения оцифрованного сигнала: {memory_usage_bytes} байт')
 
plt.figure(figsize=(10, 6))
plt.plot(original_t, reconstructed_y, label="Восстановленный сигнал")
plt.plot(t, y, label="Оригинальный сигнал", linestyle='dashed')
plt.title("Оригинальный сигнал")
plt.xlabel("Время (сек)")
plt.ylabel("y(t)")
plt.grid(True)
plt.legend()
plt.show()




