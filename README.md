# Simulacion_Tarea_2

• Capacidad de la Fila (espacios disponibles)
• Promedio de tiempo entre llegadas de trabajos (tiempo que tarda en llegar un trabajo)
• Promedio de tiempo de atención de trabajos (tiempo que tarda en atenderse un trabajo)
• Ocupación promedio de la fila (porcentaje de tiempo que la fila está ocupada)
• Total de atendidos (trabajos que llegaron y fueron atendidos)
• Total de abandonos (trabajos que llegaron y no fueron atendidos)
• Promedio de atendidos por unidad de tiempo (tasa de atención)
• Promedio de abandonos por unidad de tiempo (tasa de abandono)

Comando de ejecucion:
g++ -Wall -Wextra -g3 -Iinclude FilaGG1.cc main.cc Simulator.cc Random.cc include/checkArgs.cc -o main.exe && ./main.exe --espaciosDisponibles 4 --trabajosAProcesar 20 --slogs --elogs
