# structures/stack_linear.py
from typing import List, Tuple
import sys
sys.path.append('..')
from utils.data_structure import DataStructure


class StackLinear(DataStructure):
    """Pilha com alocação linear (array fixo)"""
    
    def __init__(self, capacity: int):
        self.data = [0] * capacity
        self.top = -1
        self.capacity = capacity
    
    def push(self, value: int) -> None:
        if self.top < self.capacity - 1:
            self.top += 1
            self.data[self.top] = value
    
    def pop(self) -> Tuple[int, bool]:
        if self.top == -1:
            return 0, False
        
        value = self.data[self.top]
        self.top -= 1
        return value, True
    
    def to_array(self) -> List[int]:
        return self.data[:self.top + 1].copy()
    
    def from_array(self, arr: List[int]) -> None:
        self.top = -1
        for v in arr:
            self.push(v)
    
    def size(self) -> int:
        return self.top + 1