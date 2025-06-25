import time
import gc
import sys
import platform
import tracemalloc
from datetime import datetime
from typing import List, Dict, Callable
from dataclasses import dataclass

# Adicionar diretórios ao path
sys.path.append('.')

# Importar módulos do projeto
from algorithms.counting_sort import counting_sort
from algorithms.radix_sort import radix_sort # Re-added for completeness, though not used in the specific benchmark loop by default
from structures.list_linear import ListLinear
from structures.list_dynamic import ListDynamic
from structures.queue_linear import QueueLinear
from structures.queue_dynamic import QueueDynamic
from structures.stack_linear import StackLinear
from structures.stack_dynamic import StackDynamic
from utils.csv_reader import load_ratings_csv, generate_test_data
from utils.data_structure import DataStructure


# --- Estruturas de Dados e Funções de Medição Refatoradas ---

@dataclass
class BenchmarkResult:
    """Resultado de um único benchmark para uma estrutura e tamanho."""
    structure_name: str
    structure_type: str
    data_size: int
    time_ms: float
    memory_mb: float

def get_memory_usage_bytes() -> float:
    """Retorna o uso de memória atual em bytes."""
    process = psutil.Process()
    return process.memory_info().rss

def force_gc():
    """Força coleta de lixo para estabilizar a medição de memória."""
    gc.collect()
    time.sleep(0.05) # Small sleep to allow GC to complete if heavy

# Function to perform the full sort cycle for time measurement
def perform_sort_cycle(ds: DataStructure, data: List[int]):
    """Performs the data insertion, conversion, sorting, and reconversion."""
    ds.from_array(data)
    arr = ds.to_array()
    sorted_arr = counting_sort(arr) # Using counting_sort as specified
    ds.from_array(sorted_arr)
    # Important: Check if sorted_arr is actually sorted and matches expected
    # This check is crucial for correctness validation within the main loop.
    return sorted_arr

def medir_tempo(ds: DataStructure, data: List[int], sort_func: Callable) -> float:
    """Executa o ciclo completo de ordenação e retorna o tempo em milissegundos."""
    # We pass the sort_func to allow flexibility if other sorts were to be used.
    # The actual sorting happens inside perform_sort_cycle.
    start_time = time.perf_counter()
    
    ds.from_array(data)
    arr = ds.to_array()
    sorted_arr = sort_func(arr) # Use the provided sort function
    ds.from_array(sorted_arr)

    end_time = time.perf_counter()
    return (end_time - start_time) * 1000  # Converte para milissegundos

def medir_memoria(ds: DataStructure, data: List[int], sort_func: Callable) -> float:
    """Executa o ciclo completo de ordenação e retorna o PICO de memória usada em bytes."""
    
    tracemalloc.start() 
    # Force GC before starting tracemalloc to clear prior allocations
    force_gc() 

    # --- Executa a mesma lógica da medição de tempo ---
    # Need to re-insert data as the structure might have been cleared or modified by time measurement.
    ds.from_array(data)
    arr = ds.to_array()
    sorted_arr = sort_func(arr) # Use the provided sort function
    ds.from_array(sorted_arr)
    # --- Fim da lógica ---

    current, peak = tracemalloc.get_traced_memory()
    
    tracemalloc.stop()
    
    # Clean up structure and force GC to minimize impact on next measurements
    ds.from_array([]) 
    force_gc()

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
    
    log_file.write("\n" + "="*80 + "\n") # Expanded width for better formatting
    log_file.write("                   TABELA RESUMO FINAL\n")
    log_file.write("="*80 + "\n\n")
    
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
    log_file.write("\nTEMPO MÉDIO (ms):\n")
    for struct_name in structures_order:
        if struct_name in all_results:
            results_by_size = all_results[struct_name]
            # Ensure we have a result for the first size to get structure_type
            struct_type = results_by_size[sizes[0]].structure_type if sizes[0] in results_by_size else "N/A"
            line = f"{struct_name:<20} | {struct_type:<8} | "
            for size in sizes:
                if size in results_by_size:
                    line += f"{results_by_size[size].time_ms:10.2f} | "
                else:
                    line += f"{'N/A':>10} | " # If no data for this size
            log_file.write(line + "\n")

    # Seção de Memória (Pico)
    log_file.write("\nPICO DE MEMÓRIA (MB):\n")
    for struct_name in structures_order:
        if struct_name in all_results:
            results_by_size = all_results[struct_name]
            struct_type = results_by_size[sizes[0]].structure_type if sizes[0] in results_by_size else "N/A"
            line = f"{struct_name:<20} | {struct_type:<8} | "
            for size in sizes:
                if size in results_by_size:
                    line += f"{results_by_size[size].memory_mb:10.2f} | "
                else:
                    line += f"{'N/A':>10} | " # If no data for this size
            log_file.write(line + "\n")


