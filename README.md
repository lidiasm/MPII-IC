# Inteligencia Computacional.

## Máster en Ingeniería Informática 19-20.

### Teoría

* Trabajo y presentación sobre la **lógica difusa aplicada a la selección de personal en empresas**.

### Prácticas

1. **Redes Neuronales**. Implementación de diferentes arquitecturas de redes neuronales aplicadas sobre el problema *Mnist: reconocimiento de dígitos*. Para ello se ha utilizado Java como lenguaje de programación sin hacer uso de librerías específicas, todas las implementaciones de la práctica son hechas por mi. Estas son las siguientes:
  - Perceptrón simple lineal. Tasa de error: 14.81%
  - Multicapa con una capa oculta. Tasa de error: **1.83%**.
  - Multicapa con dos capas ocultas: 1.95%.
  - CNN incompleta, no funciona correctamente.

2. **Algoritmos Genéticos**. Implementación de diferentes variantes de los algoritmos genéticos aplicados sobre el problema del *QAP*. Para ello se ha utilizado C++ como lenguaje de programación debido a su eficiencia y tampoco se han utilizado librerías de terceros, la implementación es propia. Las variantes que se han desarrollado son las siguientes:
  - Algoritmos Genéticos Generacionales con Elitismo con operadores de cruce basados en posición y el OX.
  - Algoritmos Genéticos Estacionarios con operadores de cruce basados en posición y el OX.
  - Algoritmos Meméticos: combinación de las dos variantes anteriores con el algoritmo de la Búsqueda Local.
  - Variante Baldwiniana: combinación de las dos variantes originales junto con el algoritmo *2-opt* para calcular el coste de las solucioens sin utilizar los cromosomas obtenidos.
  - Variante Lamarckiana: combinación de las dos variantes originales junto con el algoritmo *2-opt* para buscar soluciones mejores. **Mejor solución obtenida: 44919026**, con 20 individuos por población y 1.000 iteraciones aplicando el algoritmo *2-opt* cada diez generaciones.

