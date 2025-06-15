# benchmark_runner.py
import time
import gc
import sys
import platform
import psutil
from datetime import datetime
from typing import List, Dict, Callable, Tuple
from dataclasses import dataclass, field

# Adicionar diretórios ao path
sys.path.append('.')

# Importar módulos do projeto
from algorithms.counting_sort import counting_sort
from algorithms.radix_sort import radix_sort
from structures.list_linear import ListLinear
from structures.list_dynamic import ListDynamic
from structures.queue_linear import QueueLinear
from structures.queue_dynamic import QueueDynamic
from structures.stack_linear import StackLinear
from structures.stack_dynamic import StackDynamic
from utils.csv_reader import load_ratings_csv, generate_test_data
from utils.data_structure import DataStructure


NUM_EXECUTIONS = 10


@dataclass
class BenchmarkRun:
    """Resultado de uma execução individual"""
    execution_number: int
    time_ns: int
    time_micros: float
    time_ms: float
    memory_used_kb: float
    memory_used_mb: float


@dataclass
class BenchmarkResult:
    """Resultado completo de benchmark para uma estrutura"""
    structure_name: str
    structure_type: str
    algorithm: str
    data_size: int
    runs: List[BenchmarkRun] = field(default_factory=list)
    avg_time_ms: float = 0.0
    avg_memory_mb: float = 0.0
    min_time_ms: float = 0.0
    max_time_ms: float = 0.0
    min_memory_mb: float = 0.0
    max_memory_mb: float = 0.0


@dataclass
class SystemInfo:
    """Informações do sistema"""
    timestamp: str
    os: str
    arch: str
    cpus: int
    python_version: str
    total_mem_gb: float


def get_memory_usage() -> float:
    """Retorna o uso de memória atual em bytes"""
    process = psutil.Process()
    return process.memory_info().rss


def force_gc():
    """Força coleta de lixo"""
    gc.collect()
    gc.collect()
    time.sleep(0.1)


def run_single_benchmark(ds: DataStructure, data: List[int], algorithm: str) -> Tuple[int, float]:
    """Executa um único teste de benchmark"""
    force_gc()
    
    mem_before = get_memory_usage()
    start_time = time.perf_counter_ns()
    
    # Processo de ordenação
    ds.from_array(data)
    arr = ds.to_array()
    
    if algorithm == "counting":
        sorted_arr = counting_sort(arr)
    else:  # radix
        sorted_arr = radix_sort(arr)
    
    ds.from_array(sorted_arr)
    
    end_time = time.perf_counter_ns()
    mem_after = get_memory_usage()
    
    time_ns = end_time - start_time
    memory_bytes = max(0, mem_after - mem_before)
    
    return time_ns, memory_bytes


def benchmark_structure(
    struct_name: str, 
    struct_type: str,
    create_structure: Callable[[int], DataStructure],
    data: List[int],
    algorithm: str
) -> BenchmarkResult:
    """Executa benchmark completo para uma estrutura"""
    
    result = BenchmarkResult(
        structure_name=struct_name,
        structure_type=struct_type,
        algorithm=algorithm,
        data_size=len(data)
    )
    
    print(f"  {struct_name}: ", end='', flush=True)
    
    total_time = 0.0
    total_memory = 0.0
    min_time = float('inf')
    max_time = 0.0
    min_memory = float('inf')
    max_memory = 0.0
    
    for i in range(NUM_EXECUTIONS):
        ds = create_structure(len(data))
        time_ns, memory_bytes = run_single_benchmark(ds, data, algorithm)
        
        run = BenchmarkRun(
            execution_number=i + 1,
            time_ns=time_ns,
            time_micros=time_ns / 1000.0,
            time_ms=time_ns / 1e6,
            memory_used_kb=memory_bytes / 1024.0,
            memory_used_mb=memory_bytes / (1024.0 * 1024.0)
        )
        
        result.runs.append(run)
        
        total_time += run.time_ms
        total_memory += run.memory_used_mb
        
        min_time = min(min_time, run.time_ms)
        max_time = max(max_time, run.time_ms)
        min_memory = min(min_memory, run.memory_used_mb)
        max_memory = max(max_memory, run.memory_used_mb)
        
        print(".", end='', flush=True)
    
    result.avg_time_ms = total_time / NUM_EXECUTIONS
    result.avg_memory_mb = total_memory / NUM_EXECUTIONS
    result.min_time_ms = min_time
    result.max_time_ms = max_time
    result.min_memory_mb = min_memory
    result.max_memory_mb = max_memory
    
    print(f" Concluído (Média: {result.avg_time_ms:.2f}ms, {result.avg_memory_mb:.2f}MB)")
    
    return result


