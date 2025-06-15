# algorithms/counting_sort.py
from typing import List


def counting_sort(arr: List[int]) -> List[int]:
    """
    Counting Sort otimizado para ratings (valores de 1 a 10)
    """
    if not arr:
        return arr
    
    # Para ratings: valores vão de 1 a 10 (0.5 a 5.0 multiplicado por 2)
    MIN_RATING = 1
    MAX_RATING = 10
    RANGE_SIZE = MAX_RATING - MIN_RATING + 1
    
    # Criar array de contagem
    count = [0] * RANGE_SIZE
    
    # Contar ocorrências
    for v in arr:
        if MIN_RATING <= v <= MAX_RATING:
            count[v - MIN_RATING] += 1
    
    # Acumular contagens
    for i in range(1, RANGE_SIZE):
        count[i] += count[i - 1]
    
    # Construir array ordenado
    output = [0] * len(arr)
    for i in range(len(arr) - 1, -1, -1):
        if MIN_RATING <= arr[i] <= MAX_RATING:
            output[count[arr[i] - MIN_RATING] - 1] = arr[i]
            count[arr[i] - MIN_RATING] -= 1
    
    return output


def counting_sort_with_range(arr: List[int], min_val: int, max_val: int) -> List[int]:
    """
    Counting Sort genérico para valores com range específico
    """
    if not arr:
        return arr
    
    range_size = max_val - min_val + 1
    count = [0] * range_size
    
    # Contar ocorrências
    for v in arr:
        count[v - min_val] += 1
    
    # Reconstruir array ordenado
    index = 0
    for i in range(range_size):
        for j in range(count[i]):
            arr[index] = i + min_val
            index += 1
    
    return arr