# algorithms/radix_sort.py
from typing import List


def get_max(arr: List[int]) -> int:
    """Encontra o valor máximo no array"""
    return max(arr) if arr else 0


def counting_sort_for_radix(arr: List[int], exp: int) -> None:
    """
    Counting sort modificado para Radix Sort
    Ordena baseado no dígito representado por exp
    """
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    
    # Contar ocorrências de cada dígito
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1
    
    # Calcular posições acumuladas
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # Construir array ordenado
    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1
    
    # Copiar de volta para o array original
    for i in range(n):
        arr[i] = output[i]


def radix_sort(arr: List[int]) -> List[int]:
    """
    Radix Sort (LSD - Least Significant Digit)
    """
    if not arr:
        return arr
    
    # Fazer cópia para não modificar original
    result = arr.copy()
    
    # Encontrar o número máximo
    max_num = get_max(result)
    
    # Aplicar counting sort para cada dígito
    exp = 1
    while max_num // exp > 0:
        counting_sort_for_radix(result, exp)
        exp *= 10
    
    return result