import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import platform
import sys

file_dir = os.path.dirname(__file__)
sys.path.append(file_dir)

# Load benchmark data from CSV
if platform.platform().startswith('Windows'):
    df = pd.read_csv('benchmark_results_win.csv')
else:
    df = pd.read_csv('benchmark_results_linux.csv')


# Round input sizes to the nearest kilobyte (assuming sizes are in bytes)
df['Size(KB)'] = np.round(df['Size(Bytes)'] / 1024)

# Group by rounded input sizes and calculate average time
grouped = df.groupby('Size(KB)').mean().reset_index()

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(grouped['Size(KB)'], grouped['Time(Microseconds)'],
         marker='o', linestyle='-', color='b', label='AES Encryption Time')
plt.title('AES Encryption Time vs Input Size')
plt.xlabel('Input Size (KB)')
plt.ylabel('Time (Microseconds)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
