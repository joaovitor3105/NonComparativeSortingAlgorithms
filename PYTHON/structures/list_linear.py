# structures/list_linear.py
from typing import List
import sys
sys.path.append('..')
from utils.data_structure import DataStructure


class ListLinear(DataStructure):
    """Lista com alocação linear (array fixo)"""
    
    def __init__(self, capacity: int):
        self.data = [0] * capacity
        self._size = 0
        self.capacity = capacity
    
    def add(self, value: int) -> None:
        if self._size < self.capacity:
            self.data[self._size] = value
            self._size += 1
    
    def to_array(self) -> List[int]:
        return self.data[:self._size].copy()
    
    def from_array(self, arr: List[int]) -> None:
        self._size = 0
        for v in arr:
            if self._size < self.capacity:
                self.data[self._size] = v
                self._size += 1
    
    def size(self) -> int:
        return self._size