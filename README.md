# 📊 Algoritmos de Ordenação Não Comparativos

## Análise Comparativa de Counting Sort e Radix Sort em Diferentes Linguagens e Estruturas de Dados

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Go](https://img.shields.io/badge/Go-00ADD8?style=flat&logo=go&logoColor=white)](https://golang.org/)
[![Java](https://img.shields.io/badge/Java-ED8B00?style=flat&logo=java&logoColor=white)](https://www.java.com/)
[![Python](https://img.shields.io/badge/Python-3776AB?style=flat&logo=python&logoColor=white)](https://www.python.org/)

---

## 🎯 Visão Geral

Este projeto apresenta uma análise comparativa aprofundada dos algoritmos de ordenação **Counting Sort** e **Radix Sort**, implementados em **5 linguagens de programação** diferentes e testados com **6 estruturas de dados** distintas. O estudo utiliza o dataset **MovieLens 25M** para avaliar performance em cenários reais.

### 🔬 Objetivos

- Analisar a eficiência de algoritmos não comparativos sob restrições de complexidade linear
- Comparar performance entre linguagens compiladas vs interpretadas
- Avaliar impacto de estruturas lineares vs dinâmicas no desempenho
- Validar complexidade teórica Θ(n+k) em implementações práticas

---

---

## 🚀 Como Executar

### 📋 Pré-requisitos

```bash
# Compiladores necessários
gcc --version          # Para C
g++ --version          # Para C++
go version             # Para Go
java -version          # Para Java
python3 --version      # Para Python

# Dataset MovieLens 25M
wget https://files.grouplens.org/datasets/movielens/ml-25m.zip
unzip ml-25m.zip
cp ml-25m/ratings.csv datasets/
```

## 📊 Estruturas de Dados Testadas

| Estrutura | Tipo Linear | Tipo Dinâmico |
|-----------|-------------|---------------|
| **Lista** | Array/Vector | Lista Encadeada |
| **Pilha** | Array Circular | Pilha com Nós |
| **Fila** | Array Circular | Fila com Nós |

### 🔄 Processo de Benchmark

1. **Carregamento**: Dados → Estrutura de Dados
2. **Conversão**: Estrutura → Array
3. **Ordenação**: Counting Sort no Array
4. **Reconversão**: Array → Estrutura
5. **Medição**: Tempo + Memória

---

## 📈 Resultados Principais

### ⚡ Performance de Tempo (1M elementos)

| Linguagem | Lista Linear | Lista Dinâmica | Melhor Estrutura |
|-----------|--------------|----------------|------------------|
| **C** | 6.42ms | 29.29ms | Pilha Linear (4.06ms) |
| **Go** | 19.02ms | 105.85ms | Pilha Linear (17.41ms) |
| **Java** | 11.70ms | 27.60ms | Lista Linear (11.70ms) |
| **C++** | 121.20ms | 72.20ms | Lista Dinâmica (72.20ms) |
| **Python** | 241.38ms | 910.31ms | Lista Linear (241.38ms) |

### 💾 Consumo de Memória (1M elementos)

| Linguagem | Estruturas Lineares | Estruturas Dinâmicas |
|-----------|---------------------|----------------------|
| **C/C++** | 3.81 MB | 15.26 MB |
| **Java** | 3.81 MB | 15.26 MB |
| **Go** | 15.27 MB | 45.78 MB |
| **Python** | 15.26 MB | 91.98 MB |

### 🏆 Ranking Geral (1M elementos)

1. **🥇 C** - Pilha Linear: **4.06ms**
2. **🥈 C** - Lista Linear: **6.42ms**
3. **🥉 Java** - Lista Linear: **11.70ms**
4. **4º Go** - Pilha Linear: **17.41ms**
5. **5º Java** - Fila Dinâmica: **21.20ms**

---

## 🔬 Análise Técnica

### ✅ Vantagens do Counting Sort

- **Complexidade Linear**: Θ(n+k) onde k=10 (ratings 0.5-5.0)
- **Estabilidade**: Preserva ordem relativa de elementos iguais
- **Previsibilidade**: Performance consistente independente da distribuição

### 📊 Dataset: MovieLens 25M

- **Formato**: `userId,movieId,rating,timestamp`
- **Ratings**: 0.5 → 5.0 (incrementos de 0.5)
- **Transformação**: `rating_int = rating × 2` (1-10)
- **Vantagem**: k constante e pequeno = Θ(n)

### 🎯 Fatores de Performance

1. **Linguagem**:
   - Compiladas > Interpretadas
   - Controle manual de memória > GC automático

2. **Estrutura de Dados**:
   - Lineares > Dinâmicas (localidade de referência)
   - Arrays contíguos > Nós dispersos

3. **Volume de Dados**:
   - Escalabilidade linear confirmada
   - Overhead mais visível em grandes volumes

---

## 🛠️ Tecnologias Utilizadas

### Linguagens
- **C** - Controle de baixo nível
- **C++** - Orientação a objetos + performance
- **Go** - Concorrência moderna + GC eficiente
- **Java** - JVM + otimizações JIT
- **Python** - Simplicidade + flexibilidade

### Ferramentas
- **Compiladores**: GCC, G++, OpenJDK
- **Build Systems**: Make, CMake, Go Modules
- **Dataset**: MovieLens 25M
- **SO**: Linux Ubuntu 24.04 LTS

---

## 📚 Artigo Científico

Este projeto foi documentado em um artigo científico completo seguindo padrões IEEE:

**"Ordenações Não Comparativas: Counting Sort e Radix Sort sob Restrições de Complexidade Linear"**

### 📖 Seções do Artigo

1. **Introdução** - Contexto e importância histórica
2. **Metodologia** - Algoritmos e pseudocódigos
3. **Modelos de Aplicação** - Casos de uso e limitações
4. **Resultados e Discussão** - Análise comparativa detalhada
5. **Conclusões** - Insights e trabalhos futuros

---

## 👥 Equipe

- **Ahmed Amer Hachem** - CEFET-MG
- **Bernardo Silva Andrade** - CEFET-MG  
- **João Antônio Melo Zacarias** - CEFET-MG
- **João Pedro Silva Siqueira** - CEFET-MG
- **João Vitor Lobato Romualdo** - CEFET-MG

---

## 📄 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

---

## 📞 Contato

Para dúvidas ou colaborações:
- **Email**: joaopedrosilvasiqueira1@gmail.com
- **Instituição**: CEFET-MG - Departamento de Engenharia de Computação
- **Localização**: Divinópolis, Brasil

---

## 🙏 Agradecimentos

- **CEFET-MG** pelo suporte acadêmico
- **MovieLens/GroupLens** pelo dataset público
- **Comunidade Open Source** pelas ferramentas utilizadas