def run_benchmarks_for_size(data: List[int], algorithm: str, log_file) -> List[BenchmarkResult]:
    """Executa benchmarks para um tamanho específico de dados"""
    results = []
    
    log_file.write(f"\n=== TAMANHO DO DATASET: {len(data)} elementos ===\n")
    log_file.write(f"Algoritmo: {algorithm.upper()} SORT\n")
    print(f"\n--- Testando com {len(data)} elementos ({algorithm} sort) ---")
    
    # Lista Linear
    result = benchmark_structure(
        "Lista Linear", "linear",
        lambda size: ListLinear(size + 100),
        data, algorithm
    )
    results.append(result)
    log_result(log_file, result)
    
    # Lista Dinâmica
    result = benchmark_structure(
        "Lista Dinâmica", "dynamic",
        lambda size: ListDynamic(),
        data, algorithm
    )
    results.append(result)
    log_result(log_file, result)
    
    # Fila Linear
    result = benchmark_structure(
        "Fila Linear", "linear",
        lambda size: QueueLinear(size + 100),
        data, algorithm
    )
    results.append(result)
    log_result(log_file, result)
    
    # Fila Dinâmica
    result = benchmark_structure(
        "Fila Dinâmica", "dynamic",
        lambda size: QueueDynamic(),
        data, algorithm
    )
    results.append(result)
    log_result(log_file, result)
    
    # Pilha Linear
    result = benchmark_structure(
        "Pilha Linear", "linear",
        lambda size: StackLinear(size + 100),
        data, algorithm
    )
    results.append(result)
    log_result(log_file, result)
    
    # Pilha Dinâmica
    result = benchmark_structure(
        "Pilha Dinâmica", "dynamic",
        lambda size: StackDynamic(),
        data, algorithm
    )
    results.append(result)
    log_result(log_file, result)
    
    return results


def log_result(log_file, result: BenchmarkResult):
    """Registra resultado no arquivo de log"""
    log_file.write(f"\n{result.structure_name} ({result.structure_type}) - {result.data_size} elementos:\n")
    log_file.write("-" * 40 + "\n")
    
    # Cabeçalho da tabela
    log_file.write("Execução | Tempo (ms) | Memória (MB)\n")
    log_file.write("---------|------------|-------------\n")
    
    # Dados de cada execução
    for run in result.runs:
        log_file.write(f"{run.execution_number:8d} | {run.time_ms:10.2f} | {run.memory_used_mb:11.2f}\n")
    
    log_file.write("---------|------------|-------------\n")
    log_file.write(f"MÉDIA    | {result.avg_time_ms:10.2f} | {result.avg_memory_mb:11.2f}\n")
    log_file.write(f"MÍNIMO   | {result.min_time_ms:10.2f} | {result.min_memory_mb:11.2f}\n")
    log_file.write(f"MÁXIMO   | {result.max_time_ms:10.2f} | {result.max_memory_mb:11.2f}\n")
    log_file.write("\n")


def get_system_info() -> SystemInfo:
    """Coleta informações do sistema"""
    return SystemInfo(
        timestamp=datetime.now().strftime("%d/%m/%Y %H:%M:%S"),
        os=platform.system(),
        arch=platform.machine(),
        cpus=psutil.cpu_count(),
        python_version=platform.python_version(),
        total_mem_gb=psutil.virtual_memory().total / (1024**3)
    )


def log_system_info(log_file, info: SystemInfo):
    """Registra informações do sistema no log"""
    log_file.write("="*50 + "\n")
    log_file.write("     BENCHMARK - ORDENAÇÃO NÃO COMPARATIVA      \n")
    log_file.write("="*50 + "\n")
    log_file.write(f"Data/Hora: {info.timestamp}\n")
    log_file.write(f"Sistema: {info.os}/{info.arch}\n")
    log_file.write(f"CPUs: {info.cpus}\n")
    log_file.write(f"Python Version: {info.python_version}\n")
    log_file.write(f"Memória Total: {info.total_mem_gb:.2f} GB\n")
    log_file.write(f"Execuções por teste: {NUM_EXECUTIONS}\n")
    log_file.write("="*50 + "\n")


