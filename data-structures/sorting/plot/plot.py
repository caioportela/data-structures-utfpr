import numpy as np
import matplotlib.pyplot as plt

comparisons = []
exchanges = []
execution_time = []

def data_input(path, a=comparisons, b=exchanges, c=execution_time):
	comps = []
	chngs = []
	exec_time = []

	input_file = open(path)

	for _ in range(12):
		comp_treat =[]
		exc_treat = []
		time_treat = []

		for __ in range(100):
			line = input_file.readline().split()

			comp_treat.append(int(line[0]))
			exc_treat.append(int(line[1]))
			time_treat.append(float(line[2]))
		
		input_file.readline()

		comps.append(np.mean(comp_treat))
		chngs.append(np.mean(exc_treat))
		exec_time.append(np.mean(time_treat))


	input_file.close()

	comparisons.append(comps)
	exchanges.append(chngs)
	execution_time.append(exec_time)

def plot_comparisons():
	ax = plt.subplot(131)
	ax.plot(size, comparisons[0], label='Bubble Sort')
	ax.plot(size, comparisons[1], label='Insertion Sort')
	ax.plot(size, comparisons[2], label='Merge Sort')
	ax.plot(size, comparisons[3], label='Quick Sort')
	ax.set_yscale('log')
	plt.legend()

	plt.title('Comparações')
	plt.xlabel('Tamanho da Sequência')
	plt.ylabel('Número de Comparações')

def plot_exchanges():
	ax = plt.subplot(132)
	ax.plot(size, exchanges[0], label='Bubble Sort')
	ax.plot(size, exchanges[1], label='Insertion Sort')
	ax.plot(size, exchanges[2], label='Merge Sort')
	ax.plot(size, exchanges[3], label='Quick Sort')
	ax.set_yscale('log')
	plt.legend()

	plt.title('Trocas')
	plt.xlabel('Tamanho da Sequência')
	plt.ylabel('Número de Trocas')

def plot_time():
	ax = plt.subplot(133)
	ax.plot(size, execution_time[0], label='Bubble Sort')
	ax.plot(size, execution_time[1], label='Insertion Sort')
	ax.plot(size, execution_time[2], label='Merge Sort')
	ax.plot(size, execution_time[3], label='Quick Sort')
	ax.set_yscale('log')
	plt.legend()

	plt.title('Tempo de Execução')
	plt.xlabel('Tamanho da Sequência')
	plt.ylabel('Tempo de Execução (s)')

size = [10*(2**x) for x in range(1, 13)]

data_input('out/bubble_semi.txt')
data_input('out/insrt_semi.txt')
data_input('out/quick_semi.txt')
data_input('out/merge_semi.txt')

#plt.figure(figsize=(10,4))
plt.figure(figsize=(13, 5))
plt.suptitle('Sequências Semi-Ordenadas', fontsize=16)
plt.subplots_adjust(left=0.08, right=0.98, wspace=0.3, top=0.85)

plot_comparisons()
plot_exchanges()
plot_time()

plt.show()
#plt.savefig('APS/Sequências Semi-Ordenadas.png')
