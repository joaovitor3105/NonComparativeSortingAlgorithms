# utils/data_structure.py
from abc import ABC, abstractmethod
from typing import List


class DataStructure(ABC):
    """Interface base para todas as estruturas de dados"""
    
    @abstractmethod
    def to_array(self) -> List[int]:
        """Converte a estrutura para um array"""
        pass
    
    @abstractmethod
    def from_array(self, arr: List[int]) -> None:
        """Preenche a estrutura a partir de um array"""
        pass
    
    @abstractmethod
    def size(self) -> int:
        """Retorna o tamanho da estrutura"""
        pass