def create_summary_table(log_file, all_results: Dict[str, List[List[BenchmarkResult]]]):
    """Cria tabela resumo final"""
    log_file.write("\n" + "="*50 + "\n")
    log_file.write("           TABELA RESUMO FINAL           \n")
    log_file.write("="*50 + "\n\n")
    
    sizes = [100, 1000, 10000, 100000, 1000000]
    structures = [
        "Lista Linear", "Lista Dinâmica",
        "Fila Linear", "Fila Dinâmica",
        "Pilha Linear", "Pilha Dinâmica"
    ]
    
    for algorithm in ["counting", "radix"]:
        log_file.write(f"\n{'='*20} {algorithm.upper()} SORT {'='*20}\n\n")
        
        # Cabeçalho
        log_file.write(f"{'Estrutura':<20} | {'Tipo':<8} | ")
        for size in sizes:
            log_file.write(f"{size:>10} | ")
        log_file.write("\n")
        
        # Linha separadora
        log_file.write("-"*20 + "-+-" + "-"*8 + "-+-")
        for _ in sizes:
            log_file.write("-"*11 + "+-")
        log_file.write("\n")
        
        # Dados de tempo
        log_file.write("\nTEMPO MÉDIO (ms):\n")
        for struct_name in structures:
            # Encontrar tipo da estrutura
            struct_type = ""
            for size_idx, results in enumerate(all_results[algorithm]):
                for result in results:
                    if result.structure_name == struct_name:
                        struct_type = result.structure_type
                        break
                if struct_type:
                    break
            
            log_file.write(f"{struct_name:<20} | {struct_type:<8} | ")
            
            for size_idx in range(len(sizes)):
                found = False
                for result in all_results[algorithm][size_idx]:
                    if result.structure_name == struct_name:
                        log_file.write(f"{result.avg_time_ms:10.2f} | ")
                        found = True
                        break
                if not found:
                    log_file.write(f"{'N/A':>10} | ")
            log_file.write("\n")
        
        # Dados de memória
        log_file.write("\nMEMÓRIA MÉDIA (MB):\n")
        for struct_name in structures:
            # Encontrar tipo da estrutura
            struct_type = ""
            for size_idx, results in enumerate(all_results[algorithm]):
                for result in results:
                    if result.structure_name == struct_name:
                        struct_type = result.structure_type
                        break
                if struct_type:
                    break
            
            log_file.write(f"{struct_name:<20} | {struct_type:<8} | ")
            
            for size_idx in range(len(sizes)):
                found = False
                for result in all_results[algorithm][size_idx]:
                    if result.structure_name == struct_name:
                        log_file.write(f"{result.avg_memory_mb:10.2f} | ")
                        found = True
                        break
                if not found:
                    log_file.write(f"{'N/A':>10} | ")
            log_file.write("\n")


def main():
    """Função principal"""
    # Criar arquivo de log
    log_filename = f"benchmark_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"
    
    with open(log_filename, 'w', encoding='utf-8') as log_file:
        # Log system info
        sys_info = get_system_info()
        log_system_info(log_file, sys_info)
        
        print("=== BENCHMARK ORDENAÇÃO NÃO COMPARATIVA ===")
        print(f"Executando {NUM_EXECUTIONS} testes para cada estrutura...")
        print(f"Salvando resultados em: {log_filename}")
        
        # Tamanhos para testar
        sizes = [100, 1000, 10000, 100000, 1000000]
        all_results = {"counting": [], "radix": []}
        
        # Caminho do arquivo CSV - ajuste conforme necessário
        csv_path = "ml-25m/ratings.csv"
        
        for algorithm in ["counting", "radix"]:
            print(f"\n\n{'='*20} {algorithm.upper()} SORT {'='*20}")
            all_results[algorithm] = []
            
            for size in sizes:
                # Carregar dados
                data = load_ratings_csv(csv_path, size)
                
                # Se não conseguir ler o arquivo, criar dados de teste
                if not data:
                    print(f"Aviso: Usando dados de teste para tamanho {size}")
                    data = generate_test_data(size)
                
                results = run_benchmarks_for_size(data, algorithm, log_file)
                all_results[algorithm].append(results)
        
        # Criar tabela resumo
        create_summary_table(log_file, all_results)
        
        log_file.write("\n" + "="*50 + "\n")
        log_file.write("         BENCHMARK FINALIZADO            \n")
        log_file.write("="*50 + "\n")
    
    print(f"\n✅ Benchmark concluído! Resultados salvos em: {log_filename}")


if __name__ == "__main__":
    main()