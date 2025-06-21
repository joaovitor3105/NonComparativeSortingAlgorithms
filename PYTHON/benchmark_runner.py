# benchmark_runner.py
import time
import gc
import sys
import platform
import psutil
import tracemalloc  
from datetime import datetime
from typing import List, Dict, Callable
from dataclasses import dataclass

# Adicionar diretórios ao path
sys.path.append('.')

# Importar módulos do projeto
from algorithms.counting_sort import counting_sort
# from algorithms.radix_sort import radix_sort  # REMOVIDO
from structures.list_linear import ListLinear
from structures.list_dynamic import ListDynamic
from structures.queue_linear import QueueLinear
from structures.queue_dynamic import QueueDynamic
from structures.stack_linear import StackLinear
from structures.stack_dynamic import StackDynamic
from utils.csv_reader import load_ratings_csv, generate_test_data
from utils.data_structure import DataStructure


# --- Estruturas de Dados e Funções de Medição Refatoradas ---

# ALTERADO: dataclass simplificado para um único resultado
@dataclass
class BenchmarkResult:
    """Resultado de um único benchmark para uma estrutura e tamanho."""
    structure_name: str
    structure_type: str
    data_size: int
    time_ms: float
    memory_mb: float

# REMOVIDO: A classe BenchmarkRun não é mais necessária

def get_memory_usage_bytes() -> float:
    """Retorna o uso de memória atual em bytes."""
    return psutil.Process().memory_info().rss

def force_gc():
    """Força coleta de lixo para estabilizar a medição de memória."""
    gc.collect()
    time.sleep(0.1)

# NOVO: Função para medir APENAS o tempo de execução
def medir_tempo(ds: DataStructure, data: List[int]) -> float:
    """Executa o ciclo completo de ordenação e retorna o tempo em milissegundos."""
    start_time = time.perf_counter()

    ds.from_array(data)
    arr = ds.to_array()
    sorted_arr = counting_sort(arr)
    ds.from_array(sorted_arr)

    end_time = time.perf_counter()
    return (end_time - start_time) * 1000  # Converte para milissegundos

# NOVO: Função para medir a memória usando tracemalloc
def medir_memoria(ds: DataStructure, data: List[int]) -> float:
    """Executa o ciclo completo de ordenação e retorna o PICO de memória usada em bytes."""
    
    tracemalloc.start() # Inicia o monitoramento

    # Limpa a estrutura para garantir que a medição seja apenas da execução atual
    ds.from_array([]) 
    
    # --- Executa a mesma lógica da medição de tempo ---
    ds.from_array(data)
    arr = ds.to_array()
    sorted_arr = counting_sort(arr)
    ds.from_array(sorted_arr)
    # --- Fim da lógica ---

    # Captura o uso de memória atual e o pico
    current, peak = tracemalloc.get_traced_memory()
    
    tracemalloc.stop() # Para o monitoramento
    
    # Limpa a estrutura para não impactar a próxima medição
    ds.from_array([])
    gc.collect()

    return peak # Retorna o PICO de memória alocada durante o bloco


