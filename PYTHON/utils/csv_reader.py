# utils/csv_reader.py
import csv
from typing import List, Tuple
from enum import Enum


class SortField(Enum):
    """Enum para escolher qual campo ordenar"""
    USER_ID = 0
    MOVIE_ID = 1
    RATING = 2
    TIMESTAMP = 3


def load_ratings_csv(filename: str, limit: int = 0) -> List[int]:
    """
    Carrega ratings do arquivo CSV
    Retorna uma lista de inteiros (ratings multiplicados por 2)
    """
    ratings = []
    count = 0
    
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            
            # Pular cabeçalho
            next(reader, None)
            
            for row in reader:
                try:
                    # Converter rating (coluna 3) para inteiro
                    # Ratings vão de 0.5 a 5.0 em incrementos de 0.5
                    # Multiplicamos por 2 para ter inteiros de 1 a 10
                    rating_float = float(row[2])
                    
                    # Multiplicar por 2 para converter: 0.5→1, 1.0→2, ..., 5.0→10
                    rating_int = int(rating_float * 2)
                    
                    ratings.append(rating_int)
                    count += 1
                    
                    if limit > 0 and count >= limit:
                        break
                        
                except (ValueError, IndexError):
                    continue
        
        print(f"Carregados {len(ratings)} ratings do CSV (valores de 1 a 10)")
        return ratings
        
    except FileNotFoundError:
        print(f"Erro: Arquivo {filename} não encontrado")
        return []
    except Exception as e:
        print(f"Erro ao ler arquivo: {e}")
        return []


def generate_test_data(size: int) -> List[int]:
    """
    Gera dados de teste caso o arquivo CSV não esteja disponível
    """
    import random
    random.seed(42)  # Para resultados reproduzíveis
    
    # Gerar ratings aleatórios de 1 a 10
    data = [random.randint(1, 10) for _ in range(size)]
    print(f"Gerados {size} ratings de teste (valores de 1 a 10)")
    return data