# main.py
import sys
sys.path.append('.')

from algorithms.counting_sort import counting_sort
from algorithms.radix_sort import radix_sort
from structures.list_linear import ListLinear
from structures.list_dynamic import ListDynamic
from utils.csv_reader import load_ratings_csv, generate_test_data


def demonstrate_usage(data):
    """Demonstra o uso das estruturas e algoritmos"""
    print(f"\nDados originais (primeiros 10): {data[:10]}")
    
    # Exemplo com Lista Linear
    print("\n=== Lista Linear com Counting Sort ===")
    list_linear = ListLinear(len(data) + 100)
    list_linear.from_array(data)
    
    # Converter para array, ordenar e reconverter
    arr = list_linear.to_array()
    sorted_arr = counting_sort(arr)
    list_linear.from_array(sorted_arr)
    
    result = list_linear.to_array()
    print(f"Primeiros 10 elementos ordenados: {result[:10]}")
    print(f"Últimos 10 elementos ordenados: {result[-10:]}")
    
    # Exemplo com Lista Dinâmica e Radix Sort
    print("\n=== Lista Dinâmica com Radix Sort ===")
    list_dynamic = ListDynamic()
    list_dynamic.from_array(data)
    
    arr = list_dynamic.to_array()
    sorted_arr = radix_sort(arr)
    list_dynamic.from_array(sorted_arr)
    
    result = list_dynamic.to_array()
    print(f"Primeiros 10 elementos ordenados: {result[:10]}")
    print(f"Últimos 10 elementos ordenados: {result[-10:]}")


def main():
    print("=== Ordenação Não Comparativa em Python ===")
    
    # Carregar dados do CSV ou gerar dados de teste
    csv_path = "/home/john/Desktop/NonComparativeSortingAlgorithms/ml-25m/ratings.csv"
    data = load_ratings_csv(csv_path, 1000)
    
    if not data:
        print("\nUsando dados de teste...")
        data = generate_test_data(1000)
    
    # Demonstrar uso
    demonstrate_usage(data)
    
    # Para executar benchmark completo
    print("\n" + "="*50)
    print("Para executar o benchmark completo, use:")
    print("python benchmark_runner.py")
    print("="*50)


if __name__ == "__main__":
    main()