def log_system_info(log_file):
    """Registra informações do sistema no log."""
    log_file.write("="*60 + "\n")
    log_file.write("     BENCHMARK - PYTHON - COUNTING SORT      \n")
    log_file.write("="*60 + "\n")
    log_file.write(f"Data/Hora: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
    log_file.write(f"Sistema: {platform.system()}/{platform.machine()}\n")
    log_file.write(f"Python: {platform.python_version()}\n")
    log_file.write("="*60 + "\n\n")


def create_summary_table(log_file, all_results: Dict[str, Dict[int, BenchmarkResult]], sizes: List[int]):
    """Cria e salva a tabela resumo final no arquivo de log."""
    structures_order = [
        "Lista Linear", "Lista Dinâmica",
        "Fila Linear", "Fila Dinâmica",
        "Pilha Linear", "Pilha Dinâmica"
    ]
    
    log_file.write("\n" + "="*60 + "\n")
    log_file.write("                   TABELA RESUMO FINAL\n")
    log_file.write("="*60 + "\n\n")
    
    # Cabeçalho da tabela
    header = f"{'Estrutura':<20} | {'Tipo':<8} | "
    for size in sizes:
        header += f"{size:>10} | "
    log_file.write(header + "\n")
    
    separator = "-"*20 + "-+-" + "-"*8 + "-+-"
    for _ in sizes:
        separator += "-"*11 + "+-"
    log_file.write(separator + "\n")
    
    # Seção de Tempo
    log_file.write("\nTEMPO (ms):\n")
    for struct_name in structures_order:
        if struct_name in all_results:
            results_by_size = all_results[struct_name]
            struct_type = results_by_size[sizes[0]].structure_type
            line = f"{struct_name:<20} | {struct_type:<8} | "
            for size in sizes:
                line += f"{results_by_size[size].time_ms:10.2f} | "
            log_file.write(line + "\n")

    # Seção de Memória
    log_file.write("\nMEMÓRIA (MB):\n")
    for struct_name in structures_order:
        if struct_name in all_results:
            results_by_size = all_results[struct_name]
            struct_type = results_by_size[sizes[0]].structure_type
            line = f"{struct_name:<20} | {struct_type:<8} | "
            for size in sizes:
                line += f"{results_by_size[size].memory_mb:10.2f} | "
            log_file.write(line + "\n")


def main():
    """Função principal que orquestra o benchmark."""
    log_filename = f"benchmark_python_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"
    
    with open(log_filename, 'w', encoding='utf-8') as log_file:
        log_system_info(log_file)
        
        print("=== BENCHMARK PYTHON - COUNTING SORT ===")
        print(f"Resultados serão salvos em: {log_filename}")
        
        # ALTERADO: Apenas um algoritmo, sem loop de execuções
        sizes_to_test = [100, 1000, 10000, 100000, 1000000]
        
        # Dicionário para armazenar todos os resultados
        all_results: Dict[str, Dict[int, BenchmarkResult]] = {}

        # Mapeamento de estruturas para facilitar a criação
        structures_to_test: Dict[str, Callable[[int], DataStructure]] = {
            "Lista Linear": lambda size: ListLinear(size),
            "Lista Dinâmica": lambda size: ListDynamic(),
            "Fila Linear": lambda size: QueueLinear(size),
            "Fila Dinâmica": lambda size: QueueDynamic(),
            "Pilha Linear": lambda size: StackLinear(size),
            "Pilha Dinâmica": lambda size: StackDynamic(),
        }
        
        csv_path = "/home/john/Desktop/NonComparativeSortingAlgorithms/ml-25m/ratings.csv"

        for size in sizes_to_test:
            print(f"\n--- Testando com {size} elementos ---")
            log_file.write(f"\n=== TAMANHO DO DATASET: {size} elementos ===\n")

            data = load_ratings_csv(csv_path, size)
            if not data:
                print(f"Aviso: Não foi possível ler o CSV. Gerando dados de teste para o tamanho {size}.")
                data = generate_test_data(size)
            
            for name, create_func in structures_to_test.items():
                ds_instance = create_func(size)
                struct_type = "linear" if "Linear" in name else "dynamic"
                
                print(f"  {name:<20}: ", end='', flush=True)
                
                # Executa medições separadas
                tempo_ms = medir_tempo(ds_instance, data)
                memoria_bytes = medir_memoria(ds_instance, data)
                
                memoria_mb = memoria_bytes / (1024.0 * 1024.0)

                # Armazena o resultado único
                result = BenchmarkResult(
                    structure_name=name,
                    structure_type=struct_type,
                    data_size=size,
                    time_ms=tempo_ms,
                    memory_mb=memoria_mb
                )
                
                if name not in all_results:
                    all_results[name] = {}
                all_results[name][size] = result
                
                print(f"Concluído (Tempo: {tempo_ms:.2f}ms, Memória: {memoria_mb:.2f}MB)")
                log_file.write(f"{name} -> Tempo: {tempo_ms:.4f} ms, Memória: {memoria_mb:.4f} MB\n")

        # Gerar a tabela resumo final no arquivo de log
        create_summary_table(log_file, all_results, sizes_to_test)
        
        log_file.write("\n" + "="*60 + "\n")
        log_file.write("                 BENCHMARK FINALIZADO\n")
        log_file.write("="*60 + "\n")
    
    print(f"\n✅ Benchmark concluído! Resultados salvos em: {log_filename}")


if __name__ == "__main__":
    main()