def main():
    """Função principal que orquestra o benchmark."""
    log_filename = f"benchmark_python_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"
    
    with open(log_filename, 'w', encoding='utf-8') as log_file:
        log_system_info(log_file)
        
        print("=== BENCHMARK PYTHON - COUNTING SORT ===")
        print(f"Resultados serão salvos em: {log_filename}")
        
        NUM_REPETICOES = 10 # Defined here for easier access
        sizes_to_test = [100, 1000, 10000, 100000, 1000000]
        
        all_results: Dict[str, Dict[int, BenchmarkResult]] = {}

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
            
            if not data: # If data is still empty after trying both methods
                print(f"Erro: Não foi possível obter dados para o tamanho {size}. Pulando.")
                log_file.write(f"ERRO: Não foi possível obter dados para o tamanho {size}. Pulando.\n")
                continue

            # It's good practice to get the expected sorted data once per data set
            expected_sorted_data = sorted(data)
            
            for name, create_func in structures_to_test.items():
                ds_instance = create_func(size) # Create a fresh instance for each benchmark
                struct_type = "linear" if "Linear" in name else "dynamic"
                
                print(f"  {name:<20}: ", end='', flush=True)
                
                total_time_ms = 0.0
                successful_runs_time = 0
                first_run_memory_mb = 0.0 # Store memory from the first successful run

                # Run time measurement multiple times
                for i in range(NUM_REPETICOES):
                    # Create a new instance for each run to avoid side effects between runs
                    # particularly important for structures like queues/stacks where elements are consumed.
                    current_ds_instance_for_time = create_func(size) 
                    
                    start_time = time.perf_counter()
                    current_ds_instance_for_time.from_array(data)
                    arr_to_sort = current_ds_instance_for_time.to_array()
                    sorted_arr = counting_sort(arr_to_sort)
                    
                    # Verify sorting correctness
                    if sorted_arr == expected_sorted_data:
                        end_time = time.perf_counter()
                        total_time_ms += (end_time - start_time) * 1000
                        successful_runs_time += 1
                    else:
                        print(f"❌ Falha de ordenação na repetição {i+1} para {name} (tamanho {size}).", end="")
                        # Consider breaking here or marking as failed for this structure/size combination
                        # For now, we'll just not count this run towards the average.
                
                # Measure memory once after all time measurements, using a fresh instance
                # This gives a representative peak memory for this size/structure.
                force_gc() # Force GC before memory measurement
                ds_instance_for_mem = create_func(size)
                peak_memory_bytes = medir_memoria(ds_instance_for_mem, data, counting_sort)
                first_run_memory_mb = peak_memory_bytes / (1024.0 * 1024.0)

                if successful_runs_time > 0:
                    average_time_ms = total_time_ms / successful_runs_time
                else:
                    average_time_ms = -1.0 # Indicate failure or no successful runs

                # Store the result (average time, single memory measurement)
                result = BenchmarkResult(
                    structure_name=name,
                    structure_type=struct_type,
                    data_size=size,
                    time_ms=average_time_ms,
                    memory_mb=first_run_memory_mb
                )
                
                if name not in all_results:
                    all_results[name] = {}
                all_results[name][size] = result
                
                if average_time_ms >= 0:
                    print(f"Média (Tempo: {average_time_ms:.2f}ms, Memória Pico: {first_run_memory_mb:.2f}MB)")
                    log_file.write(f"{name} -> Tempo Médio: {average_time_ms:.4f} ms, Memória Pico: {first_run_memory_mb:.4f} MB\n")
                else:
                    print(f"Falha (Memória Pico: {first_run_memory_mb:.2f}MB)")
                    log_file.write(f"{name} -> FALHA (Tempo), Memória Pico: {first_run_memory_mb:.4f} MB\n")

        # Gerar a tabela resumo final no arquivo de log
        create_summary_table(log_file, all_results, sizes_to_test)
        
        log_file.write("\n" + "="*60 + "\n")
        log_file.write("                 BENCHMARK FINALIZADO\n")
        log_file.write("="*60 + "\n")
    
    print(f"\n✅ Benchmark concluído! Resultados salvos em: {log_filename}")


if __name__ == "__main__":
    main()