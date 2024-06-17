import pandas as pd
import numpy as np
import os
import platform
import sys

import matplotlib.pyplot as plt

file_dir = os.path.dirname(__file__)
sys.path.append(file_dir)

# Load benchmark data from CSV
if platform.platform().startswith('Windows'):
    df_enc = pd.read_csv('benchmark_results_enc_win.csv')
    df_dec = pd.read_csv('benchmark_results_dec_win.csv')
else:
    df_enc = pd.read_csv('benchmark_results_enc_linux.csv')
    df_dec = pd.read_csv('benchmark_results_dec_linux.csv')


# Round input sizes to the nearest kilobyte (assuming sizes are in bytes)
df_enc['Size(KB)'] = np.round(df_enc['Size(Bytes)'] / 1024)

# Group by rounded input sizes and calculate average time
grouped_enc = df_enc.groupby('Size(KB)').mean().reset_index()

# Round input sizes to the nearest kilobyte (assuming sizes are in bytes)
df_dec['Size(KB)'] = np.round(df_dec['Size(Bytes)'] / 1024)

# Group by rounded input sizes and calculate average time
grouped_dec = df_dec.groupby('Size(KB)').mean().reset_index()

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(grouped_enc['Size(KB)'], grouped_enc['Time(Microseconds)'],
         marker='o', linestyle='-', color='b', label='AES Encryption Time')
plt.plot(grouped_dec['Size(KB)'], grouped_dec['Time(Microseconds)'],
         marker='o', linestyle='-', color='r', label='AES Decryption Time')
plt.xlabel('Input Size (KB)')
plt.ylabel('Time (Microseconds)')
if platform.platform().startswith('Windows'):
    plt.title('AES Encryption and Decryption Time on Windows')
else:
    plt.title('AES Encryption and Decryption Time on Linux')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
