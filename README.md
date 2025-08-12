# philosophers

*Implementación del clásico problema de los filósofos comensales en C, parte del Common Core de 42 Madrid.*

---

## 📌 Descripción

Simulación del problema de los filósofos comensales en C utilizando concurrencia y sincronización. Cada filósofo alterna entre pensar y comer, usando forks compartidos y evitando condiciones de carrera y deadlocks.

**Características destacadas**:
- Uso de hilos (`pthread`) con **mutex** y/o **condition variables**.
- Gestión de sincronización adecuada para evitar deadlocks.
- Control de tiempos y estados: `time_to_die`, `time_to_eat`, `time_to_sleep`.
- Monitorización de filósofos y terminación segura al completar sus comidas o al morir.
- Parsing robusto y control de errores en los parámetros.

---

## ⚙️ Cómo compilar

```bash
make
```

---

## 🚀 Ejecución

```bash
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_times_must_eat]
```

Ejemplo:

```bash
./philo 5 800 200 200 7
```

Donde:
- `num_philosophers`: número de filósofos y forks.
- `time_to_die`: tiempo máximo sin comer (ms).
- `time_to_eat`, `time_to_sleep`: tiempos de cada acción (ms).
- `num_times_must_eat` (opcional): cuántas veces debe comer cada filósofo antes de terminar.

---

## ⏱ Ejemplo básico

```bash
philo 5 800 200 200
```

Salida esperada (simplificada):

```
0 1 has taken a fork
0 1 is eating
1 2 has taken a fork
1 2 is eating
...
```

---

## 📂 Estructura del proyecto

```
philosophers/
├── src/         # Código fuente (.c)
├── inc/         # Cabeceras (.h)
├── Makefile
└── README.md
```

---

## 📋 Dependencias

- Sistema operativo Unix/Linux
- Compilador `cc`
- `make`
- Biblioteca `pthread`

---

## 🛠️ Tecnologías utilizadas

- **Lenguaje:** C  
- **Herramientas:** `make`, `git`, `pthread`  
- **Conceptos:** concurrencia, sincronización, hilos, mutex, condiciones, time‑based control

---

## 🎯 Sobre el proyecto

Desarrollado como parte del Common Core en 42 Madrid, este proyecto profundiza en los fundamentos de concurrencia y sincronización en sistemas operativos, además de reforzar habilidades en programación en C y diseño de algoritmos seguros.

---
