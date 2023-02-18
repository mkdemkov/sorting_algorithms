import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("../tables/time_of_size.csv")


random_0_5 = data[data['Вид массива'] == 'обычный 0-5']
size = random_0_5['Размер массива']
time = random_0_5['Время(нс)']

plt.plot(size, time)
plt.xlabel('размер массива')
plt.ylabel('время(нс)')
plt.title('значения массива - случайные от 0 до 5')
plt.show()